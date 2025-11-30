//Write a program to find the sum of cubes if the 1st n natural numbers.

#include <stdio.h>

int sumofncu(int n){
    return (n * n * (n + 1) * (n + 1)) / 4;
}

int main(){
    int n;
    printf("Enter the final number up to which the sum of cubes should be calculated:");
    scanf("%d", &n);

    printf("the sum of the first %d natural numbers is: %d", n, sumofncu(n));

    return 0;
}