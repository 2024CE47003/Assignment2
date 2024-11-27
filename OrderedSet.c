// File Name: OrderedSet.c
#include <stdio.h>
#include <stdlib.h> 
#include "OrderedSetHeader.h"
#include "DoubleLinkedListHeader.h"

// Function to create an ordered set
OrderedIntSet* createOrderedSet() {
    OrderedIntSet* set = (OrderedIntSet*)malloc(sizeof(OrderedIntSet));
    set->list = createDoubleLinkedList();
    set->count = 0;
    return set;
}

// Function to delete the ordered set
void deleteOrderedSet(OrderedIntSet* set) {
        deleteDoubleLinkedList(set->list);
        free(set);
}


