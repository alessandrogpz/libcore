#include "libcore.h"

/**
 * Description:
 * Counts the total number of nodes in the linked list starting from 'lst'.
 * It traverses the list until the 'next' pointer becomes NULL.
 *
 * Return:
 * The integer count of the nodes in the list.
 */
int lstsize(t_list *lst)
{
    unsigned int len;

    len = 0;
    while (lst)
    {
        len++;
        lst = lst->next;
    }

    return (len);
}