//
// Created by maciek on 11/06/19.
//
#include "linkedListFun.h"
#include <stddef.h>
#include <stdio.h>


int main(){
    struct node *head = NULL;
    struct node *end = NULL;
    struct node *current = NULL;

    head = init();
    head->data = 0;

    push(&head, 1);
    push(&head, 2);
    push(&head, 3);
    push(&head, 4);
    push(&head, 5);

    display(head);

    destroy(head);
    return 0;
}