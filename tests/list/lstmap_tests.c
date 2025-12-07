#include <stdio.h>
#include <stdlib.h> // For malloc, free, NULL
#include <string.h> // For strdup, strcmp
#include <ctype.h>  // For toupper
#include "libcore.h"

// -----------------------------------------------------------------------------
//                         HELPER FUNCTIONS
// -----------------------------------------------------------------------------

// The 'del' function
void del_content(void *content)
{
    free(content);
}

// The 'f' function (Map)
// Takes a string, allocates a COPY, converts copy to Uppercase, returns it.
void *map_to_upper(void *content)
{
    char *original = (char *)content;
    char *new_str = strdup(original); // 1. Allocate new memory

    if (!new_str)
        return NULL;

    int i = 0;
    while (new_str[i])
    {
        // Convert to uppercase
        if (new_str[i] >= 'a' && new_str[i] <= 'z')
            new_str[i] -= 32;
        i++;
    }
    return (void *)new_str;
}

// Helper to print a list of strings
void print_list(t_list *lst)
{
    while (lst)
    {
        printf("[%s] -> ", (char *)lst->content);
        lst = lst->next;
    }
    printf("NULL\n");
}

// -----------------------------------------------------------------------------
//                         TEST RUNNER
// -----------------------------------------------------------------------------

int main(void)
{
    printf("--- Running lstmap Tests ---\n\n");

    // 1. SETUP: Create Original List [ "one" -> "two" -> "three" ]
    // We use strdup so the original list has alloc'd memory to free later.
    t_list *head = lstnew(strdup("one"));
    lstadd_back(&head, lstnew(strdup("two")));
    lstadd_back(&head, lstnew(strdup("three")));

    printf("Original List:\n  ");
    print_list(head);

    // 2. EXECUTE: Call lstmap
    t_list *new_list = lstmap(head, &map_to_upper, &del_content);

    printf("Mapped List (Upper):\n  ");
    print_list(new_list);

    // 3. VERIFICATION
    int success = 1;

    // Check if new list exists
    if (!new_list)
    {
        printf("  -> \033[31mFAIL\033[0m: New list is NULL.\n");
        success = 0;
    }
    else
    {
        // Check Content of Node 1
        if (strcmp((char *)new_list->content, "ONE") != 0)
            success = 0;
        // Check Content of Node 2
        if (new_list->next && strcmp((char *)new_list->next->content, "TWO") != 0)
            success = 0;
        // Check Pointer Independence (Deep Copy check)
        if (new_list->content == head->content)
        {
            printf("  -> \033[31mFAIL\033[0m: Shallow copy detected (pointers are same).\n");
            success = 0;
        }
    }

    if (success)
        printf("  -> \033[32mPASS\033[0m: New list created, content mapped, memory separate.\n");
    else
        printf("  -> \033[31mFAIL\033[0m: Content mismatch or structure error.\n");

    // 4. CLEANUP
    // We must be able to free BOTH lists independently.
    // If they shared pointers, this would double-free and crash.
    lstclear(&head, &del_content);
    lstclear(&new_list, &del_content);

    printf("\n--- Cleanup successful (No Double Free) ---\n");

    return (0);
}