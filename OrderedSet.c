#include <stdio.h>
#include <stdlib.h>
#include "OrderedSet.h"
#include "DoubleLinkedListHeader.h"


/**
 * @file OrderedSet.c
 * @brief Implementation of an ordered integer set using a double linked list.
 *
 * This file contains the implementation of an ordered integer set (orderedIntSet) data structure.
 * The ordered set maintains its elements in ascending order and provides various operations such as:
 * - Insertion of elements while maintaining order
 * - Removal of elements
 * - Set operations such as intersection, union, and difference
 * - Printing the set to standard output
 * - If numbers are repeated there will only be one output for that number
 * - Count of the number of elements is tracked
 *
 * The ordered set is backed by a double linked list, and the operations on the set interact with the underlying list to ensure that the elements remain ordered.
 *
 * Dependencies:
 * - DoubleLinkedList.h - Header file
 *
 * Functions:
 * - createOrderedSet() - Creates a new ordered set.
 * - deleteOrderedSet() - Deletes an ordered set and frees memory.
 * - addElement() - Adds an element to the ordered set.
 * - removeElement() - Removes an element from the ordered set.
 * - setIntersection() - Returns the intersection of two ordered sets.
 * - setUnion() - Returns the union of two ordered sets.
 * - setDifference() - Returns the difference of two ordered sets.
 * - printToStdout() - Prints the elements of the ordered set to standard output.
 *
 * @author Liam O'Mara, Liam Walter, Gabor Kiss, Stephen Cunningham, Dylan Culloo
 * @date December 2024
 */

 /**
  * @brief Creates a new ordered set.
  *
  * Allocates memory for an ordered set and initializes its linked list.
  *
  * @return A pointer to the newly created ordered set, or NULL if allocation fails.
  */

  // Function to create a new ordered set
orderedIntSet* createOrderedSet() {
    orderedIntSet* newSet = (orderedIntSet*)malloc(sizeof(orderedIntSet)); // Allocate memory for the ordered set
    if (newSet == NULL) {
        return NULL;  // If allocation fails return NULL
    }

    newSet->list = createDoubleLinkedList();  // Create the underlying linked list
    newSet->count = 0; //Initialise the count of elements to 0
    return newSet; // Return the pointer to the new ordered set
}


/**
 * @brief Deletes an ordered set.
 *
 * Frees the memory associated with the ordered set and its underlying linked list.
 *
 * @param set The ordered set to delete.
 */

 // Function to delete an ordered set
void deleteOrderedSet(orderedIntSet* set) {
    if (set != NULL) {
        deleteDoubleLinkedList(set->list);  // Delete the underlying linked list
        free(set);  // Free the ordered set structure
    }
}


/**
 * @brief Adds an element to the ordered set.
 *
 * Inserts an element into the ordered set, ensuring the order is maintained.
 * If the element is already in the set, it is not added.
 *
 * @param set The ordered set to which the element will be added.
 * @param elem The element to add.
 * @return An OperationStatus indicating success or failure.
 */

 // Function to add an element to the ordered set
OperationStatus addElement(orderedIntSet* set, int elem) {
    if (set == NULL) return ALLOCATION_ERROR; // If the set is NULL, return an allocation error

    // Start from the first data node (after the head)
    goToHead(set->list); // Move to the head of the linked list
    goToNextNode(set->list); // Move to the first data node

    while (set->list->current != set->list->tail) { // Traverse the list
        int currentData = getData(set->list); // Get the data at the current node
        if (currentData == elem) {
            return NUMBER_ALREADY_IN_SET;  // Element is already in the set
        }
        else if (currentData > elem) {
            // Insert the element before the current node
            insertBefore(set->list, elem);
            set->count++; // Increment the element count
            return NUMBER_ADDED;  // Element added at the correct position
        }
        goToNextNode(set->list); // Move to the next node in the list
    }

    // If the list traversal is complete and no insertion was made, insert at the tail
    insertBefore(set->list, elem);  // Insert the element before the tail (i.e., at the end of the list)
    set->count++; // Increment the element count
    return NUMBER_ADDED; // Return success indicating the element was added
}

/**
 * @brief Removes an element from the ordered set.
 *
 * Removes the specified element from the set if it exists.
 *
 * @param set The ordered set from which the element will be removed.
 * @param elem The element to remove.
 * @return An OperationStatus indicating success or failure.
 */

 // Function to remove an element from the ordered set
OperationStatus removeElement(orderedIntSet* set, int elem) {
    if (set == NULL) return ALLOCATION_ERROR; // If the set is NULL, return allocation error

    goToHead(set->list); // Start from the head of the list
	
    while (set->list->current->next != set->list->tail) { // Traverse the list
        goToNextNode(set->list); // Move to the next node in the list
        int currentData = getData(set->list); // Get the data at the current node
        if (currentData == elem) {
            deleteCurrentNode(set->list);  // Remove the current node
            set->count--; // Decrement the element count
            return NUMBER_REMOVED;  // Element removed
        }
       
    }

    return NUMBER_NOT_IN_SET;  // Element not found in the set
}


/**
 * @brief Finds the intersection of two ordered sets.
 *
 * Creates a new ordered set containing elements that are in both input sets.
 *
 * @param s1 The first ordered set.
 * @param s2 The second ordered set.
 * @return A pointer to a new ordered set containing the intersection of s1 and s2, or NULL if allocation fails.
 */

