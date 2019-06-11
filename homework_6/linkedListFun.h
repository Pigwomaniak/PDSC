//
// Created by maciek on 11/06/19.
//

#ifndef PDSC_LINKEDLISTFUN_H
#define PDSC_LINKEDLISTFUN_H

#include <stddef.h>
#include <stdlib.h>


typedef struct node{
    int data;
    struct node *next;
};


struct node* init();
int length(struct node *head);
void display(struct node *head);
void destroy(struct node *head);
void push(struct node **head, int data);
int pop(struct node *head);
void append(struct node *head, int data);


#endif //PDSC_LINKEDLISTFUN_H
