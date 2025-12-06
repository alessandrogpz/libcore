#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For write, read, close, unlink
#include <fcntl.h>  // For file flags (O_WRONLY, O_CREAT, etc.)
#include <string.h> // For strcmp
#include "includes.h"

// -----------------------------------------------------------------------------
//                         FILE VERIFICATION TEST
// -----------------------------------------------------------------------------

// Helper to run the test: writes to a file, reads back, verifies content.
void run_file_test(const char *test_name, char c)
{
    const char *temp_filename = "test_output.txt";
    int fd;
    char buffer;
    int success = 0;

    printf("--- Test: %s (Char: '%c') ---\n", test_name, (c == '\n' ? ' ' : c));

    // 1. OPEN, WRITE, and CLOSE the temporary file
    // O_CREAT creates the file, O_TRUNC clears it, 0644 are permissions
    fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("Error opening file for writing");
        return;
    }

    // Call the function being tested
    putchar_fd(c, fd);
    close(fd);

    // 2. OPEN, READ, and CLOSE the file again to verify
    fd = open(temp_filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file for reading");
        unlink(temp_filename);
        return;
    }

    // Read the single character back
    if (read(fd, &buffer, 1) == 1)
    {
        if (buffer == c)
            success = 1;
    }
    close(fd);

    // 3. Output Result and Cleanup
    if (success)
        printf("  -> \033[32mPASS\033[0m: Character correctly written and verified.\n\n");
    else
        printf("  -> \033[31mFAIL\033[0m: Character mismatch or read failure.\n\n");

    // Clean up the created file
    unlink(temp_filename);
}

// -----------------------------------------------------------------------------
//                         TERMINAL VISUAL TEST
// -----------------------------------------------------------------------------

void run_visual_test(const char *test_name, char c, int fd)
{
    // STDOUT (fd 1) or STDERR (fd 2)
    printf("--- Test: %s (FD %d) ---\n", test_name, fd);
    printf("  Expected Output: '%c' on line below.\n", (c == '\n' ? '_' : c));

    // Call the function being tested
    putchar_fd(c, fd);

    // The visual check is left to the human running the test.
    if (fd != 2) // Avoids confusing error logs
        putchar_fd('\n', fd);
}

// -----------------------------------------------------------------------------
//                         MAIN FUNCTION
// -----------------------------------------------------------------------------

int main(void)
{
    printf("--- Running putchar_fd Tests ---\n");

    // PART A: TERMINAL VISUAL TESTS (FD 1 - STDOUT)
    // NOTE: You must visually confirm the output.
    run_visual_test("A1. Visual Check (Standard Output)", 'X', 1);
    run_visual_test("A2. Visual Check (Newline)", '\n', 1);

    // PART B: TERMINAL VISUAL TESTS (FD 2 - STDERR)
    // The output should be displayed, but potentially unsynchronized with STDOUT
    run_visual_test("B. Visual Check (Standard Error)", 'E', 2);

    // PART C: FILE SYSTEM VERIFICATION TESTS (Most rigorous check)
    run_file_test("C1. File Verification (Letter)", 'Z');
    run_file_test("C2. File Verification (Space)", ' ');
    run_file_test("C3. File Verification (Newline)", '\n');

    printf("--- All Tests Complete ---\n");

    return (0);
}