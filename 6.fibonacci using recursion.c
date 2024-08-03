#include <stdio.h>

// Function to calculate the nth Fibonacci number
int Fibonacci(int n) {
    if (n == 0) return 0;
    else if (n == 1) return 1;
    else return Fibonacci(n - 1) + Fibonacci(n - 2);
}

int main() {
    int n, i = 0;

    printf("Enter the number of terms required in the Fibonacci Series: ");
    scanf("%d", &n);

    printf("\nFibonacci series:\n");
    for (int c = 1; c <= n; ++c) {
        printf("%d ", Fibonacci(i));
        ++i;
    }

    return 0;
}
