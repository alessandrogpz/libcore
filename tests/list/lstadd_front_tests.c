#include <stdio.h>
#include <stdlib.h> // For malloc, free, NULL
#include "includes.h"

// -----------------------------------------------------------------------------
//                         MEMORY CLEANUP HELPER
// -----------------------------------------------------------------------------

// Safely traverses the list starting at *lst and frees all nodes.
void safe_list_free(t_list **lst)
{
    t_list *current;
    t_list *next_node;

    if (!lst || !*lst)
        return;

    current = *lst;
    while (current)
    {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    *lst = NULL; // Ensures the head pointer is set back to NULL
}

// -----------------------------------------------------------------------------
//                         TEST RUNNER
// -----------------------------------------------------------------------------

void run_add_front_test(const char *test_name, t_list **list_ptr, t_list *new_node)
{
    t_list *old_head_ptr = *list_ptr; // Store the original head address

    printf("--- Test: %s ---\n", test_name);
    printf("  Old Head Address: %p\n", (void *)old_head_ptr);
    printf("  New Node Address: %p\n", (void *)new_node);

    // Call the function being tested
    lstadd_front(list_ptr, new_node);

    // 1. Check if the list head was updated
    if (*list_ptr == new_node)
        printf("  -> \033[32mPASS (Head Update)\033[0m: List head now points to the new node.\n");
    else
        printf("  -> \033[31mFAIL (Head Update)\033[0m: List head pointer was NOT updated.\n");

    // 2. Check if the new node's 'next' pointer points to the old head
    if (new_node->next == old_head_ptr)
        printf("  -> \033[32mPASS (Next Pointer)\033[0m: New node correctly links to old head.\n\n");
    else
        printf("  -> \033[31mFAIL (Next Pointer)\033[0m: New node links to %p instead of old head.\n\n", (void *)new_node->next);
}

// -----------------------------------------------------------------------------
//                         MAIN FUNCTION
// -----------------------------------------------------------------------------

int main(void)
{
    printf("--- Running lstadd_front Tests ---\n\n");

    // --- SETUP DATA ---
    int data1 = 10;
    int data2 = 20;

    // --- TEST 1: ADDING TO AN EXISTING LIST (Standard Case) ---
    {
        // N1 (New Head), N2 (Old Head)
        t_list *node_new = lstnew(&data1);
        t_list *node_head = lstnew(&data2);

        // list_one is the address of the pointer 'node_head'
        t_list **list_one = &node_head;

        run_add_front_test("1. Add to Existing List", list_one, node_new);

        // SAFE CLEANUP: Traverse the list starting at the new head (*list_one)
        safe_list_free(list_one);
    }

    // --- TEST 2: ADDING TO A NULL LIST (List is initially empty) ---
    {
        t_list *node_new_two = lstnew(&data1);
        t_list *null_list = NULL;
        t_list **list_two = &null_list; // Points to a NULL pointer

        run_add_front_test("2. Add to Empty (NULL) List", list_two, node_new_two);

        // SAFE CLEANUP: Traverse the 1-node list
        safe_list_free(list_two);
    }

    printf("--- All Tests Complete ---\n");
    return (EXIT_SUCCESS);
}