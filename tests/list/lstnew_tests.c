#include <stdio.h>
#include <stdlib.h> // For malloc, free, NULL
#include "includes.h"

// -----------------------------------------------------------------------------
//                         TEST RUNNER
// -----------------------------------------------------------------------------

void run_lstnew_test(const char *test_name, void *input_content, int expected_null)
{
    t_list *new_node;
    int success = 1;

    printf("--- Test: %s ---\n", test_name);
    printf("  Input Content Address: %p\n", input_content);

    // Call the function being tested
    new_node = lstnew(input_content);

    // 1. Check Allocation (Must be non-NULL if input is non-NULL)
    if (new_node == NULL && expected_null == 0)
    {
        printf("  -> \033[31mFAIL (Allocation)\033[0m: Returned NULL unexpectedly.\n\n");
        return;
    }
    if (new_node == NULL)
    {
        printf("  -> \033[32mPASS\033[0m (Correctly returned NULL)\n\n");
        return;
    }

    // 2. Check Content Initialization
    if (new_node->content != input_content)
    {
        printf("  -> \033[31mFAIL (Content)\033[0m: Content pointer mismatch.\n");
        printf("     Expected: %p, Got: %p\n", input_content, new_node->content);
        success = 0;
    }

    // 3. Check Next Pointer (Must be NULL)
    if (new_node->next != NULL)
    {
        printf("  -> \033[31mFAIL (Next)\033[0m: 'next' pointer not NULL.\n");
        printf("     Got: %p\n", (void *)new_node->next);
        success = 0;
    }

    // Final Result
    if (success)
    {
        printf("  -> \033[32mPASS\033[0m: Node initialized correctly.\n\n");
    }
    else
    {
        printf("\n");
    }

    // Clean up allocated memory
    free(new_node);
}

// -----------------------------------------------------------------------------
//                         MAIN FUNCTION
// -----------------------------------------------------------------------------

int main(void)
{
    printf("--- Running lstnew Tests ---\n\n");

    // Sample data to store (to get valid addresses)
    int num = 42;
    char *str = "Hello World";

    // 1. Standard Case: Storing a pointer to an integer
    run_lstnew_test("1. Standard Integer Content", &num, 0);

    // 2. Standard Case: Storing a pointer to a string
    run_lstnew_test("2. Standard String Content", str, 0);

    // 3. Edge Case: Storing a NULL content pointer
    // The node should still be allocated, but content will be NULL.
    run_lstnew_test("3. NULL Content Pointer", NULL, 0);

    // 4. Large Allocation Test (Not done here, requires mocking malloc, but conceptually ready)

    printf("--- All Tests Complete ---\n");
    return (0);
}