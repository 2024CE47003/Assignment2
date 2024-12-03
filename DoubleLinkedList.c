/*
* Assignment 2
* Group Members: Stephen Cunningham - 23375841, Liam Walter, Liam O Meara, Gabor Kiss, Dylan Cullo
* Date: 25/11/2024
*
* Creates the double linked list
*/
#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinkedListHeader.h"

/**
 * @file DoubleLinkedList.c
 * @brief Implementation of a double linked list.
 *
 * - This file contains the functions required to create, manipulate, and delete a
 *   doubly linked list. It includes operations such as inserting, deleting,
 *   navigating through the list, and retrieving data from the nodes.
 * - The list structure consists of a head and tail node that serve as boundaries, and nodes
 *   in between store data and provide links to the previous and next nodes.
 *
 *
 * @date 25/11/2024
 */

 /**
  * @brief Creates a new double linked list.
  *
  * This function initializes an empty double linked list with a head and a tail node.
  * The head node's next pointer points to the tail, and the tail's previous pointer points to the head.
  * The current pointer is set to the head.
  *
  * @return A pointer to the newly created double linked list.
  */

DoubleLinkedList* createDoubleLinkedList() {
    // Variable refrencing the linked list
    DoubleLinkedList* list = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));

    //Creates the memory required for a node in the head and tail of the list
    list->head = (Node*)malloc(sizeof(Node));
    list->tail = (Node*)malloc(sizeof(Node));

    //Sets the node after the head to the tail
    list->head->next = list->tail;
    //Sets the node before the head to NULL
    list->head->prev = NULL;

    //Sets the node before the tail to head
    list->tail->prev = list->head;
    //Sets the node after the tail to NULL
    list->tail->next = NULL;
    // Initialises the current pointer to the head node
    list->current = list->head;
    // Return the newly created list
    return list;
}

/**
 * @brief Deletes the entire double linked list and frees memory.
 *
 * This function deallocates all memory used by the list, including nodes and the list structure itself.
 *
 * @param list The double linked list to be deleted.
 */

void deleteDoubleLinkedList(DoubleLinkedList* list) {
    if (list == NULL || list->head == NULL) {
        return NULL;  // If the list or head is NULL, return NULL.
    }

    Node* temp = list->head; // Start from the head node

    // Loop through the list, deleting each node
    while (temp != NULL) {
        Node* next = temp->next; // Store the next node
        free(temp);  // Free current node
        temp = next; // Move to the next node
    }

    // Now, free the list itself
    free(list);  // Free the list structure
}

/**
 * @brief Retrieves the data from the current node.
 *
 * This function returns the data stored in the node currently pointed to by the 'current' pointer.
 * If the current node is invalid, an error is reported and the program exits.
 *
 * @param list The double linked list from which data is to be retrieved.
 * @return The data stored in the current node.
 */

int getData(DoubleLinkedList* list) {
    if (list->current == NULL || list->current == list->head || list->current == list->tail) {
        fprintf(stderr, "Error: Current node is not a valid data node.\n");
        exit(1); // Or return an error code instead of exiting
    }
    return list->current->data;
}

/**
 * @brief Moves the current pointer to the next node.
 *
 * This function advances the current pointer to the next node in the list.
 * If the current node is the last valid node (tail), an error message is printed.
 *
 * @param list The double linked list.
 */

void goToNextNode(DoubleLinkedList* list) {
    if (list == NULL || list->current == NULL) {
        fprintf(stderr, "Error: Current node is NULL.\n");
        return;
    }
    if (list->current->next == NULL) {
        fprintf(stderr, "Error: Current node is not a valid data node.\n");
        return;
    }
    list->current = list->current->next;
}


/**
 * @brief Moves the current pointer to the previous node.
 *
 * This function moves the current pointer to the previous node in the list.
 * If the current node is at the head, an error message is printed.
 *
 * @param list The double linked list.
 */

void goToPreviousNode(DoubleLinkedList* list) {
    //Checks if the current node is at the head
    if (list->current != list->head) {
        //If it isnt move to the next node
        list->current = list->current->prev;
    }
    else {
        //Prints a standerd error informing the user they are at the tail of the list. Ends the function
        fprintf(stderr, "Error: You are at the head of the list. Cannot move past the head\n");

    }
}

