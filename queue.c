#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (q) {
        q->head = q->tail = NULL;
        q->size = 0;
    } else
        q = NULL;

    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    list_ele_t *temp = NULL, *temp_prev = NULL;
    // for (temp = q->head; temp && !temp->next; temp = temp->next) {
    //    free(temp->value);
    //}

    // need complete code...to be continuous
    while (q->head->next) {
        temp = q->head;

        // free from tail
        while (temp->next) {
            temp_prev = temp;
            temp = temp->next;
        }
        free(temp->value);
        free(temp->next);
        temp_prev->next = NULL;
    }

    free(q->head->value);
    free(q->head->next);

    /* Free queue structure */
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q)
        return false;

    list_ele_t *newh;
    char *str;
    /* TODO: What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    str = malloc(strlen(s) + 1);  // allocate space for sting

    if (!newh || !str) {
        if (newh)
            free(newh);
        if (str)
            free(str);

        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    // update tail of queue
    if (!q->tail && !q->head)
        q->tail = newh;

    newh->next = q->head;
    q->head = newh;

    // copy string and save point address to object
    int str_len = strlen(s);
    strncpy(str, s, str_len);
    *(str + str_len) = 0;
    newh->value = str;

    // update queu count
    q->size++;

    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q)
        return false;

    list_ele_t *newh;
    char *str;
    /* TODO: What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    str = malloc(sizeof(char) * strlen(s));  // allocate space for sting

    if (!newh || !str) {
        if (newh)
            free(newh);
        if (str)
            free(str);

        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    // update tail of queue
    if (!q->tail && !q->head)
        q->head = newh;

    newh->next = q->tail;
    q->tail = newh;

    // copy string and save point address to object
    strncpy(str, s, strlen(s));
    newh->value = str;

    // update queu count
    q->size++;

    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q)
        return false;

    // save q->head
    list_ele_t *temp = q->head;

    // assign new head
    q->head = q->head->next;

    bufsize = strlen(temp->value);
    strncpy(sp, temp->value, bufsize);
    *(sp + bufsize) = 0;

    // free old head mempry
    free(temp->value);
    free(temp);

    q->size--;

    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    return q->size;  // test
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
