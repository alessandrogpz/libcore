#include <stdio.h>
#include <string.h> // For standard strrchr
#include <stdlib.h> // For NULL
#include "libcore.h"

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ====================================================================

// Function to run and display a single test result
void run_strrchr_test(const char *test_name, const char *s, int c)
{
    // The standard strrchr must be used with the same arguments
    char *core_ptr = core_strrchr(s, c);
    char *std_ptr = strrchr(s, c);

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
    printf("--- Running core_strrchr vs strrchr Comparison Tests ---\n\n");

    char str[] = "apple and orange!";

    // 1. Character Found Multiple Times (Last 'a')
    run_strrchr_test("1. Last Occurrence ('a')", str, 'a');

    // 2. Character Found Multiple Times (Last 'p')
    run_strrchr_test("2. Last Occurrence ('p')", str, 'p');

    // 3. Character Found Once (At start)
    run_strrchr_test("3. Single Occurrence ('d')", str, 'd');

    // 4. Character Not Found
    run_strrchr_test("4. Not Found ('z')", str, 'z');

    // 5. Character Found at End (Exclamation mark)
    run_strrchr_test("5. Found at End ('!')", str, '!');

    // 6. Null-Terminator Search (CRITICAL EDGE CASE)
    // Should return a pointer to the '\0' character.
    run_strrchr_test("6. Search for Null ('\\0')", str, '\0');

    // 7. Empty String Test (Should return NULL)
    run_strrchr_test("7. Empty String ('a')", "", 'a');

    // 8. Search for a character not found, but a digit
    run_strrchr_test("8. Not Found Digit ('5')", str, '5');

    printf("--- All Tests Complete ---\n");

    return (EXIT_SUCCESS);
}