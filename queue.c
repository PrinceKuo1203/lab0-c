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
    if (!q || !q->head || !q->tail) {
        if (q)
            free(q);

        return;
    }

    /* TODO: How about freeing the list elements and the strings? */
    list_ele_t *now = NULL, *temp = NULL;
    for (now = q->head; now; now = temp) {
        temp = now->next;  // save next object before free
        free(now->value);
        free(now);
    }

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

    int str_len = strlen(s);

    /* TODO: What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    str = malloc(str_len + 1);  // allocate space for sting

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

    int str_len = strlen(s);

    /* TODO: What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    str = malloc(str_len + 1);  // allocate space for sting

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

    if (q->tail)
        q->tail->next = newh;

    q->tail = newh;
    q->tail->next = NULL;  // need update tail, otherwise default value
                           // "0x555555555555" will deference undefine object

    // copy string and save point address to object
    strncpy(str, s, str_len);
    *(str + str_len) = 0;
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
    if (!q || !q->size)
        return false;

    // save q->head
    list_ele_t *temp = q->head;

    // assign new head
    q->head = q->head->next;

    if (bufsize) {
        // copy value of remove object to target point.
        size_t temp_size = strlen(temp->value);
        if (bufsize < temp_size)
            temp_size = bufsize - 1;

        strncpy(sp, temp->value, temp_size);
        *(sp + temp_size) = 0;
    }

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
    if (!q || !q->head)
        return 0;

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
    if (!q || !q->size)
        return;

    // reserve
    list_ele_t *prev, *now, *next;

    // reserve elements
    // initial
    prev = NULL;       // next target of now object
    now = q->head;     // update now object
    next = now->next;  // update save next object

    for (; next;) {
        // redirection next point of object
        now->next = prev;

        prev = now;        // update next target of now object
        now = next;        // update now object
        next = now->next;  // update save next object
    }

    now->next = prev;
    // reverse elements done

    // reverse head and tail
    list_ele_t *temp = q->head;
    q->head = q->tail;
    q->tail = temp;
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
#if 0  // debug use
    list_ele_t *temp = q->head;
    printf("\nqueue list as below:\n");
    printf("queue->head = %c_%s\n", *q->head->value, q->head->value);
    for (; temp; temp = temp->next) {
        printf("%p = %c_%s\n", temp, *temp->value, temp->value);
    }
#endif

    if (!q || !q->size || q->size == 1)
        return;


    // separate list to half
    list_ele_t *half, *end;  // end = half->next to end
    for (half = end = q->head; end; end = end->next) {
#if 0  // debug use
        printf("half => %c_%s\n", *half->value, half->value);
        printf("end  => %c_%s\n", *end->value, end->value);
        printf("end->next  => %p\n", end->next);
#endif
        if (end->next) {
            end = end->next;
            if (!end->next)
                break;
            else
                half = half->next;
        } else
            break;
    }
#if 0  // debug use
    printf("half => %c_%s\n", *half->value, half->value);
    printf("end  => %c_%s\n", *end->value, end->value);
#endif

    if (end != q->head) {
        // create a queue_t to store another half queue
        queue_t half_q_obj, *half_q;  // point need deference real object
        half_q = &half_q_obj;

        // update half queue haed and tail
        q->tail = half;

        half_q->head = half->next;
        half_q->tail = end;

        half->next = NULL;  // 1st half queue finish
#if 0                       // debug use
        if (q) {
            printf("@1st half\n");
            temp = q->head;
            for (; temp; temp = temp->next) {
                printf("%p = %c_%s\n", temp, *temp->value, temp->value);
            }
        }

        if (half_q) {
            printf("@2nd half\n");
            temp = half_q->head;
            for (; temp; temp = temp->next) {
                printf("%p = %c_%s\n", temp, *temp->value, temp->value);
            }
        } else {
            printf("@2nd half is NULL\n");
        }
#endif
        q_sort(q);
        q_sort(half_q);


        // merge
        if (end == q->head)  // just one element, next element is NULL
            return;
        else {
            list_ele_t *temp_q = q->head, *temp_half_q = half_q->head,
                       *temp_head = NULL;

            while (temp_q && temp_half_q) {
                // printf("~~~ q->value = %x, half_q->value = %x\n",
                // *temp_q->value, *temp_half_q->value);
                if (*temp_q->value < *temp_half_q->value) {
                    if (!temp_head) {
                        q->head = temp_head = temp_q;
#if 0  // debug use
                        list_ele_t *temp = q->head;
                        printf("\n--queue merge_AAAAA as below:\n");
                        printf("--queue->head = %c_%s\n", *q->head->value,
                               q->head->value);
                        for (; temp; temp = temp->next) {
                            printf("--%p = %c_%s\n", temp, *temp->value,
                                   temp->value);
                        }

#endif

                    } else {
                        temp_head->next = temp_q;
                        temp_head = temp_head->next;
#if 0  // debug use
                        list_ele_t *temp = q->head;
                        printf("\n--queue merge_BBBBB as below:\n");
                        printf("--queue->head = %c_%s\n", *q->head->value,
                               q->head->value);
                        for (; temp; temp = temp->next) {
                            printf("--%p = %c_%s\n", temp, *temp->value,
                                   temp->value);
                        }
#endif
                    }
                    // compare next elements
                    if (temp_q->next)
                        temp_q = temp_q->next;
                    else {
                        temp_head->next = temp_half_q;
                        q->tail = half_q->tail;
#if 0  // debug use
                        list_ele_t *temp = q->head;
                        printf("\n--queue merge_CCCCC as below:\n");
                        printf("--queue->head = %c_%s\n", *q->head->value,
                               q->head->value);
                        for (; temp; temp = temp->next) {
                            printf("--%p = %c_%s\n", temp, *temp->value,
                                   temp->value);
                        }
#endif
                        break;
                    }

                } else {
                    if (!temp_head) {
                        q->head = temp_head = temp_half_q;
#if 0  // debug use
                        list_ele_t *temp = q->head;
                        printf("\n--queue merge_11111 as below:\n");
                        printf("--queue->head = %c_%s\n", *q->head->value,
                               q->head->value);
                        for (; temp; temp = temp->next) {
                            printf("--%p = %c_%s\n", temp, *temp->value,
                                   temp->value);
                        }
#endif

                    } else {
                        temp_head->next = temp_half_q;
                        temp_head = temp_head->next;
#if 0  // debug use
                        list_ele_t *temp = q->head;
                        printf("\n--queue merge_22222 as below:\n");
                        printf("--queue->head = %c_%s\n", *q->head->value,
                               q->head->value);
                        for (; temp; temp = temp->next) {
                            printf("--%p = %c_%s\n", temp, *temp->value,
                                   temp->value);
                        }
#endif
                    }
                    // compare next elements
                    if (temp_half_q->next)
                        temp_half_q = temp_half_q->next;
                    else {
                        temp_head->next = temp_q;
                        half_q->tail = q->tail;
#if 0  // debug use
                        list_ele_t *temp = q->head;
                        printf("\n--queue merge_33333 as below:\n");
                        printf("--queue->head = %c_%s\n", *q->head->value,
                               q->head->value);
                        for (; temp; temp = temp->next) {
                            printf("--%p = %c_%s\n", temp, *temp->value,
                                   temp->value);
                        }
#endif
                        break;
                    }
                }
            }
        }
    } else {
        // printf("next object is NULL!!!\n");
    }
}
