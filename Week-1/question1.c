#include <stdio.h>

int sumofn(int n){
    return (n*(n+1))/2;
}

int main(){
    int n;
    printf("Enter the final number up to which the sum should be calculated:");
    scanf("%d", &n);

    printf("the sum of the first %d natural numbers is: %d", n, sumofn(n));

    return 0;
}