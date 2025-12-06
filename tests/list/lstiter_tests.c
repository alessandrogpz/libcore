#include <stdio.h>
#include <stdlib.h> // For malloc, free, NULL
#include <ctype.h>  // For toupper
#include <string.h> // For strdup, strcmp
#include "includes.h"

// -----------------------------------------------------------------------------
//                         HELPER FUNCTIONS
// -----------------------------------------------------------------------------

// Helper to create a node (simplified lstnew)
t_list *create_node(void *content)
{
    t_list *new_node = malloc(sizeof(t_list));
    if (!new_node)
        return NULL;
    new_node->content = content;
    new_node->next = NULL;
    return new_node;
}

// THE ITERATOR FUNCTION 'f'
// This function takes a void pointer (which we know is a char*),
// and modifies the string to be all uppercase.
void to_upper_iter(void *content)
{
    char *s = (char *)content;
    int i = 0;
    while (s[i])
    {
        if (s[i] >= 'a' && s[i] <= 'z')
            s[i] -= 32; // Convert to uppercase
        i++;
    }
}

// -----------------------------------------------------------------------------
//                         TEST RUNNER
// -----------------------------------------------------------------------------

void run_lstiter_test(const char *test_name)
{
    printf("--- Test: %s ---\n", test_name);

    // 1. SETUP: Create a list [ "one" -> "two" -> "three" ]
    // We use strdup because we need mutable memory for the iterator to modify.
    t_list *n1 = create_node(strdup("one"));
    t_list *n2 = create_node(strdup("two"));
    t_list *n3 = create_node(strdup("three"));

    // Link them
    n1->next = n2;
    n2->next = n3;

    // 2. EXECUTE
    // Apply the uppercase function to every node
    lstiter(n1, &to_upper_iter);

    // 3. VERIFY
    int success = 1;
    if (strcmp((char *)n1->content, "ONE") != 0)
        success = 0;
    if (strcmp((char *)n2->content, "TWO") != 0)
        success = 0;
    if (strcmp((char *)n3->content, "THREE") != 0)
        success = 0;

    if (success)
    {
        printf("  -> \033[32mPASS\033[0m: Content modified correctly.\n");
        printf("     Nodes: %s -> %s -> %s\n", (char *)n1->content, (char *)n2->content, (char *)n3->content);
    }
    else
    {
        printf("  -> \033[31mFAIL\033[0m: Content mismatch.\n");
        printf("     Expected: ONE -> TWO -> THREE\n");
        printf("     Got:      %s -> %s -> %s\n", (char *)n1->content, (char *)n2->content, (char *)n3->content);
    }

    // Cleanup (Free string content AND nodes)
    free(n1->content);
    free(n1);
    free(n2->content);
    free(n2);
    free(n3->content);
    free(n3);
    printf("\n");
}

int main(void)
{
    printf("--- Running lstiter Tests ---\n\n");

    // Test 1: Standard list iteration
    run_lstiter_test("1. Uppercase String Iteration");

    // Test 2: Empty List (Should simply return without crashing)
    printf("--- Test: 2. Empty List ---\n");
    lstiter(NULL, &to_upper_iter);
    printf("  -> \033[32mPASS\033[0m: Did not crash on NULL list.\n");

    return (0);
}