#include <stdio.h>
#include <stdlib.h> // For malloc, free, NULL
#include <string.h> // For strcmp, strlen
#include "includes.h"

// ====================================================================
//            LOCAL FUNCTION DEFINITIONS (FOR TESTING)
// ====================================================================

// --- Mapping Function 1: Simple Index-Based Transformation ---
// Adds the index (i) to the character (c). Wraps around ASCII values.
char map_add_index(unsigned int i, char c)
{
    return (c + (i % 5)); // Add index mod 5 to keep result printable
}

// --- Mapping Function 2: Index-Specific Transformation ---
// Capitalizes every even-indexed character.
char map_capitalize_even(unsigned int i, char c)
{
    if (i % 2 == 0 && c >= 'a' && c <= 'z')
        return (c - 32); // Convert to uppercase
    return (c);
}

// --- Mapping Function 3: Character Replacement ---
// Replaces every 'e' with a 'X'. Ignores index.
char map_replace_e(unsigned int i, char c)
{
    (void)i; // Cast to void to suppress unused variable warning
    if (c == 'e')
        return ('X');
    return (c);
}

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ====================================================================

// Function to run and display a single test result
void run_strmapi_test(const char *test_name, const char *s, char (*f)(unsigned int, char), const char *expected)
{
    char *result = strmapi(s, f);

    printf("--- Test: %s ---\n", test_name);
    printf("  Input: \"%s\"\n", s);
    printf("  Expected: \"%s\"\n", expected);

    if (result == NULL && expected != NULL)
    {
        printf("  -> \033[31mFAIL\033[0m (Returned NULL unexpectedly)\n\n");
        return;
    }
    if (result == NULL && expected == NULL)
    {
        printf("  -> \033[32mPASS\033[0m (Correctly returned NULL)\n\n");
        return;
    }

    // Check Content
    if (strcmp(expected, result) == 0)
    {
        printf("  -> \033[32mPASS\033[0m (Content match)\n");

        // Check Independence (optional but good)
        if (result != s)
            printf("  -> Address Check: \033[32mPASS\033[0m (New memory allocated)\n\n");
        else
            printf("  -> Address Check: \033[31mFAIL\033[0m (Did not allocate new memory)\n\n");
    }
    else
    {
        printf("  -> \033[31mFAIL (Mismatch)\033[0m (Got: \"%s\")\n\n", result);
    }

    // Clean up allocated memory
    if (result)
        free(result);
}

// ====================================================================
//                         MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running strmapi Comparison Tests ---\n\n");

    // 1. Empty String Input (Should return NULL based on your implementation choice)
    run_strmapi_test("1. Empty Input", "", map_add_index, NULL);

    // 2. Index-based transformation (map_capitalize_even)
    // Input: "hello world"
    // Index: 01234 567890
    // Fix: 'w' (index 6) capitalizes. 'o' (index 7) does not. 'r' (index 8) capitalizes.
    // Correct Expected: "HeLlO WoRlD"
    run_strmapi_test("2. Capitalize Even Index", "hello world", map_capitalize_even, "HeLlO WoRlD");

    // 3. Simple Character Replacement (map_replace_e)
    // Input: "elephants like trees"
    // Fix: All 'e's are replaced: XlXphants likX trXXs
    // Correct Expected: "XlXphants likX trXXs"
    run_strmapi_test("3. Character Replacement", "elephants like trees", map_replace_e, "XlXphants likX trXXs");

    // 4. Index-based shifting (map_add_index)
    // Input: "abcd"
    // Action: a+0, b+1, c+2, d+3
    // Correct Expected: "aceg"
    run_strmapi_test("4. Shift by Index", "abcd", map_add_index, "aceg");

    printf("--- All Tests Complete ---\n");

    return (EXIT_SUCCESS);
}