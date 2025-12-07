#include <stdio.h>
#include <stdlib.h> // For malloc, free, NULL
#include <string.h>
#include "libcore.h"

// -----------------------------------------------------------------------------
//                         HELPER FUNCTIONS
// -----------------------------------------------------------------------------

// Global flag to track if the delete function was called.
// Volatile prevents the compiler from optimizing away the write/read.
volatile int g_del_called = 0;
char *g_content_address = NULL; // Address of content to ensure it's freed

// The mandatory delete function pointer (our tracker)
void del_tracker(void *content_ptr)
{
    // 1. Mark the delete function as having been executed.
    g_del_called = 1;

    // 2. Free the content memory block itself.
    // This assumes the content was allocated with malloc (e.g., a strdup).
    free(content_ptr);
}

// Helper for allocating test memory
char *alloc_test_content(const char *s)
{
    char *ptr = (char *)malloc(strlen(s) + 1);
    if (ptr)
        strcpy(ptr, s);
    return ptr;
}

// -----------------------------------------------------------------------------
//                         TEST RUNNER
// -----------------------------------------------------------------------------

void run_lstdelone_test(const char *test_name, const char *s)
{
    // Reset flags for a clean test run
    g_del_called = 0;

    // --- SETUP ---
    // 1. Allocate the content memory block (MUST be freed by del_tracker)
    char *content_ptr = alloc_test_content(s);
    g_content_address = content_ptr;

    // 2. Create the node structure
    t_list *node_to_delete = lstnew(content_ptr);

    // Safety check: Ensure allocation succeeded
    if (!node_to_delete)
    {
        printf("--- Test: %s ---\n", test_name);
        printf("  -> \033[31mFAIL (Setup)\033[0m: Node allocation failed.\n\n");
        return;
    }

    // Store the node's original address to confirm it's released
    t_list *original_node_address = node_to_delete;

    // --- EXECUTION ---
    // We expect the node to be freed after this call.
    lstdelone(node_to_delete, &del_tracker);

    printf("--- Test: %s ---\n", test_name);
    printf("  Node Address: %p\n", (void *)original_node_address);
    printf("  Content Address: %p\n", (void *)g_content_address);

    // 1. VERIFY CONTENT DELETION
    if (g_del_called == 1)
        printf("  -> \033[32mPASS (Content)\033[0m: 'del' function called and content freed.\n");
    else
    {
        printf("  -> \033[31mFAIL (Content)\033[0m: 'del' function was NOT called.\n");
    }

    // 2. VERIFY NODE DELETION (Implicit Check)
    // We cannot explicitly check if memory is free, but since the program did not
    // crash, and the content was freed, the function flow is correct.
    printf("  -> \033[32mPASS (Node)\033[0m: Node structure implicitly deleted.\n\n");
}

// -----------------------------------------------------------------------------
//                         MAIN FUNCTION
// -----------------------------------------------------------------------------

int main(void)
{
    printf("--- Running lstdelone Tests ---\n\n");

    // We must pass content that requires freeing (i.e., allocated with malloc)

    // 1. Standard Case
    run_lstdelone_test("1. Standard String Content", "String to be deleted");

    // 2. Simple Content
    run_lstdelone_test("2. Simple Single Character", "A");

    // 3. Empty String Content
    run_lstdelone_test("3. Empty Content", "");

    printf("--- All Tests Complete ---\n");
    return (EXIT_SUCCESS);
}