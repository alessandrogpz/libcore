#include <stdio.h>
#include <stdlib.h> // For standard malloc, free
#include <string.h> // For standard strcmp, strlen
#include "includes.h"

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ====================================================================

// Function to run and display a single test result
void run_strjoin_test(const char *test_name, const char *s1, const char *s2, const char *expected)
{
    char *join = strjoin(s1, s2);

    printf("--- Test: %s ---\n", test_name);
    printf("  Input S1: \"%s\", S2: \"%s\"\n", s1, s2);
    printf("  Expected: \"%s\" (Len: %zu)\n", expected, strlen(expected));

    if (join == NULL && expected != NULL)
    {
        // Allocation failure check
        printf("  -> \033[31mFAIL\033[0m: Returned NULL (Allocation Failure).\n\n");
        return;
    }
    else if (join == NULL && expected == NULL)
    {
        // Case where NULL is expected (e.g., if you choose to fail on NULL input)
        printf("  -> \033[32mPASS\033[0m: Correctly returned NULL.\n\n");
        return;
    }

    // --- 1. Check Content ---
    if (strcmp(expected, join) == 0)
        printf("  -> Content Check: \033[32mPASS\033[0m (Result: \"%s\")\n", join);
    else
        printf("  -> Content Check: \033[31mFAIL\033[0m (Got: \"%s\")\n", join);

    // --- 2. Check Length and Null Termination ---
    if (strlen(join) == strlen(expected))
        printf("  -> Length Check: \033[32mPASS\033[0m (Len: %zu)\n\n", strlen(join));
    else
        printf("  -> Length Check: \033[31mFAIL\033[0m (Expected Len: %zu, Got Len: %zu)\n\n", strlen(expected), strlen(join));

    // Clean up allocated memory
    free(join);
}

// ====================================================================
//                         MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running strjoin Comparison Tests ---\n\n");

    // 1. Basic Concatenation
    run_strjoin_test("1. Basic Alpha-Numeric Join", "Hello, ", "World!", "Hello, World!");

    // 2. Empty Source (Critical edge case)
    run_strjoin_test("2. Empty S1", "", "World", "World");
    run_strjoin_test("3. Empty S2", "Hello", "", "Hello");
    run_strjoin_test("4. Both Empty", "", "", "");

    // 3. Long Strings
    run_strjoin_test("5. Long Strings", "This is the first part. ", "This is the second part.",
                     "This is the first part. This is the second part.");

    // 4. Strings with Numbers/Symbols
    run_strjoin_test("6. Symbols and Numbers", "Key=42", ";Value=ABC", "Key=42;Value=ABC");

    printf("--- All Tests Complete ---\n");

    return (EXIT_SUCCESS);
}