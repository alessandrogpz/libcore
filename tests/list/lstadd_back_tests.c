#include <stdio.h>
#include <stdlib.h> // For malloc, free, NULL
#include "libcore.h"

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

void run_add_back_test(const char *test_name, t_list **list_ptr, t_list *new_node, int initial_size)
{
    t_list *old_last_ptr = lstlast(*list_ptr);

    printf("--- Test: %s ---\n", test_name);
    printf("  Initial Size: %d\n", initial_size);
    printf("  New Node Address: %p\n", (void *)new_node);

    // Call the function being tested
    lstadd_back(list_ptr, new_node);

    // 1. Check if the list head was updated (only necessary if list was NULL)
    if (initial_size == 0)
    {
        if (*list_ptr == new_node)
            printf("  -> \033[32mPASS (Head Init)\033[0m: New node correctly set as head (Empty List).\n");
        else
            printf("  -> \033[31mFAIL (Head Init)\033[0m: Head was not set to new node.\n");
    }
    // 2. Check the link update (If list was NOT NULL, the old last node must link to new_node)
    else
    {
        if (old_last_ptr->next == new_node)
            printf("  -> \033[32mPASS (Link Update)\033[0m: Old last node correctly links to new node.\n");
        else
            printf("  -> \033[31mFAIL (Link Update)\033[0m: Old last node links to %p instead of %p.\n", (void *)old_last_ptr->next, (void *)new_node);
    }

    // 3. Check new node's termination (Must be NULL)
    if (new_node->next == NULL)
        printf("  -> \033[32mPASS (Next NULL)\033[0m: New node is correctly terminated.\n\n");
    else
        printf("  -> \033[31mFAIL (Next NULL)\033[0m: New node's 'next' is not NULL.\n\n");
}

// -----------------------------------------------------------------------------
//                         MAIN FUNCTION
// -----------------------------------------------------------------------------

int main(void)
{
    printf("--- Running lstadd_back Tests ---\n\n");

    // --- SETUP DATA ---
    int data1 = 10;
    int data2 = 20;

    // --- TEST 1: ADDING TO AN EMPTY (NULL) LIST (Size 0) ---
    {
        t_list *node_new = lstnew(&data1);
        t_list *list_head = NULL;
        t_list **list_ptr = &list_head;

        run_add_back_test("1. Add to Empty (NULL) List", list_ptr, node_new, 0);

        // Clean up the 1-node list
        cleanup_list(*list_ptr);
    }

    // --- TEST 2: ADDING TO AN EXISTING LIST (Size 2) ---
    {
        // Setup initial list: A -> B
        t_list *node_b = lstnew(&data2);
        t_list *node_a = lstnew(&data1);
        node_a->next = node_b;

        // Node C is the new node to add
        t_list *node_new = lstnew(&data2);
        t_list **list_ptr = &node_a;

        run_add_back_test("2. Add to Existing List", list_ptr, node_new, 2);
        // Final list: A -> B -> C

        // Clean up the 3-node list
        cleanup_list(*list_ptr);
    }

    // --- TEST 3: ADDING TO A SINGLE-NODE LIST (Size 1) ---
    {
        // Setup initial list: A
        t_list *node_a = lstnew(&data1);

        // Node B is the new node to add
        t_list *node_new = lstnew(&data2);
        t_list **list_ptr = &node_a;

        run_add_back_test("3. Add to Single-Node List", list_ptr, node_new, 1);
        // Final list: A -> B

        // Clean up the 2-node list
        cleanup_list(*list_ptr);
    }

    printf("--- All Tests Complete ---\n");
    return (EXIT_SUCCESS);
}