#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

// Creates the structure of Node
typedef struct Node {
    int data;                // Data stored in the node
    struct Node* next;       // Pointer to the next node
    struct Node* prev;       // Pointer to the previous node
} Node;

//Creates the structure of the DoubleLinkedList
typedef struct DoubleLinkedList {
    struct Node* head; // Pointer to the head of the list
    struct Node* tail; // Pointer to the tail of the list
    struct Node* current; // Pointer to the current element of the list
} DoubleLinkedList;


//FUNCTIONS

/*
Creates an empty double linked list with only a head and tail.
Current node is set to head
*/
DoubleLinkedList* createDoubleLinkedList();


/*
Deletes all memory associated with a DoubleLinkedList
@param list - The list you want to delete
*/
void deleteDoubleLinkedList(DoubleLinkedList* list);


/*
Gets the data from the node currently selected excluding the head and tail
@param list - The list whos currently selected code you want to get the data from
@return The selected nodes data
*/
int getData(DoubleLinkedList* list);


/*
Goes to the next node in the list
@param list - The list you want to move the current node forward in
*/
void goToNextNode(DoubleLinkedList* list);


/*
Goes to the previous node in the list
@param list - The list you want to move the current node backwards in
*/
void goToPreviousNode(DoubleLinkedList* list);


/*
Go to the head of the list
@param list - The list you want to move to the head of
*/
void goToHead(DoubleLinkedList* list);


/*
Go to the tail of the list
@param list - The list you want to move to the tail of
*/
void goToTail(DoubleLinkedList* list);


/*
Inserts a new node after the current node. Moves to that node
@param list - The list you want to add a node to
@param value - The value you want the node to have
*/
void insertAfter(DoubleLinkedList* list, int value);


/*
Inserts a new node before the current node. Moves to that node
@param list - The list you want to add a node to
@param value - The value you want the node to have
*/
void insertBefore(DoubleLinkedList* list, int value);


/*
Deletes the current node and moves onto the next node
@param list - The list whos current value you want to delete
*/
void deleteCurrentNode(DoubleLinkedList* list);


/*
Prints the data in each node of the list. Used for debugging
@param - list - The list you want to print out
*/
void printList(DoubleLinkedList* list);

#endif //DOUBLE_LINKED_LIST_H
