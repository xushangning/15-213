/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// #include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = (queue_t *) malloc(sizeof(queue_t));
    if (q) {
        q->head = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q) {
        for (list_ele_t *p = q->head, *next; p; p = next) {
            next = p->next;
            free(p->value);
            free(p);
        }
        /* Free queue structure */
        free(q);
    }
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL)
        return false;

    list_ele_t *newh = (list_ele_t *) malloc(sizeof(list_ele_t));
    if (newh == NULL) 
        return false;

    newh->value = (char *) calloc(strlen(s) + 1, sizeof *s);
    if (newh->value) {
        strcpy(newh->value, s);
        if (q->head == NULL)
            q->tail = newh;
        // change queue head
        newh->next = q->head;
        q->head = newh;
        ++q->size;
    }
    else {
        free(newh);     // free allocated list_ele_t
        return false;
    }
    return true;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (q) {
        list_ele_t *newt = (list_ele_t *) malloc(sizeof(list_ele_t));
        if (newt) {
            newt->value = (char *) calloc(strlen(s) + 1, sizeof *s);
            if (newt->value) {
                strcpy(newt->value, s);
                newt->next = NULL;
                if (q->head)    // if queue is not empty i.e. tail is set
                    q->tail = q->tail->next = newt;
                else
                    q->head = q->tail = newt;
                ++q->size;
                return true;
            }
            // allocation failed
            free(newt);
        }
    }
    return false;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL || q->head == NULL)
        return false;

    list_ele_t *temp_head = q->head;
    if (sp) {
        strncpy(sp, temp_head->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    free(temp_head->value);
    q->head = q->head->next;
    free(temp_head);
    --q->size;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return q ? q->size : 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    // queue pointer is null or queue has no more than one element
    if (q == NULL || q->size <= 1)
        return;
    q->tail = q->head;
    list_ele_t *p = q->head->next; 
    q->head->next = NULL;
    for (list_ele_t *next; p; p = next) {
        next = p->next;
        p->next = q->head;
        q->head = p;
    }
}
