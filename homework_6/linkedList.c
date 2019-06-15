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
    push(&head, "A12");
    push(&head, "zh123");
    push(&head, "b1234");
    push(&head, "d12345");

    append(head, "koza");

    display(head);
/*
    char *poping = pop(&head);
    printf("%s", poping);
    free(poping);
    display(head);

    struct node *newHead = init();
    newHead = copy(head);
    printf("New List \n");
    display(newHead);
    destroy(newHead);


    reverse(&head);
    display(head);

    struct node** Max = findPreMax(&head);
    display(*Max);
*/

    sort(&head);
    display(head);

    destroy(head);
    return 0;
}

