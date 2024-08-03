#include <stdio.h>

int main() {
    int i, n, firstTerm = 0, secondTerm = 1, sum = 0;

    printf("Enter the number of terms required in the Fibonacci Series: ");
    scanf("%d", &n);

    // Display the first two terms
    printf("\nFibonacci Series is:\n\n%d %d", firstTerm, secondTerm);

    // Calculate and print the remaining terms
    for (i = 2; i < n; ++i) {
        sum = firstTerm + secondTerm;
        firstTerm = secondTerm;
        secondTerm = sum;
        printf(" %d", sum);
    }

    return 0;
}
