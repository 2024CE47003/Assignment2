#include <stdio.h>
#include <stdlib.h>
#include "MenuFunctions.h"
int IndexChoiceEntered(orderedIntSet** setArray) {
    printf("--------------------------------------------------------------------------\n");
    int IndexChoice = 0;
    printf("Please enter what index from Set Array you wish to work with (0-9) for Function 1 \n");
    scanf_s("%i", &IndexChoice);

    // Validate the index is within bounds
    if (IndexChoice > 9 || IndexChoice < 0) {
        printf("Error: Invalid input for index. Please choose a number between 0 and 9.\n");
        return; // Exit the function if the index is invalid
    }
    return IndexChoice;
}
void MF1(orderedIntSet** setArray) {
    int IndexChoice = IndexChoiceEntered(setArray);
    // Initialize the set for the chosen index
    setArray[IndexChoice] = createOrderedSet();
    if (setArray[IndexChoice] == NULL) {
        printf("Error: Failed to create a set for index %d.\n", IndexChoice);
        return; // Exit if memory allocation for the set failed
    }
    else {
        printf("Empty Ordered Set Created at set #%d\n\n",IndexChoice);
    }
    
}

void MF2(orderedIntSet** setArray) {
    
    int IndexChoice = IndexChoiceEntered(setArray);
    
    // Check if the index has already been populated
    if (setArray[IndexChoice] != NULL) {
        deleteOrderedSet(setArray[IndexChoice]);
        printf("Ordered Set #%d successfully deleted \n\n", IndexChoice);
        return; 
    }

    // Initialize the set for the chosen index
    
    if (setArray[IndexChoice] == NULL) {
        printf("Error: Failed to delete set for index %d as set is already NULL\n\n", IndexChoice);
        return; // Exit if memory allocation for the set failed
    }
    
}

void MF3(orderedIntSet** setArray) {
    int IndexChoice = IndexChoiceEntered(setArray);
    int element = 0;
    if (setArray[IndexChoice]==NULL) {
        while (1) {
            scanf_s("%i", &element);
            if (element == -1) { // Exit the loop if -1 is entered
                break;
            }
        }
        printf("Error set has been deleted or was not created\n");
        return;
    }
    
    while (1) { // Infinite loop, explicitly break on -1
        printf("Please enter an integer value for Set Array #(%d) (enter -1 to stop):\n", IndexChoice);
        scanf_s("%i", &element);

        if (element == -1) { // Exit the loop if -1 is entered
            break;
        }

        // Add the element to the set
        int added=addElement(setArray[IndexChoice], element);

        // Display the updated set
        printf("\nElement entered is %d\n", element);
        if (added == NUMBER_ALREADY_IN_SET) {
            printf("Number is already in the set\n");
        }
        else {
            printf("Number Added Sucessfully\n");
            printf("Set Array[%d] has value of:\n", IndexChoice);
            printToStdout(setArray[IndexChoice]);
        }
    }
}

void MF4(orderedIntSet** setArray) { // no work yet
    int IndexChoice = IndexChoiceEntered(setArray);

    int element = 0; // Reset element for each set
    while (1) { // Infinite loop, explicitly break on -1
        printf("Please enter an integer value for Set Array #(%d) that you wish to delete (enter -1 to stop):\n", IndexChoice);
        scanf_s("%i", &element);

        if (element == -1) { // Exit the loop if -1 is entered
            break;
        }

        int removed = removeElement(setArray[IndexChoice], element);

        // Display the updated set
        printf("\nElement entered is %d\n", element);
        if (removed == NUMBER_NOT_IN_SET) {
            printf("Number is not in the set\n");
        }
        else {
            printf("Number Removed Sucessfully\n");
            printf("Set Array[%d] has value of:\n", IndexChoice);
            printToStdout(setArray[IndexChoice]);
        }
    }
}

void MF5(orderedIntSet** setArray) {
	
    int IndexChoice[3];
	for (int i = 0; i < 3;i++) {
        IndexChoice[i] = IndexChoiceEntered(setArray);
        if (setArray[IndexChoice[i]]==NULL) {
            printf("Error set has been deleted\n");
        }
	}
	
	setArray[IndexChoice[2]]=setIntersection(setArray[IndexChoice[0]], setArray[IndexChoice[1]]);
	printf("The intersection of set 1 and 2 is\n");
	printToStdout(setArray[IndexChoice[2]]);
	printf("--------------------------------------------------------------------------\n");
}

void MF6(orderedIntSet** setArray) {
    int IndexChoice[3];
    for (int i = 0; i < 3; i++) {
        IndexChoice[i] = IndexChoiceEntered(setArray);
        if (setArray[IndexChoice[i]] == NULL) {
            printf("Error set has been deleted\n");
        }
    }

    setArray[IndexChoice[2]] = setUnion(setArray[IndexChoice[0]], setArray[IndexChoice[1]]);
    printf("The Union of set 1 and 2 is\n");
    printToStdout(setArray[IndexChoice[2]]);
    printf("--------------------------------------------------------------------------\n");
}

void MF7(orderedIntSet** setArray) {
    int IndexChoice[3];
    for (int i = 0; i < 3; i++) {
        printf("Please enter what indices #%d from Set Array you wish to work with (0-9) for Function 7 (Difference)\n", i + 1);
        scanf_s("%d", &IndexChoice[i]);
        if (IndexChoice[i] > 9 || IndexChoice[i] < 0) {
            printf("Error: Invalid Input for Indices\n");
            return EXIT_SUCCESS;
        }
    }

    setArray[IndexChoice[2]] = setDifference(setArray[IndexChoice[0]], setArray[IndexChoice[1]]);
    printf("The Difference between set 1 and 2 is\n");
    printToStdout(setArray[IndexChoice[2]]);
    printf("--------------------------------------------------------------------------\n");
}



//void main() {
//    orderedIntSet** setArray = (orderedIntSet**)malloc(10 * sizeof(orderedIntSet*));
//    for (int i = 0; i < 10; i++) {
//        setArray[i] = NULL; // Initialize each pointer to NULL
//    }
//    //MF1(setArray);
//    //MF2(setArray);
//	for (int i = 0; i < 2; i++) {
//		MF3(setArray);
//	}
//    MF4(setArray);
//	//MF5(setArray);
//    //MF6(setArray);
//    //MF7(setArray);
//}