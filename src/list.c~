#include "list.h"
#include "stdlib.h"
#include <stdio.h>

Cell *createCell(int x)
{
    Cell *c = NULL;
    c = (Cell*) malloc(sizeof(Cell));
    if (c == NULL)
        return c;
    c->x = x;
    c->next = NULL;
    return c;
}
void addCell(Cell **head, Cell *c)
{
    Cell *curr = *head;
    
    if (curr == NULL)
    {
        curr = c;
        return;
    }
    while (curr->next != NULL)
        curr = curr->next;
    curr->next = c;
}
void freeCell(Cell **c)
{
    free(*c);
}
void destroyCells(Cell **head)
{
    if ((*head)->next != NULL)
        destroyCells(&(*head)->next);
    freeCell(head);
}
void removeCell(Cell **head, int x)
{
    Cell *temp;
    Cell *toRemove;
    /* If the head is the cell to be removed... */
    if ((*head)->x == x)
    {
        temp = (*head)->next;
        freeCell(head);
        *head = temp;
    }
    for (temp = *head; temp->next != NULL; temp = temp->next)
    {
        if (temp->next->x == x)
        {
            toRemove = temp->next;
            temp->next = temp->next->next;
            freeCell(&toRemove);
            return;
        }
    }
}

Row *createRow(int y)
{
    Row *r = (Row*) malloc(sizeof(Row));
    r->y = y;
    r->next = NULL;
    r->cells = NULL;
    return r;
}
void addRow(Row **head, Row *r)
{
    Row *curr = *head;
    while (curr->next != NULL)
        curr = curr->next;
    curr->next = r;
}
void freeRow(Row **head)
{
    free(*head);
}
void destroyRows(Row **head)
{
    if ((*head)->next != NULL)
        destroyRows(&(*head)->next);
    freeRow(head);
}
void removeRow(Row **head, int y)
{
    Row *toRemove;
    Row *temp;
    /* If you are trying to remove the head node */
    if ((*head)->y == y)
    {
        toRemove = *head;
        temp = toRemove->next;
        freeRow(&toRemove);
        *head = temp;
        return;
    }
    /* Iterate through each row, and find one with a matching y-value */
    for (temp = *head; temp->next != NULL; temp = temp->next)
    {
        /* If the next one is the one to remove... */
        if (temp->next->y == y)
        {
            toRemove = temp->next;
            temp->next = temp->next->next;
            freeRow(&toRemove);
            return;
        }
    }
}





















