//
// Created by maciek on 11/06/19.
//
#include "linkedListFun.h"
#include <stddef.h>
#include <stdio.h>


int main(){
    struct node *head = init();
/*
    push(&head, "jak");
    push(&head, "to jest");
    push(&head, "być");
    push(&head, " Skrybą!! ");
    push(&head, "\n");
    */
    push(&head, "");

    printf("push after init \n");
    display(head);

    append(head, "koza");

    printf("after append \n");
    display(head);

    char *poping = pop(&head);
    printf(" pop contain: %s \n", poping);
    free(poping);
    display(head);

    printf("Copy of first list \n");
    struct node *newHead = init();
    newHead = copy(head);
    printf("New List \n");
    display(newHead);
    destroy(newHead);
    printf("Reversing head \n");
    reverse(&head);
    display(head);
    printf("sorting list \n");
    sort(&head);
    display(head);

    destroy(head);
    return 0;
}

