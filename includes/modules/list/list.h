#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct s_list
{
    void *content;
    struct s_list *next;
} t_list;

// --------------- Linked List Manipulation ---------------

// Creation

t_list *lstnew(void *content);

// Information

int lstsize(t_list *lst);
t_list *lstlast(t_list *lst);

// Insertion

void lstadd_front(t_list **lst, t_list *new);
void lstadd_back(t_list **lst, t_list *new);

// Deletion

void lstdelone(t_list *lst, void (*del)(void *));
void lstclear(t_list **lst, void (*del)(void *));

// Iteration / Mapping

void lstiter(t_list *lst, void (*f)(void *));
t_list *lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif