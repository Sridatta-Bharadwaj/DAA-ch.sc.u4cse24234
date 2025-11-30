#include <stdio.h>

int factorial(int n){
    if(n == 0){
        return 1;
    }
    return n * factorial(n - 1);
}

int main(){
    int n;
    printf("Enter the number of which factorial is to be calculated ");
    scanf("%d", &n);

    printf("the factorial of %d is %d", n, factorial(n));

    return 0;
}
