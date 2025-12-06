#include <stdio.h>
#include <stdlib.h> // For malloc, free, NULL
#include "includes.h"

// ====================================================================
//            LOCAL FUNCTION DEFINITIONS
// ====================================================================

// Helper for cleaning up test lists
void cleanup_list(t_list *head)
{
    t_list *current = head;
    t_list *next_node;
    while (current)
    {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

// -----------------------------------------------------------------------------
//                         TEST RUNNER
// -----------------------------------------------------------------------------

void run_size_test(const char *test_name, t_list *lst, int expected_size)
{
    int size = lstsize(lst);

    printf("--- Test: %s ---\n", test_name);
    printf("  Expected Size: %d\n", expected_size);
    printf("  lstsize Result: %d\n", size);

    if (size == expected_size)
    {
        printf("  -> \033[32mPASS\033[0m: Size calculation is correct.\n\n");
    }
    else
    {
        printf("  -> \033[31mFAIL (Mismatch)\033[0m: Expected %d, Got %d.\n\n", expected_size, size);
    }

    // Clean up memory allocated for the test list
    cleanup_list(lst);
}

// -----------------------------------------------------------------------------
//                         MAIN FUNCTION
// -----------------------------------------------------------------------------

int main(void)
{
    printf("--- Running lstsize Tests ---\n\n");

    t_list *head;

    // --- Test 1: Empty List (Size 0) ---
    run_size_test("1. Empty List (NULL)", NULL, 0);

    // --- Test 2: Single Node List (Size 1) ---
    head = lstnew("A");
    run_size_test("2. Single Node", head, 1);

    // --- Test 3: Standard List (Size 3) ---
    t_list *node1 = lstnew("C");
    t_list *node2 = lstnew("B");
    head = lstnew("A");
    head->next = node2;
    node2->next = node1; // List: A -> B -> C
    run_size_test("3. Standard List (3 Nodes)", head, 3);

    // --- Test 4: Larger List (Size 5) ---
    head = lstnew("E");
    head->next = lstnew("D");
    head->next->next = lstnew("C");
    head->next->next->next = lstnew("B");
    head->next->next->next->next = lstnew("A"); // List: E -> D -> C -> B -> A
    run_size_test("4. Larger List (5 Nodes)", head, 5);

    return (EXIT_SUCCESS);
}