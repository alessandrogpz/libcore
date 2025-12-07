#include <stdio.h>
#include <string.h> // For standard strchr
#include <stdlib.h> // For NULL
#include "libcore.h"

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ====================================================================

// Function to run and display a single test result
void run_strchr_test(const char *test_name, const char *s, int c)
{
    // The standard strchr must be used with the same arguments
    char *core_ptr = core_strchr(s, c);
    char *std_ptr = strchr(s, c);

    printf("--- Test: %s ---\n", test_name);
    printf("  Search for char '%c' (ASCII %d) in \"%s\"\n", (char)c, c, s);
    printf("  core_ptr: %p\n", (void *)core_ptr);
    printf("  std_ptr: %p\n", (void *)std_ptr);

    // --- 1. Check Pointer Equality (NULL or Address) ---
    // If both return the same address (or both return NULL/0), they match.
    if (core_ptr == std_ptr)
    {
        printf("  -> \033[32mPASS\033[0m: Pointers Match.\n");

        // Extra check: If found, verify the content at that pointer is correct
        if (core_ptr != NULL)
            printf("  -> Found Value: '%c'\n\n", *core_ptr);
        else
            printf("  -> Result: NOT FOUND (NULL)\n\n");
    }
    else
    {
        printf("  -> \033[31mFAIL (Mismatch)\033[0m: Pointers Differ.\n");
        if (core_ptr != NULL && std_ptr != NULL)
            printf("  -> ft points to: '%c', std points to: '%c'\n\n", *core_ptr, *std_ptr);
        else
            printf("  -> One returned NULL, the other returned an address.\n\n");
    }
}

// ====================================================================
//                         MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running core_strchr vs strchr Comparison Tests ---\n\n");

    char str[] = "The quick brown fox.";

    // 1. Character Found at Start
    run_strchr_test("1. Found at Start ('T')", str, 'T');

    // 2. Character Found in Middle
    run_strchr_test("2. Found in Middle ('b')", str, 'b');

    // 3. Character Not Found
    run_strchr_test("3. Not Found ('z')", str, 'z');

    // 4. Character Found at End (space character)
    run_strchr_test("4. Found at End ('.')", str, '.');

    // 5. Null-Terminator Search (CRITICAL EDGE CASE)
    // Should return a pointer to the byte AFTER the dot ('.')
    run_strchr_test("5. Search for Null ('\\0')", str, '\0');

    // 6. Character Found Multiple Times (Tests for FIRST occurrence)
    run_strchr_test("6. Multiple ('o')", str, 'o');

    // 7. Case Sensitivity Check
    run_strchr_test("7. Case Sensitivity ('O')", str, 'O');

    // 8. Empty String Test
    run_strchr_test("8. Empty String ('a')", "", 'a');

    printf("--- All Tests Complete ---\n");

    return (EXIT_SUCCESS);
}