orderedIntSet* setIntersection(orderedIntSet* s1, orderedIntSet* s2) {
    if (s1 == NULL || s2 == NULL) return NULL; // If either set is NUll, return NULL

    orderedIntSet* resultSet = createOrderedSet(); // create a new ordered set for the result
    if (resultSet == NULL) return NULL;  // If allocation fails reurn NULL

    // Start from the first valid node in s1 (skip head)
    goToHead(s1->list);
    if (s1->list->current != s1->list->tail) {
        goToNextNode(s1->list);  // Skip head node if it's not pointing to the tail
    }

    while (s1->list->current != s1->list->tail) { // Traverse s1
        int currentData = getData(s1->list); // Get data from s1

        // Start from the first valid node in s2 (skip head)
        goToHead(s2->list);
        if (s2->list->current != s2->list->tail) {
            goToNextNode(s2->list);  // Skip head node if it's not pointing to the tail
        }

        while (s2->list->current != s2->list->tail) { // Traverse s2
            if (currentData == getData(s2->list)) { // Get data from s2
                addElement(resultSet, currentData);  // Add to result set if common element
                break; // Break inner loop once intersection is found
            }
            goToNextNode(s2->list); // Move to the next node in s2
        }
        goToNextNode(s1->list); // move to the next node in s1
    }

    return resultSet; // Return the resulting set
}

/**
 * @brief Finds the union of two ordered sets.
 *
 * Creates a new ordered set containing all elements from both input sets.
 * Duplicates are not added to the result.
 *
 * @param s1 The first ordered set.
 * @param s2 The second ordered set.
 * @return A pointer to a new ordered set containing the union of s1 and s2, or NULL if allocation fails.
 */

 // Function to get the union of two ordered sets
orderedIntSet* setUnion(orderedIntSet* s1, orderedIntSet* s2) {
    if (s1 == NULL || s2 == NULL) return NULL; // If either set is NULL return NULL

    orderedIntSet* resultSet = createOrderedSet(); // Create a new ordered set for the result
    if (resultSet == NULL) return NULL;  // Allocation failed

    goToHead(s1->list);
    while (s1->list->current->next != s1->list->tail) {
        goToNextNode(s1->list);
        addElement(resultSet, getData(s1->list));  // Add all elements from s1

    }

    goToHead(s2->list);
    while (s2->list->current->next != s2->list->tail) {
        goToNextNode(s2->list);
        addElement(resultSet, getData(s2->list));  // Add all elements from s2

    }

    return resultSet;
}

/**
 * @brief Finds the difference between two ordered sets (s1 - s2).
 *
 * Creates a new ordered set containing elements that are in s1 but not in s2.
 *
 * @param s1 The first ordered set.
 * @param s2 The second ordered set.
 * @return A pointer to a new ordered set containing the difference of s1 and s2, or NULL if allocation fails.
 */

orderedIntSet* setDifference(orderedIntSet* s1, orderedIntSet* s2) {
    if (s1 == NULL || s2 == NULL) return NULL;

    orderedIntSet* resultSet = createOrderedSet();
    if (resultSet == NULL) return NULL;  // Allocation failed

    // Traverse s1 and check if elements are in s2
    goToHead(s1->list);
    if (s1->list->current != s1->list->tail) {
        goToNextNode(s1->list);  // Skip head node if necessary
    }

    while (s1->list->current != s1->list->tail) {
        int currentData = getData(s1->list);
        int found = 0;

        // Traverse s2 to check for the element in s1
        goToHead(s2->list);
        if (s2->list->current != s2->list->tail) {
            goToNextNode(s2->list);  // Skip head node if necessary
        }

        while (s2->list->current != s2->list->tail) {
            if (currentData == getData(s2->list)) {
                found = 1;
                break;  // Element found in s2, no need to add to resultSet
            }
            goToNextNode(s2->list);
        }

        if (!found) {
            addElement(resultSet, currentData);  // Add to resultSet if element not found in s2
        }

        goToNextNode(s1->list);
    }

    return resultSet;
}

/**
 * @brief Prints the elements of an ordered set to stdout.
 *
 * Displays the elements of the ordered set in the format `{element1, element2, ...}`.
 *
 * @param set The ordered set to print.
 */

void printToStdout(orderedIntSet* set) {
    if (set == NULL || set->list == NULL) {
        printf("{}\n");
        return;
    }

    // Start from the first valid node after the head
    goToHead(set->list);
    if (set->list->current->next == set->list->tail) {
        printf("{}\n"); // List is empty (no valid nodes)
        return;
    }

    // Skip the head and start from the first data node
    set->list->current = set->list->current->next;

    printf("{");
    int first = 1;
    while (set->list->current != set->list->tail) {
        if (!first) {
            printf(", ");
        }
        printf("%d", getData(set->list)); // Print the data at the current node
        first = 0;
        goToNextNode(set->list); // Move to the next node
    }
    printf("}\n");
}




//// Main function for testing
//int main() {
//    orderedIntSet* set1 = createOrderedSet();
//    orderedIntSet* set2 = createOrderedSet();
//
//    if (!set1 || !set2) return 1;
//
//    addElement(set1, 10);
//    addElement(set1, 5);
//    addElement(set1, 15);
//
//    addElement(set2, 10);
//    addElement(set2, 20);
//    addElement(set2, 5);
//
//    printf("Set 1: ");
//    printToStdout(set1);
//
//    printf("Set 2: ");
//    printToStdout(set2);
//
//    orderedIntSet* intersection = setIntersection(set1, set2);
//    printf("Intersection: ");
//    printToStdout(intersection);
//
//    orderedIntSet* unionSet = setUnion(set1, set2);
//    printf("Union: ");
//    printToStdout(unionSet);
//
//    orderedIntSet* difference = setDifference(set1, set2);
//    printf("Difference (Set1 - Set2): ");
//    printToStdout(difference);
//
//    deleteOrderedSet(set1);
//    deleteOrderedSet(set2);
//    deleteOrderedSet(intersection);
//    deleteOrderedSet(unionSet);
//    deleteOrderedSet(difference);
//
//    return 0;
//}
