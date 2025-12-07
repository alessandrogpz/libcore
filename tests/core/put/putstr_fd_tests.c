#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For write, read, close, unlink
#include <fcntl.h>  // For file flags
#include <string.h> // For strcmp, strlen
#include "libcore.h"

// -----------------------------------------------------------------------------
//                         FILE VERIFICATION TEST
// -----------------------------------------------------------------------------

// Helper to run the test: writes the string to a file, reads back, verifies content.
void run_file_test(const char *test_name, char *s, const char *expected)
{
    const char *temp_filename = "putstr_test_output.txt";
    int fd;
    char buffer[100]; // Buffer to read content back
    size_t expected_len = strlen(expected);
    int success = 0;

    printf("--- Test: %s ---\n", test_name);
    printf("  Input: \"%s\"\n", s);
    printf("  Expected: \"%s\" (Len: %zu)\n", expected, expected_len);

    // 1. OPEN, WRITE, and CLOSE the temporary file
    fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("Error opening file for writing");
        return;
    }

    // Call the function being tested
    putstr_fd(s, fd);
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
    if (bytes_read == (ssize_t)expected_len && strcmp(buffer, expected) == 0)
        success = 1;

    // 4. Output Result and Cleanup
    if (success)
        printf("  -> \033[32mPASS\033[0m: Content correctly written and verified.\n\n");
    else
        printf("  -> \033[31mFAIL\033[0m: Mismatch (Read: \"%s\", Expected: \"%s\").\n\n", buffer, expected);

    // Clean up the created file
    unlink(temp_filename);
}

// -----------------------------------------------------------------------------
//                         MAIN FUNCTION
// -----------------------------------------------------------------------------

int main(void)
{
    printf("--- Running putstr_fd Verification Tests ---\n\n");

    // 1. Basic String Test
    run_file_test("1. Basic String", "Hello World!", "Hello World!");

    // 2. String with Newline
    run_file_test("2. String with Newline", "Line 1\nLine 2", "Line 1\nLine 2");

    // 3. Empty String (Should write 0 bytes)
    run_file_test("3. Empty String", "", "");

    // 4. String with Spaces and Symbols
    run_file_test("4. Spaces and Symbols", "a b c 1 2 3 !@#", "a b c 1 2 3 !@#");

    // 5. Short String
    run_file_test("5. Short String", "Test", "Test");

    printf("--- All Tests Complete ---\n");

    return (0);
}