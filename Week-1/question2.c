//Write a program to find the sum of squares of the 1st n natural numbers using user-defined functions.

#include <stdio.h>

int sumofnsq(int n){
    return (n * (n+1) * (2*n + 1))/6;
}

int main(){
    int n;
    printf("Enter the final number up to which the sum of squares should be calculated:");
    scanf("%d", &n);

    printf("the sum of the first %d natural numbers is: %d", n, sumofnsq(n));

    return 0;
}