//
// Created by maciek on 11/06/19.
//

#include "linkedListTests.h"
#include "linkedListFun.h"

int testInit(){
    struct node *head = NULL;
    struct node *end = NULL;
    struct node *current = NULL;

    head = init();
    head->data = 1;


    return head->data;
}
