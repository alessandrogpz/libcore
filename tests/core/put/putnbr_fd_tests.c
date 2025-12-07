#include <stdio.h>
#include <stdlib.h> // For free
#include <unistd.h> // For write, read, close, unlink
#include <fcntl.h>  // For file flags
#include <string.h> // For strcmp, strlen
#include <limits.h> // For INT_MIN/INT_MAX
#include "libcore.h"

// -----------------------------------------------------------------------------
//                         FILE VERIFICATION TEST
// -----------------------------------------------------------------------------

// Helper to run the test: writes the number to a file, reads back, verifies content.
void run_nbr_test(const char *test_name, int n, const char *expected_str)
{
    const char *temp_filename = "putnbr_test_output.txt";
    int fd;
    char buffer[30]; // Buffer large enough for INT_MIN string + extra
    size_t expected_len = strlen(expected_str);
    int success = 0;

    printf("--- Test: %s (Input: %d) ---\n", test_name, n);

    // 1. OPEN, WRITE, and CLOSE the temporary file
    fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("Error opening file for writing");
        return;
    }

    // Call the function being tested
    putnbr_fd(n, fd);
    close(fd);

    // 2. OPEN, READ, and CLOSE the file again to verify
    fd = open(temp_filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file for reading");
        unlink(temp_filename);
        return;
    }

    // Read the content back into the buffer
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    close(fd);

    buffer[bytes_read] = '\0'; // Null-terminate the read buffer

    // 3. Verification
    if (bytes_read == (ssize_t)expected_len && strcmp(buffer, expected_str) == 0)
        success = 1;

    // 4. Output Result and Cleanup
    if (success)
        printf("  -> \033[32mPASS\033[0m: Output verified: \"%s\"\n\n", buffer);
    else
        printf("  -> \033[31mFAIL\033[0m: Expected: \"%s\", Got: \"%s\"\n\n", expected_str, buffer);

    // Clean up the created file
    unlink(temp_filename);
}

// -----------------------------------------------------------------------------
//                         MAIN FUNCTION
// -----------------------------------------------------------------------------

int main(void)
{
    printf("--- Running putnbr_fd Verification Tests ---\n\n");

    // 1. Zero and Single Digits
    run_nbr_test("1. Zero (0)", 0, "0");
    run_nbr_test("2. Positive Single Digit (5)", 5, "5");
    run_nbr_test("3. Negative Single Digit (-5)", -5, "-5");

    // 2. Standard Numbers
    run_nbr_test("4. Standard Positive (4200)", 4200, "4200");
    run_nbr_test("5. Standard Negative (-1234)", -1234, "-1234");

    // 3. Edge Cases (Crucial for itoa logic)
    // NOTE: This test requires itoa to correctly handle INT_MIN.
    run_nbr_test("6. INT_MAX", INT_MAX, "2147483647");
    run_nbr_test("7. INT_MIN", INT_MIN, "-2147483648");

    printf("--- All Tests Complete ---\n");

    return (EXIT_SUCCESS);
}