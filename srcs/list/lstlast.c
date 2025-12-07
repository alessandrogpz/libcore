#include "libcore.h"

/**
 * Description:
 * Traverses the linked list starting at 'lst' and returns a pointer
 * to the last node. Returns NULL if the list is empty (lst is NULL).
 *
 * Return:
 * A pointer to the last t_list node in the sequence.
 */
t_list *lstlast(t_list *lst)
{
    if (!lst)
        return (NULL);

    while (lst->next)
        lst = lst->next;

    return (lst);
}