#include <stdio.h>
#include <stdlib.h> // For malloc, free, NULL
#include <string.h> // For strlen
#include "libcore.h"

// -----------------------------------------------------------------------------
//                         HELPER FUNCTIONS
// -----------------------------------------------------------------------------

// Global counter to track how many times the delete function was called.
volatile int g_deletion_count = 0;
volatile int g_list_size = 0;

// The mandatory delete function pointer (our tracker)
void del_tracker(void *content_ptr)
{
    if (content_ptr)
    {
        free(content_ptr); // Free the content block itself
    }
    g_deletion_count++; // Increment global counter
}

// Helper to create a new node (for test setup only)
t_list *lstnew_test(void *content)
{
    t_list *new_node = malloc(sizeof(t_list));
    if (!new_node)
        return NULL;

    new_node->content = content;
    new_node->next = NULL;
    return new_node;
}

// Helper to build a list of N nodes for testing
t_list **build_test_list(int count)
{
    t_list **lst_ptr = (t_list **)malloc(sizeof(t_list *));
    if (!lst_ptr)
        return NULL;

    *lst_ptr = NULL;
    g_list_size = count;

    // Add nodes to the front
    for (int i = 0; i < count; i++)
    {
        // Allocate content dynamically so del_tracker can free it.
        // FIX: Increased size to 16 to safely hold "Data" + MAX_INT string.
        char *content = malloc(sizeof(char) * 16);
        if (!content)
            break;

        sprintf(content, "Data%d", i); // Store unique data

        t_list *new_node = lstnew_test(content);
        if (!new_node)
            break;

        // lstadd_front logic (simplified for test setup)
        new_node->next = *lst_ptr;
        *lst_ptr = new_node;
    }
    return lst_ptr;
}

// -----------------------------------------------------------------------------
//                         TEST RUNNER
// -----------------------------------------------------------------------------

void run_lstclear_test(const char *test_name, int node_count)
{
    t_list **list_ptr;

    printf("--- Test: %s (Nodes: %d) ---\n", test_name, node_count);

    // Reset global flags
    g_deletion_count = 0;

    // 1. SETUP LIST
    list_ptr = build_test_list(node_count);
    if (!list_ptr)
    {
        printf("  -> \033[31mFAIL (Setup)\033[0m: Failed to allocate initial list.\n\n");
        return;
    }

    // 2. EXECUTE FUNCTION
    lstclear(list_ptr, &del_tracker);

    // 3. VERIFICATION

    // A. Check Final Head Pointer
    if (*list_ptr != NULL)
    {
        printf("  -> \033[31mFAIL (Head)\033[0m: Head pointer was NOT set to NULL.\n");
    }
    else
    {
        printf("  -> \033[32mPASS (Head)\033[0m: External head pointer set to NULL.\n");
    }

    // B. Check Deletion Count
    if (g_deletion_count == node_count)
    {
        printf("  -> \033[32mPASS (Deletion)\033[0m: All %d nodes were freed.\n", node_count);
    }
    else
    {
        printf("  -> \033[31mFAIL (Deletion)\033[0m: Expected %d frees, got %d.\n", node_count, g_deletion_count);
    }

    // C. Check Memory State (FIXED LOGIC)
    // We confirm that the pointer is NULL, regardless of whether it started as NULL.
    if (*list_ptr == NULL)
    {
        printf("  -> \033[32mPASS (Memory)\033[0m: List pointer is NULL (Success).\n\n");
    }
    else
    {
        printf("  -> \033[31mFAIL (Memory)\033[0m: List pointer is NOT NULL.\n\n");
    }

    // Free the pointer to the head pointer storage itself
    free(list_ptr);
}

// -----------------------------------------------------------------------------
//                         MAIN FUNCTION
// -----------------------------------------------------------------------------

int main(void)
{
    printf("--- Running lstclear Tests ---\n\n");

    // 1. Empty List (Should return immediately, set NULL, count 0)
    run_lstclear_test("1. Empty List (NULL)", 0);

    // 2. Single Node List
    run_lstclear_test("2. Single Node", 1);

    // 3. Standard 5-Node List
    run_lstclear_test("3. Standard 5-Node List", 5);

    // 4. Larger List
    run_lstclear_test("4. Larger 10-Node List", 10);

    return (EXIT_SUCCESS);
}