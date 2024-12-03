#include <stdio.h>
#include <stdlib.h>
#include "MenuFunctions.h" // Ensure this file exists and provides the required functions

void displayMenu() {
    printf("\nMENU:\n");
    printf("1. Menu Function 1\n");
    printf("2. Menu Function 2\n");
    printf("3. Menu Function 3\n");
    printf("4. Menu Function 4\n");
    printf("5. Menu Function 5\n");
    printf("6. Menu Function 6\n");
    printf("7. Menu Function 7\n");
    printf("8. Exit\n");
}

int main() {
    int choice = -1;
    orderedIntSet** setArray = (orderedIntSet**)malloc(10 * sizeof(orderedIntSet*));
    for (int i = 0; i < 10; i++) {
        setArray[i] = NULL; // Initialize each pointer to NULL
    }
    while (1) {
        // Display the menu
        displayMenu();

        // Prompt user for choice
        printf("\nEnter your choice: ");
        if (scanf_s("%d", &choice) != 1) {
            // Handle invalid (non-numeric) input
            printf("> Invalid input! Please enter a number.\n");
            // Clear the input buffer
            while (getchar() != '\n');
            continue;
        }
        
        // Process user choice
        switch (choice) {
        case 1:
            MF1(setArray);
            break;
        case 2:
            MF2(setArray);
            break;
        case 3:
            MF3(setArray);
            break;
        case 4:
            MF4(setArray);
            break;
        case 5:
            MF5(setArray);
            break;
        case 6:
            MF6(setArray);
            break;
        case 7:
            MF7(setArray);
            break;
        case 8:
            printf("Exiting.....\n");
            exit(0);
        default:
            printf("> Invalid choice! Please try again.\n");
            break;
        }
    }
    return 0;
}
