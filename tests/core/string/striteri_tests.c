#include <stdio.h>
#include <stdlib.h> // For NULL, EXIT_SUCCESS
#include <string.h> // For strcmp
#include "libcore.h"

// ====================================================================
//            LOCAL HELPER FUNCTIONS (FOR TESTING)
// ====================================================================

// --- Modification Function: Transforms based on index ---
// If the index is even, the character is capitalized.
// If the index is odd, the character is set to 'X'.
void mod_transform(unsigned int i, char *c)
{
    if (i % 2 == 0)
    {
        // If it's an even index and a lowercase letter, capitalize it.
        if (*c >= 'a' && *c <= 'z')
            *c -= 32; // Standard ASCII conversion to uppercase
    }
    else
    {
        // For odd indices, replace the character with 'X'.
        *c = 'X';
    }
}

// --- Modification Function: Nullifies first character if index is large ---
// Used to test function flow control without affecting all characters.
void mod_null_test(unsigned int i, char *c)
{
    (void)c; // Suppress unused warning
    if (i == 0)
    {
        // This is a minimal function just to be called.
    }
}

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ====================================================================

// Function to run and display a single test result
void run_striteri_test(const char *test_name, char *s, void (*f)(unsigned int, char *), const char *expected)
{
    // The input string needs to be duplicated because striteri modifies it in place.
    char *test_str = strdup(s);

    printf("--- Test: %s ---\n", test_name);
    printf("  Initial String: \"%s\"\n", test_str);

    // CALL THE FUNCTION
    striteri(test_str, f);

    printf("  Expected: \"%s\"\n", expected);
    printf("  Result:   \"%s\"\n", test_str);

    // --- 1. Check Content (Must match exactly) ---
    if (strcmp(test_str, expected) == 0)
    {
        printf("  -> \033[32mPASS\033[0m: In-place modification successful.\n\n");
    }
    else
    {
        printf("  -> \033[31mFAIL (Mismatch)\033[0m\n\n");
    }

    // Clean up memory
    free(test_str);
}

// ====================================================================
//                         MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running striteri In-Place Modification Tests ---\n\n");

    // 1. Basic Transformation Test (mod_transform)
    // Input: "abcde fghij"
    // Index: 0 1 2 3 4 5 6 7 8 9 0
    // Result: A X C X E X G X I X J
    run_striteri_test("1. Basic In-Place Mod", "abcde fghij", mod_transform, "AXCXEXFXHXJ");

    // 2. Already Uppercase/Symbol Test (Should leave uppercase/symbols alone on even indices)
    // Input: "4L5M6N7"
    // Index: 0123456
    // Result: 4 X 5 X 6 X 7 (L, M, N are skipped because logic only targets lowercase)
    run_striteri_test("2. Mixed Case/Symbols", "4L5M6N7", mod_transform, "4X5X6X7");

    // 3. Empty String Test (Should do nothing and return immediately)
    run_striteri_test("3. Empty String", "", mod_transform, "");

    // 4. String with only one character
    run_striteri_test("4. Single Character", "z", mod_transform, "Z");

    // 5. Test flow control and loop termination (mod_null_test)
    // Should run successfully without changing content.
    run_striteri_test("5. Flow Control", "flow", mod_null_test, "flow");

    printf("--- All Tests Complete ---\n");

    return (EXIT_SUCCESS);
}