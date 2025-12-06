#include "includes.h"

/**
 * Description:
 * Adds the node 'new' to the end (tail) of the list pointed to by '*lst'.
 * If the list is empty (NULL), the new node becomes the head of the list.
 *
 * Return:
 * None (void).
 */
void lstadd_back(t_list **lst, t_list *new)
{
    t_list *last_node;

    if (!lst || !new)
        return;

    if (*lst == NULL)
    {
        *lst = new;
        return;
    }

    last_node = lstlast(*lst);
    last_node->next = new;
}