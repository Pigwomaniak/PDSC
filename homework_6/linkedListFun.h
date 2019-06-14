//
// Created by maciek on 11/06/19.
//

#ifndef PDSC_LINKEDLISTFUN_H
#define PDSC_LINKEDLISTFUN_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



typedef struct node{
    char* data;
    struct node *next;
} node;


struct node* init();
int length(struct node *head);
void display(struct node *head);
void destroy(struct node *head);
void push(struct node **head, char *input);
char* pop(struct node **head);
void append(struct node *head, char *input);
struct node* copy(struct node *head);
struct node* getNext(struct node **nodePtr);
void insertNode(struct node **nodePtr, struct node *insNode);
void reverse(struct node **head);

#endif //PDSC_LINKEDLISTFUN_H

