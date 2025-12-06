#include "includes.h"

/**
 * Description:
 * Iterates through the list 'lst' and applies the function 'f' to the
 * content of each node. Creates a new list resulting from the successive
 * applications of the function 'f'. The 'del' function is used to delete
 * the content of a node if memory allocation fails.
 *
 * Return:
 * The new list.
 * NULL if the allocation fails.
 */
t_list *lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    t_list *new_list;
    t_list *new_node;
    void *new_content;

    if (!lst || !f || !del)
        return (NULL);

    new_list = NULL;

    while (lst)
    {
        new_content = f(lst->content);
        new_node = lstnew(new_content);
        if (!new_node)
        {
            del(new_content);
            lstclear(&new_list, del);

            return (NULL);
        }

        lstadd_back(&new_list, new_node);
        lst = lst->next;
    }

    return (new_list);
}