/**
 * @brief Moves the current pointer to the head node.
 *
 * This function sets the current pointer to the head of the list.
 *
 * @param list The double linked list.
 */

void goToHead(DoubleLinkedList* list) {
    if (list == NULL || list->head == NULL) {
        fprintf(stderr, "Error: List or head is NULL.\n");
        return;
    }
    list->current = list->head;
}

/**
 * @brief Moves the current pointer to the tail node.
 *
 * This function sets the current pointer to the tail of the list.
 *
 * @param list The double linked list.
 */

void goToTail(DoubleLinkedList* list) {
    //Moves the current value to the tail
    list->current = list->tail;
}

/**
 * @brief Inserts a new node with the specified value after the current node.
 *
 * This function creates a new node and inserts it after the node currently pointed to by the current pointer.
 * If the current node is the tail, an error is reported.
 *
 * @param list The double linked list where the node is to be inserted.
 * @param value The data to be inserted in the new node.
 */

void insertAfter(DoubleLinkedList* list, int value) {
    //Checks if the current node is the tail
    if (list->current == list->tail) {
        //Prints a standerd error informing the user they are at the tail of the list. Ends the function
        fprintf(stderr, "Error: Cannot add an element after the tail\n");
        return;
    }

    //Makes a new Node
    Node* newNode = (Node*)malloc(sizeof(Node));
    //Sets the data in the new node to the desired value
    newNode->data = value;

    //Sets the addresses of the next and previous nodes for the newNode
    newNode->next = list->current->next;
    newNode->prev = list->current;

    //Fixes the old address of the two adjacent nodes. 
    list->current->next->prev = newNode;
    list->current->next = newNode;

    goToNextNode(list);
}

/**
 * @brief Inserts a new node with the specified value before the current node.
 *
 * This function creates a new node and inserts it before the node currently pointed to by the current pointer.
 * If the current node is the head, an error is reported.
 *
 * @param list The double linked list where the node is to be inserted.
 * @param value The data to be inserted in the new node.
 */

void insertBefore(DoubleLinkedList* list, int value) {
    //Checks if the current node is the tail
    if (list->current == list->head) {
        //Prints a standerd error informing the user they are at the head of the list. Ends the function
        fprintf(stderr, "Error: Cannot add an element before the head\n");
        return;
    }

    //Makes a new Node
    Node* newNode = (Node*)malloc(sizeof(Node));
    //Sets the data in the new node to the desired value
    newNode->data = value;

    //Sets the addresses of the next and previous nodes for the newNode
    newNode->prev = list->current->prev;
    newNode->next = list->current;

    //Fixes the old address of the two adjacent nodes. 
    list->current->prev->next = newNode;
    list->current->prev = newNode;

    goToPreviousNode(list);
}

/**
 * @brief Deletes the current node from the list.
 *
 * This function deletes the node currently pointed to by the current pointer.
 * If the current node is invalid, an error is printed.
 *
 * @param list The double linked list from which the node is to be deleted.
 */

void deleteCurrentNode(DoubleLinkedList* list) {
    if (list == NULL || list->current == NULL ||
        list->current == list->head || list->current == list->tail) {
        fprintf(stderr, "Error: Current node is not a valid data node.\n");
        return;
    }

    Node* toDelete = list->current;
    list->current = toDelete->next;

    if (toDelete->prev != NULL) {
        toDelete->prev->next = toDelete->next;
    }
    if (toDelete->next != NULL) {
        toDelete->next->prev = toDelete->prev;
    }

    free(toDelete);
}

/**
 * @brief Prints the contents of the double linked list.
 *
 * This function traverses the list from head to tail, printing the data of each node.
 *
 * @param list The double linked list to be printed.
 */

void printList(DoubleLinkedList* list) {
    Node* temp = list->head->next;
    printf("{");
    // Traverse the list and print each node's data
    while (temp != list->tail) {
        printf("%d", temp->data);
        if (temp->next != list->tail) {
            printf(", ");
        }
        temp = temp->next;
    }
    printf("}\n");
}




