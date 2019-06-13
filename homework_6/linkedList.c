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

    display(head);

    append(head, "koza");

    display(head);

    //char *poping = pop(&head);
    //printf("%s", poping);
   // display(head);

    destroy(head);
    return 0;
}

