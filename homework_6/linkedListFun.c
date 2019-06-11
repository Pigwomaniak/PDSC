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

int length(struct node *head){
    int len = 0;
    while (head){
        len++;
        head = head->next;
    }
    return  len;
}
void display(struct node *head){
    printf("\n List contain:\n");
    while(head){
        printf("\t%d\n", head->data);
        head = head->next;
    }
}
void destroy(struct node *head){
    while (head){
        struct node *temp = head->next;
        free(head);
        head = temp;
    }