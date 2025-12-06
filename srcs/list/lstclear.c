#include "includes.h"

/**
 * Description:
 * Deletes and safely frees the content and the node structure of the entire
 * list starting at '*lst' and all its successors. It uses the function 'del'
 * to free the content. Finally, it sets the external list pointer (*lst) to NULL
 * to avoid dangling pointers.
 *
 * Return:
 * None (void).
 */
void lstclear(t_list **lst, void (*del)(void *))
{
    t_list *current;
    t_list *next;

    if (!lst || !del)
        return;

    current = (*lst);
    while (current)
    {
        next = current->next;
        del(current->content);
        free(current);

        current = next;
    }
    *lst = NULL;
}