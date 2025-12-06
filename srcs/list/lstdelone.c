#include "includes.h"

/**
 * Description:
 * Takes a single node ('lst') as a parameter and safely frees its content
 * using the provided deletion function ('del'). It then frees the node
 * structure itself. The 'next' node is NOT freed.
 *
 * Return:
 * None (void).
 */
void lstdelone(t_list *lst, void (*del)(void *))
{
    if (!lst || !del)
        return;

    del(lst->content);

    free(lst);
}
