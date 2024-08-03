#include <stdio.h>

// Function to perform binary search
int binarySearch(int arr[], int l, int r, int x) {
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;
        else if (arr[mid] < x)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1; // Element not found
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements (in ascending order): ", n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &arr[i]);

    int x;
    printf("Enter the number to search: ");
    scanf("%d", &x);

    int result = binarySearch(arr, 0, n - 1, x);
    if (result != -1)
        printf("Element %d found at index %d.\n", x, result);
    else
        printf("Element %d not found.\n", x);

    return 0;
}
