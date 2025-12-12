#include <stdio.h>
#include <stdlib.h>

#define BUCKETS 10

void bucketSort(float arr[], int n) {
    float buckets[BUCKETS][n];
    int count[BUCKETS] = {0};

    for (int i = 0; i < n; i++) {
        int b = (int)(arr[i] * BUCKETS);
        buckets[b][count[b]++] = arr[i];
    }

    // Sort each bucket using insertion sort
    for (int b = 0; b < BUCKETS; b++) {
        for (int i = 1; i < count[b]; i++) {
            float key = buckets[b][i];
            int j = i - 1;
            while (j >= 0 && buckets[b][j] > key) {
                buckets[b][j + 1] = buckets[b][j];
                j--;
            }
            buckets[b][j + 1] = key;
        }
    }

    int index = 0;
    for (int b = 0; b < BUCKETS; b++) {
        for (int i = 0; i < count[b]; i++)
            arr[index++] = buckets[b][i];
    }
}

void printArray(float a[], int n) {
    for (int i = 0; i < n; i++) printf("%.2f ", a[i]);
}

int main() {
    float arr[] = {0.42, 0.32, 0.23, 0.52, 0.25, 0.47};
    int n = sizeof(arr)/sizeof(arr[0]);

    bucketSort(arr, n);
    printArray(arr, n);
}
