//
// Created by maciek on 11/06/19.
//
#include "linkedListFun.h"
#include <stddef.h>
#include <stdio.h>


int main(){
    struct node *head;
    head = init();

    push(&head, "1");
    push(&head, "12");
    push(&head, "123");
    push(&head, "1234");
    push(&head, "12345");

    append(head, "koza");

    display(head);

    char *poping = pop(&head);
    printf("%s", poping);
    free(poping);
    display(head);

    struct node *newHead = init();
    newHead = copy(head);
    printf("New List \n");
    display(newHead);



    destroy(newHead);
    destroy(head);
    return 0;
}

