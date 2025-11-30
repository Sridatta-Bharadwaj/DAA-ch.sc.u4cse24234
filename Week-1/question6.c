//Write a program to print the 1st n terms of the Fibonacci series using user-defined functions.

#include <stdio.h>

void printFibonacci(int n) {
    int a = 0, b = 1, c;

    printf("Fibonacci Series: ");

    for (int i = 1; i <= n; i++) {
        printf("%d ", a);
        c = a + b;
        a = b;
        b = c;
    }
}

int main() {
    int n;

    printf("Enter how many terms you want: ");
    scanf("%d", &n);

    printFibonacci(n);

    return 0;
}
