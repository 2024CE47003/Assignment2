// File Name: OrderedSetHeader.h
#pragma once
#ifndef ORDERED_SET_H
#define ORDERED_SET_H

#include "DoubleLinkedListHeader.h"

// Enumeration for return values
typedef enum {
    NUMBER_ADDED,
    NUMBER_ALREADY_IN_SET,
    NUMBER_REMOVED,
    NUMBER_NOT_IN_SET,
    ALLOCATION_ERROR
} ReturnValue;

// Creates the structure for the ordered integer set
typedef struct OrderedIntSet {
    DoubleLinkedList* list; // Pointer to the underlying double linked list
    int count;              // Number of elements in the set
} OrderedIntSet;

// Function prototypes
OrderedIntSet* createOrderedSet();
void deleteOrderedSet(OrderedIntSet* s);
#endif // ORDERED_SET_H
