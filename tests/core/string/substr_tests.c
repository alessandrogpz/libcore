#include <stdio.h>
#include <stdlib.h> // For standard malloc, free, NULL
#include <string.h> // For standard strcmp, memcmp
#include "libcore.h"

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ====================================================================

// Function to run and display a single test result
void run_substr_test(const char *test_name, const char *s, unsigned int start, size_t len, const char *expected_content)
{
    char *sub = substr(s, start, len);

    printf("--- Test: %s ---\n", test_name);
    printf("  Input: \"%s\" (Len: %zu)\n", s, core_strlen(s));
    printf("  Start: %u, Request Len: %zu\n", start, len);
    printf("  Expected: \"%s\"\n", (expected_content == NULL ? "NULL (Allocation Fail or Invalid Start)" : expected_content));

    // --- 1. Check NULL Return (Failure Cases) ---
    if (expected_content == NULL)
    {
        if (sub == NULL)
            printf("  -> \033[32mPASS\033[0m (Correctly returned NULL)\n\n");
        else
            printf("  -> \033[31mFAIL\033[0m (Expected NULL, got address %p)\n\n", (void *)sub);
        return;
    }

    // If expected is not NULL, sub must not be NULL
    if (sub == NULL)
    {
        printf("  -> \033[31mFAIL\033[0m (Expected content, got NULL)\n\n");
        return;
    }

    // --- 2. Check Content ---
    if (strcmp(expected_content, sub) == 0)
        printf("  -> Content Check: \033[32mPASS\033[0m\n");
    else
        printf("  -> Content Check: \033[31mFAIL\033[0m (Got: \"%s\")\n", sub);

    // --- 3. Check Length/Termination ---
    if (strlen(sub) == strlen(expected_content))
        printf("  -> Length Check: \033[32mPASS\033[0m (Len: %zu)\n\n", strlen(sub));
    else
        printf("  -> Length Check: \033[31mFAIL\033[0m (Expected Len: %zu, Got Len: %zu)\n\n", strlen(expected_content), strlen(sub));

    // Clean up allocated memory
    free(sub);
}

// ====================================================================
//                         MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running substr Comparison Tests ---\n\n");

    const char *long_str = "0123456789ABCDEF"; // Length 16

    // 1. Basic Substring
    run_substr_test("1. Basic Middle Substring", long_str, 5, 5, "56789"); // Start at '5', length 5

    // 2. Full Copy
    run_substr_test("2. Full String Copy", long_str, 0, 16, "0123456789ABCDEF"); // Start at 0, length 16

    // 3. Truncation Required (Safety Check)
    // String length is 16. Start at 10 ('A'). Only 6 chars remain. Request 10.
    // Expected result must be truncated to 6 chars ("ABCDEF").
    run_substr_test("3. Safety Truncation", long_str, 10, 10, "ABCDEF");

    // 4. Start at the End (Last Character)
    run_substr_test("4. Start at Last Char", long_str, 15, 1, "F");

    // 5. Zero Length Request
    run_substr_test("5. Zero Length", long_str, 5, 0, ""); // Start at 5, request 0 length (should be "\0")

    // 6. Invalid Start Index (Must return NULL)
    // Start at 17, which is past the string end (length 16).
    run_substr_test("6. Invalid Start", long_str, 17, 5, "");

    // 7. Empty String Input
    run_substr_test("7. Empty String Input", "", 0, 5, ""); // Start 0, request 5, gives ""

    // 8. Edge Case: Requesting more than INT_MAX (Testing robustness of size_t len)
    // Check if the request for a massive length still correctly truncates to available length.
    run_substr_test("8. Huge Requested Len", long_str, 1, 99999, "123456789ABCDEF");

    // 9. Start Index > String Length (Must return empty string "", NOT NULL)
    // String length 16. Start at 400.
    run_substr_test("9. Start > Len (Safety)", long_str, 400, 20, "");

    printf("--- All Tests Complete ---\n");

    return (EXIT_SUCCESS);
}