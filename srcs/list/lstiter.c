#include "libcore.h"

/**
 * Description:
 * Iterates the list 'lst' and applies the function 'f' on the content of
 * each node.
 *
 * Return:
 * None (void).
 */
void lstiter(t_list *lst, void (*f)(void *))
{
    if (!lst || !f)
        return;

    while (lst)
    {
        f(lst->content);
        lst = lst->next;
    }
}