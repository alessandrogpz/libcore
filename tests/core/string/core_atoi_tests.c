#include <stdio.h>
#include <stdlib.h> // For standard atoi
#include <string.h> // For strcmp/strdup if needed
#include "includes.h"

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ====================================================================

// Function to run and display a single test result
void run_atoi_test(const char *test_name, const char *input)
{
    int core_result = core_atoi(input);
    int std_result = atoi(input);

    printf("--- Test: %s ---\n", test_name);
    printf("  Input: \"%s\"\n", input);
    printf("  core_atoi result:  %d\n", core_result);
    printf("  std_atoi result: %d\n", std_result);

    // Check equality
    if (core_result == std_result)
    {
        printf("  -> \033[32mPASS\033[0m\n\n");
    }
    else
    {
        printf("  -> \033[31mFAIL (Mismatch)\033[0m\n\n");
    }
}

// ====================================================================
//                         MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running core_atoi vs atoi Comparison Tests ---\n\n");

    // 1. Basic Numbers
    run_atoi_test("1. Basic Positive", "42");
    run_atoi_test("2. Basic Negative", "-42");
    run_atoi_test("3. Zero", "0");

    // 2. Whitespace Tests (The critical fix)
    // ASCII 32 (Space)
    run_atoi_test("4. Leading Spaces", "    42");
    // ASCII 9-13 (\t, \n, \v, \f, \r)
    run_atoi_test("5. Leading Tabs/Newlines", "\t\n\v\f\r 12345");

    // 3. Sign Tests
    run_atoi_test("6. Explicit Plus", "+42");
    run_atoi_test("7. Spaces + Sign", "   -42");

    // 4. Junk/Stopping Tests
    run_atoi_test("8. Numbers then Text", "42abc");
    run_atoi_test("9. Negative then Text", "-42 is the answer");
    run_atoi_test("10. Text then Numbers (Invalid)", "abc 42");

    // 5. Invalid Sign Usage
    run_atoi_test("11. Double Sign", "--42");
    run_atoi_test("12. Sign after number", "42-");
    run_atoi_test("13. Sign then space", "- 42");

    // 6. Edge Cases
    run_atoi_test("14. Empty String", "");
    run_atoi_test("15. Only Sign", "-");
    run_atoi_test("16. Max Int", "2147483647");
    run_atoi_test("17. Min Int", "-2147483648");

    printf("--- All Tests Complete ---\n");

    return (EXIT_SUCCESS);
}