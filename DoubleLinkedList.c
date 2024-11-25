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
    //Sets the node after the ail to NULL
    list->tail->next = NULL;

    list->current = list->head;

    return list;
}

void deleteDoubleLinkedList(DoubleLinkedList* list) {
    //Makes a temp pointer at the head of the node. This pointer traverses and deletes each node
    Node* temp = list->head;
    //Runs until the temp pointer becomes NULL
    while (temp != NULL) {
        //Creates another node to store the address of the next node in the list
        Node* next = temp->next;
        //Frees up the memory at the current address
        free(temp);
        //Sets the temp value to the next address
        temp = next;
    }
    //Frees up all remaining memory associated with the list
    free(list);
}

int getData(DoubleLinkedList* list) {
    //Makes sure the list isnt at the head or tail
    if (list->current != list->head && list->current != list->tail) {
        //Returns the data in the selected node
        return list->current->data;
    }
    fprintf(stderr, "Error: Current node is not a valid data node. Please move from either the head or tail\n");
    exit(1);
}

void goToNextNode(DoubleLinkedList* list) {
    //Checks if the current node is the tail
    if (list->current != list->tail) {
        //If it isnt move to the next node
        list->current = list->current->next;
    }else{
        //Prints a standerd error informing the user they are at the tail of the list. Ends the function
        fprintf(stderr, "Error: You are at the tail of the list. Cannot move past the tail\n");
       
    }
}

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

void goToHead(DoubleLinkedList* list) {
    //Moves the current value to the head
    list->current = list->head;
}

void goToTail(DoubleLinkedList* list) {
    //Moves the current value to the tail
    list->current = list->tail;
}


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

void deleteCurrentNode(DoubleLinkedList* list) {
    //Checks that the current node is not the head or tail
    if (list->current == list->head || list->current == list->tail) {
        fprintf(stderr, "Error: Cannot delete head or tail.\n");
        return;
    }
    //Make a temp node equal to the cuurent node
    Node* temp = list->current;
    //The previous nodes next address is set to the current nodes next address and vice versa
    list->current->prev->next = list->current->next;
    list->current->next->prev = list->current->prev;

    // Moves the current node to the next node, leaving only the temp value at the original node
    list->current = list->current->next; 

    //Removes the temp node
    free(temp);
}


void printList(DoubleLinkedList* list) {
    //Creates a temp Node to start from the head of the list
    Node* temp = list->head->next; 
    //Operates until temp reaches the tail
    while (temp != list->tail) {
        //Prints the data from the selected node
        printf("%d ", temp->data);
        //Moves onto the next node
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    DoubleLinkedList* list = createDoubleLinkedList();

    insertAfter(list, 5);
    insertAfter(list, 15);
    insertAfter(list, 25);
    insertBefore(list, 35);
    printList(list);
    goToTail(list);
    goToPreviousNode(list);
    goToPreviousNode(list);
    deleteCurrentNode(list);
    printList(list);
   
    printf("The selected nodes data is %d \n", getData(list));

    deleteDoubleLinkedList(list);
   

}



