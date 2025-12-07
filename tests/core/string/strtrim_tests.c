#include <stdio.h>
#include <stdlib.h> // For standard malloc, free, NULL
#include <string.h> // For standard strcmp, strlen
#include "libcore.h"

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ====================================================================

// Function to run and display a single test result
void run_strtrim_test(const char *test_name, const char *s1, const char *set, const char *expected)
{
    char *trimmed = strtrim(s1, set);

    printf("--- Test: %s ---\n", test_name);
    printf("  S1: \"%s\", SET: \"%s\"\n", s1, set);
    printf("  Expected: \"%s\"\n", expected);

    if (trimmed == NULL && expected != NULL)
    {
        printf("  -> \033[31mFAIL\033[0m: Allocation failed (returned NULL).\n\n");
        return;
    }
    else if (trimmed == NULL && expected == NULL)
    {
        printf("  -> \033[32mPASS\033[0m: Correctly returned NULL.\n\n");
        return;
    }

    // --- 1. Check Content ---
    if (strcmp(expected, trimmed) == 0)
        printf("  -> Content Check: \033[32mPASS\033[0m (Result: \"%s\")\n", trimmed);
    else
        printf("  -> Content Check: \033[31mFAIL\033[0m (Got: \"%s\")\n", trimmed);

    // --- 2. Check Length and Null Termination ---
    if (core_strlen(trimmed) == core_strlen(expected))
        printf("  -> Length Check: \033[32mPASS\033[0m (Len: %zu)\n\n", core_strlen(trimmed));
    else
        printf("  -> Length Check: \033[31mFAIL\033[0m (Expected Len: %zu, Got Len: %zu)\n\n", core_strlen(expected), core_strlen(trimmed));

    free(trimmed);
}

// ====================================================================
//                         MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running strtrim Comparison Tests ---\n\n");

    // 1. Basic Bidirectional Trim
    run_strtrim_test("1. Basic Both Ends", "xxxHello Worldxxx", "x", "Hello World");

    // 2. Complex Bidirectional Trim (Mixed Characters)
    run_strtrim_test("2. Mixed Set Characters", "\n\t-+-Hello World-+-\n\t", " \t\n-+", "Hello World");

    // 3. Trim Only Left Side
    run_strtrim_test("3. Only Left", "aaabbbccc", "a", "bbbccc");

    // 4. Trim Only Right Side
    run_strtrim_test("4. Only Right", "aaabbbccc", "c", "aaabbb");

    // 5. No Trim Needed
    run_strtrim_test("5. No Trim", "a b c", "xyz", "a b c");

    // 6. Full Trim (Input consists entirely of characters in set)
    run_strtrim_test("6. Full Trim", "---", "-", "");

    // 7. Empty Input String (s1)
    run_strtrim_test("7. Empty S1", "", "abc", "");

    // 8. Empty Set String (set)
    run_strtrim_test("8. Empty Set", "abc", "", "abc");

    // 9. Input String Shorter than Set (Tests boundary checks)
    run_strtrim_test("9. S1 Shorter than SET", "abc", "axbyc", ""); // Result should be empty

    printf("--- All Tests Complete ---\n");

    return (EXIT_SUCCESS);
}