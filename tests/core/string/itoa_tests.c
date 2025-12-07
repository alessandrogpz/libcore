#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> // For INT_MAX and INT_MIN
#include "libcore.h"

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ====================================================================

void run_itoa_test(const char *test_name, int n, const char *expected)
{
    char *result = itoa(n);

    printf("--- Test: %s ---\n", test_name);
    printf("  Input: %d\n", n);

    if (result == NULL)
    {
        printf("  -> \033[31mFAIL\033[0m (Returned NULL)\n\n");
        return;
    }

    printf("  Expected: \"%s\"\n", expected);
    printf("  Result:   \"%s\"\n", result);

    if (strcmp(result, expected) == 0)
    {
        printf("  -> \033[32mPASS\033[0m\n\n");
    }
    else
    {
        printf("  -> \033[31mFAIL\033[0m (Content mismatch)\n\n");
    }

    free(result);
}

// ====================================================================
//                         MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running itoa Tests ---\n\n");

    // 1. Zero Handling
    run_itoa_test("1. Zero", 0, "0");

    // 2. Single Digits
    run_itoa_test("2. Single Digit Positive", 7, "7");
    run_itoa_test("3. Single Digit Negative", -7, "-7");

    // 3. Regular Numbers
    run_itoa_test("4. Regular Positive", 12345, "12345");
    run_itoa_test("5. Regular Negative", -9876, "-9876");

    // 4. Limits (Critical!)
    run_itoa_test("6. INT_MAX", INT_MAX, "2147483647");

    // This is the one that usually crashes naive implementations
    char min_str[12];
    sprintf(min_str, "%d", INT_MIN); // Dynamically get string for -2147483648
    run_itoa_test("7. INT_MIN", INT_MIN, min_str);

    printf("--- All Tests Complete ---\n");

    return (0);
}