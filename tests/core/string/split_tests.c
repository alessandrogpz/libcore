#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libcore.h"

// -----------------------------------------------------------------------------
//                         HELPER FUNCTIONS
// -----------------------------------------------------------------------------

// Helper to free the array returned by split
void free_split_result(char **result)
{
    size_t i = 0;
    if (!result)
        return;
    while (result[i] != NULL)
    {
        free(result[i]);
        i++;
    }
    free(result);
}

// Function to print a string array (for debugging failure)
void print_array(char **arr)
{
    size_t i = 0;
    printf("    Got: {");
    if (arr)
    {
        while (arr[i])
        {
            printf("\"%s\", ", arr[i]);
            i++;
        }
        printf("NULL}\n");
    }
    else
        printf("NULL}\n");
}

// -----------------------------------------------------------------------------
//                         TEST RUNNER
// -----------------------------------------------------------------------------

void run_split_test(const char *test_name, const char *s, char c, const char **expected)
{
    char **result;
    size_t i;
    int success;

    printf("--- Test: %s (Delimiter: '%c') ---\n", test_name, c);
    printf("  Input: \"%s\"\n", s);

    // CALL THE FUNCTION
    result = split(s, c);

    // 1. Check Allocation Failure
    if (result == NULL && expected == NULL)
    {
        printf("  -> \033[32mPASS\033[0m (Correctly returned NULL)\n\n");
        return;
    }
    if (result == NULL && expected != NULL)
    {
        printf("  -> \033[31mFAIL\033[0m (Returned NULL unexpectedly)\n\n");
        return;
    }

    // 2. Check Content
    i = 0;
    success = 1;
    while (expected[i] != NULL || result[i] != NULL)
    {
        // Check for premature end of one array
        if (expected[i] == NULL || result[i] == NULL)
        {
            success = 0;
            break;
        }
        // Check string content
        if (strcmp(expected[i], result[i]) != 0)
        {
            success = 0;
            break;
        }
        i++;
    }

    if (success)
    {
        printf("  -> \033[32mPASS\033[0m (Content matches)\n\n");
    }
    else
    {
        printf("  -> \033[31mFAIL\033[0m (Mismatch at index %zu)\n", i);
        printf("    Expected: {");
        for (size_t j = 0; expected[j]; j++)
            printf("\"%s\", ", expected[j]);
        printf("NULL}\n");
        print_array(result);
        printf("\n");
    }

    free_split_result(result);
}

// -----------------------------------------------------------------------------
//                         MAIN
// -----------------------------------------------------------------------------

int main(void)
{
    printf("--- Running split Black-Box Tests ---\n\n");

    // 1. Basic Split
    const char *exp1[] = {"one", "two", "three", NULL};
    run_split_test("1. Basic Comma", "one,two,three", ',', exp1);

    // 2. Multiple Delimiters
    const char *exp2[] = {"Hello", "World", NULL};
    run_split_test("2. Multiple Delimiters", "Hello,,,World", ',', exp2);

    // 3. Leading/Trailing Delimiters
    const char *exp3[] = {"Word", "Word", NULL};
    run_split_test("3. Leading/Trailing", "--Word--Word--", '-', exp3);

    // 4. All Delimiters (Should return empty array: {NULL})
    const char *exp4[] = {NULL};
    run_split_test("4. Only Delimiters", ".......", '.', exp4);

    // 5. Empty String (Should return empty array: {NULL})
    const char *exp5[] = {NULL};
    run_split_test("5. Empty Input", "", ' ', exp5);

    // 6. No Delimiters in String
    const char *exp6[] = {"SingleWord", NULL};
    run_split_test("6. No Delimiters", "SingleWord", ',', exp6);

    // 7. Space Delimiter
    const char *exp7[] = {"Lorem", "ipsum", "dolor", NULL};
    run_split_test("7. Space Delimiter", "Lorem ipsum dolor", ' ', exp7);

    printf("--- All Tests Complete ---\n");
    return (0);
}