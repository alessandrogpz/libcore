#include <stdio.h>
#include <stdlib.h> // For malloc, free, NULL
#include "includes.h"

// -----------------------------------------------------------------------------
//                         LOCAL FUNCTIONS
// -----------------------------------------------------------------------------

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

void run_lstlast_test(const char *test_name, t_list *lst, t_list *expected_node)
{
    t_list *last = lstlast(lst);

    printf("--- Test: %s ---\n", test_name);
    printf("  Expected Last Address: %p\n", (void *)expected_node);
    printf("  lstlast Result: %p\n", (void *)last);

    if (last == expected_node)
    {
        printf("  -> \033[32mPASS\033[0m: Correct last node found.\n\n");
    }
    else
    {
        printf("  -> \033[31mFAIL (Mismatch)\033[0m: Returned wrong node.\n\n");
    }
}

// -----------------------------------------------------------------------------
//                         MAIN FUNCTION
// -----------------------------------------------------------------------------

int main(void)
{
    printf("--- Running lstlast Tests ---\n\n");

    // --- Test 1: Empty List (Expected: NULL) ---
    run_lstlast_test("1. Empty List", NULL, NULL);

    // --- Test 2: Single Node List (Expected: Head) ---
    t_list *head_single = lstnew("Single");
    run_lstlast_test("2. Single Node", head_single, head_single);
    cleanup_list(head_single);

    // --- Test 3: Standard List (Size 3) ---
    t_list *node_last = lstnew("C"); // Expected last node
    t_list *node_mid = lstnew("B");
    t_list *head_std = lstnew("A");

    head_std->next = node_mid;
    node_mid->next = node_last; // List: A -> B -> C
    run_lstlast_test("3. Standard List (3 Nodes)", head_std, node_last);
    cleanup_list(head_std);

    // --- Test 4: Long List (Expected: Last Node) ---
    t_list *node_long_last = lstnew("Tail"); // Expected last node
    t_list *head_long = lstnew("Head");
    head_long->next = lstnew("Mid1");
    head_long->next->next = lstnew("Mid2");
    head_long->next->next->next = node_long_last;
    run_lstlast_test("4. Long List", head_long, node_long_last);
    cleanup_list(head_long);

    return (EXIT_SUCCESS);
}