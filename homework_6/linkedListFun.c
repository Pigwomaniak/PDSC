//
// Created by maciek on 11/06/19.
//

#include "linkedListFun.h"


struct node* init(){
    return NULL;
}

int length(struct node *head){
    int len = 0;
    while (head){
        len++;
        head = head->next;
    }
    return len;
}

void display(struct node *head){
    printf("\n List contain:\n");
    while(head){
        printf("\t%s\n", head->data);
        head = head->next;
    }
}

void destroy(struct node *head){
    while (head){
        struct node *temp = head->next;
        free(head->data);
        free(head);
        head = temp;
    }
}


void append(struct node *head, char* input){\
	struct node *newNode = malloc(sizeof(struct node));
    if(!newNode){
        exit(0);
    }
    if(head){
        while(head->next){
            head = head->next;
        }
        head->next = newNode;
    } else{
        head = newNode;
    }
    (head)->data = malloc(sizeof(strlen(input)));
    if(!(head->data)){
        exit(0);
    }
    strcpy(head->data, input);
}

void push(struct node **head, char* input){
    struct node *newNode = malloc(sizeof(struct node));
    if(!newNode){
        exit(0);
    }
    newNode->next = *head;
    *head = newNode;
    (*head)->data = malloc(sizeof(strlen(input)));
    if(!((*head)->data)){
        exit(0);
    }
    strcpy((*head)->data, input);
}
/*
int pop(struct node **head){
	int out = (*head)->data;


	return out;
}
*/

