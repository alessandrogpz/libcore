#include "includes.h"

/**
 * Description:
 * Allocates memory (using malloc(3)) and returns a new t_list node.
 * The node's 'content' is initialized with the given parameter, and 'next' is set to NULL.
 *
 * Return:
 * A pointer to the newly allocated t_list node, or NULL if allocation fails.
 */
t_list *lstnew(void *content)
{
    t_list *new_node;

    new_node = malloc(sizeof(t_list));
    if (!new_node)
        return NULL;

    new_node->content = content;
    new_node->next = NULL;

    return (new_node);
}