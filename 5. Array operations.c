#include <stdio.h>

// Function to display all elements in the array
void displayArray(int arr[], int size) {
    printf("Array elements: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to insert an element at a specified position
void insertElement(int arr[], int *size, int position, int value) {
    if (position >= 1 && position <= *size + 1) {
        for (int i = *size; i >= position; i--) {
            arr[i] = arr[i - 1];
        }
        arr[position - 1] = value;
        (*size)++;
        printf("Element %d inserted at position %d.\n", value, position);
    } else {
        printf("Invalid position for insertion.\n");
    }
}

// Function to delete an element from a specified position
void deleteElement(int arr[], int *size, int position) {
    if (*size > 0 && position >= 1 && position <= *size) {
        for (int i = position - 1; i < *size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        (*size)--;
        printf("Element at position %d deleted.\n", position);
    } else {
        printf("Invalid position for deletion.\n");
    }
}

int main() {
    int arr[100]; // Assuming a maximum array size of 100
    int size = 0; // Initial size of the array

    // Example: Inserting elements
    insertElement(arr, &size, 1, 10);
    insertElement(arr, &size, 2, 20);
    insertElement(arr, &size, 5, 30); // Trying an invalid position

    // Display the array
    displayArray(arr, size);

    // Example: Deleting an element
    deleteElement(arr, &size, 2);

    // Display the updated array
    displayArray(arr, size);

    return 0;
}
