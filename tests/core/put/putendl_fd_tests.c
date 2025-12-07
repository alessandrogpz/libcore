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
void run_file_test(const char *test_name, char *s)
{
    const char *temp_filename = "putendl_test_output.txt";
    int fd;
    char buffer[100]; // Buffer to read content back

    // Calculate expected length: string length + 1 for the newline
    size_t expected_len = strlen(s) + 1;

    printf("--- Test: %s ---\n", test_name);
    printf("  Input String: \"%s\"\n", s);
    printf("  Expected Content: \"%s\\n\" (Total Len: %zu)\n", s, expected_len);

    // 1. OPEN, WRITE, and CLOSE the temporary file
    fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("Error opening file for writing");
        return;
    }

    // Call the function being tested
    putendl_fd(s, fd);
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

    // 3. Verification: Check length and ensure the last character read is a newline.
    int success = 0;
    if (bytes_read == (ssize_t)expected_len && buffer[expected_len - 1] == '\n')
    {
        // Temporarily null-terminate the read string before the newline for comparison
        buffer[expected_len - 1] = '\0';
        if (strcmp(buffer, s) == 0)
            success = 1;
    }

    // 4. Output Result and Cleanup
    if (success)
        printf("  -> \033[32mPASS\033[0m: String and newline verified.\n\n");
    else
        printf("  -> \033[31mFAIL\033[0m: Output missing string or newline.\n\n");

    // Clean up the created file
    unlink(temp_filename);
}

// -----------------------------------------------------------------------------
//                         MAIN FUNCTION
// -----------------------------------------------------------------------------

int main(void)
{
    printf("--- Running putendl_fd Verification Tests ---\n\n");

    // 1. Basic String Test
    run_file_test("1. Basic String", "Test line content");

    // 2. String with Spaces/Symbols
    run_file_test("2. Spaces and Symbols", "Line with !@# $ % &");

    // 3. Empty String Input (Should only write '\n', total length 1)
    run_file_test("3. Empty String", "");

    // 4. String that already ends with a newline (Will output two newlines)
    run_file_test("4. String Ending in Newline", "End of line\n");

    printf("--- All Tests Complete ---\n");

    return (EXIT_SUCCESS);
}