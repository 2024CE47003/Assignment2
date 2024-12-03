#ifndef ORDERED_SET_H
#define ORDERED_SET_H

#include "DoubleLinkedListHeader.h"

// Enumeration for operation statuses
typedef enum {
    NUMBER_ADDED,
    NUMBER_ALREADY_IN_SET,
    NUMBER_REMOVED,
    NUMBER_NOT_IN_SET,
    ALLOCATION_ERROR
} OperationStatus;

/*
Creates the structure of an Ordered Int Set
*/
typedef struct {
    DoubleLinkedList* list;  // The underlying double linked list for the set
    int count;  // Tracks the number of elements in the set
} orderedIntSet;

//FUNCTIONS

/*
Deletes the currently selected Node in the list
@param
list - The list whos node you want to delete
*/
void deleteCurrentNode(DoubleLinkedList* list);


/*
Creates an empty set with only the head tail and a counter set to zero
*/
orderedIntSet* createOrderedSet();

/*
Deletes a specified set and all memory associated with it
@param
set - The set you want to delete
*/
void deleteOrderedSet(orderedIntSet* set);

/*
Adds an element to the set in ascending order. Then moves the current node to the newley added node.
Will not add duplicate any nodes.
@param
set - The number set you want to add the node to
value - The value you want added to the set
*/
OperationStatus addElement(orderedIntSet* set, int value);

/*
Removes a specific value from a chosen set
@param
set - The set you want to remove a number from
value - The value you want to remove from the set
*/
OperationStatus removeElement(orderedIntSet* set, int value);

/*
Prints all values in a set
@param
set- The set you want to print
*/
void printToStdout(orderedIntSet* set);

/*
Finds any elements in common between two sets
@param
s1 - The first selected set
s2 - The second selected set
@return
All elements in common between the two sets
*/
orderedIntSet* setIntersection(orderedIntSet* s1, orderedIntSet* s2);

/*
Finds every element within two sets. Removes any duplicates
@param
s1 - The first selected set
s2 - The second selected set
@return
A new ordered set with no duplicates containing all elements from set 1 and set 2 
*/
orderedIntSet* setUnion(orderedIntSet* s1, orderedIntSet* s2);

/*
Finds which elements in set 1 are not in set 2. Both sets must be the same size
@param 
s1 - The set you want to check for unique values
s2 - The set you want to compare against
@return
Returns all values in s1 that are not in s2
*/
orderedIntSet* setDifference(orderedIntSet* s1, orderedIntSet* s2);

#endif