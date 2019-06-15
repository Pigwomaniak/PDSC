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
        head = head->next;
    } else{
        head = newNode;
    }
    if(head){
        (head)->data = malloc(strlen(input) + 1);
        if(!(head->data)){
            exit(0);
        }
        strcpy(head->data, input);
        strncat(head->data, "\0", 1);
        head->next = NULL;
    }

}

void push(struct node **head, char* input){
    struct node *newNode = malloc(sizeof(struct node));
    if(!newNode){
        exit(0);
    }
    if(newNode){
        newNode->next = *head;
    }
    *head = newNode;
    (*head)->data = malloc(strlen(input) + 1);
    if(!((*head)->data)){
        exit(0);
    }
    strcpy((*head)->data, input);
    strncat((*head)->data, "\0", 1);
}

char* pop(struct node **head){
	char *out = (*head)->data;
    struct node *newHead = (*head)->next;
    /*
    free((*head)->data);
    char tempStr[strlen((*head)->data)] = strcpy(&tempStr, (*head)->data);
     return tempStr;
    */
    free(*head);
    *head = newHead;
	return out;
}

struct node* copy(struct node *head){
    struct node *newHead = NULL;
    while (head){
        push(&newHead, head->data);
        head = head->next;
    }
    reverse(&newHead);
    return newHead;
}

struct node* getNext(struct node **nodePtr){
    struct node *outNode = *nodePtr;
    if(outNode){
        *nodePtr = outNode->next;
        outNode->next = NULL;
    }
    return outNode;
}

void insertNode(struct node **nodePtr, struct node *insNode){
    if(insNode){
        insNode->next = *nodePtr;
        *nodePtr = insNode;
    }
}

void reverse(struct node **head){
    struct node *newHead = NULL;
    while (*head){
        insertNode(&newHead, getNext(head));
    }
    *head = newHead;
}
struct node** findPreMax(struct node** head){
    if(*head == NULL){
        return NULL;
    }
    struct node **maxNode = head;
    struct node **current = &((*head)->next);
    while (*current){
        if(strcmp((*current)->data, (*maxNode)->data) > 0){
            maxNode = current;
        }
        current = &((*current)->next);
    }
    return maxNode;
}
void sort(struct node** head){
    struct node *newHead = NULL;
    while (*head){
        insertNode(&newHead, getNext(findPreMax(head)));
    }
    *head = newHead;
}