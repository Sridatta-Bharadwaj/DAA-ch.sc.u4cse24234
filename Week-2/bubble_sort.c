#include <stdio.h>

void bubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
}

int main() {
    int arr[] = {5, 1, 4, 2, 8};
    int n = sizeof(arr)/sizeof(arr[0]);

    bubbleSort(arr, n);
    printArray(arr, n);
}
