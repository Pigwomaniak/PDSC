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



#endif //PDSC_LINKEDLISTFUN_H
