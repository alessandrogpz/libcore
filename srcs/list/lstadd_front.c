#include "includes.h"

/**
 * Description:
 * Adds the node 'new' to the beginning (head) of the list pointed to by '*lst'.
 * It updates the list head pointer to point to the new node.
 *
 * Return:
 * None (void).
 */
void lstadd_front(t_list **lst, t_list *new)
{
    new->next = *lst;
    *lst = new;
}