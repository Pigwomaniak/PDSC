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
    head->data = 1;

    printf("\n %d \n", head->data);


    return 0;
}