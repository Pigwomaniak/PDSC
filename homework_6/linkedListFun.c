//
// Created by maciek on 11/06/19.
//

#include "linkedListFun.h"


struct node* init(){
    struct node *head = NULL;
    head = malloc(sizeof(struct node));
    if(!head){
        exit(0);
    }
    if(head){
        head->next = NULL;
    }

    return head;
}