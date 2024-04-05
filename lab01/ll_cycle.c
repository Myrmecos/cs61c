#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* your code here */
    node * tortoise = head;
    node * hare = head;
    if (head == NULL) {
        return 0;
    }
    while (1) {
        if (hare->next == NULL) {
            return 0;
        } else if (hare->next->next == NULL) {
            return 0;
        } else {
            hare = hare->next->next;
            tortoise = tortoise->next;
            if (hare == tortoise) {
                return 1;
            }
        }
    }
    return 0;
}