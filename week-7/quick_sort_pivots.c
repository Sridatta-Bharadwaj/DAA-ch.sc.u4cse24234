#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partitionLast(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

int partitionFirst(int arr[], int low, int high) {
    swap(&arr[low], &arr[high]);
    return partitionLast(arr, low, high);
}

int partitionMedian(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid]) swap(&arr[low], &arr[mid]);
    if (arr[low] > arr[high]) swap(&arr[low], &arr[high]);
    if (arr[mid] > arr[high]) swap(&arr[mid], &arr[high]);
    swap(&arr[mid], &arr[high]);
    return partitionLast(arr, low, high);
}

void quickSortLast(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionLast(arr, low, high);
        quickSortLast(arr, low, pi - 1);
        quickSortLast(arr, pi + 1, high);
    }
}

void quickSortFirst(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionFirst(arr, low, high);
        quickSortFirst(arr, low, pi - 1);
        quickSortFirst(arr, pi + 1, high);
    }
}

void quickSortMedian(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionMedian(arr, low, high);
        quickSortMedian(arr, low, pi - 1);
        quickSortMedian(arr, pi + 1, high);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

void copyArray(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

int main() {
    int arr[] = {64, 25, 12, 22, 11, 90, 45};
    int n = sizeof(arr) / sizeof(arr[0]);
    int temp[7];

    printf("Original array: ");
    printArray(arr, n);

    copyArray(arr, temp, n);
    quickSortLast(temp, 0, n - 1);
    printf("Sorted (Last pivot):   ");
    printArray(temp, n);

    copyArray(arr, temp, n);
    quickSortFirst(temp, 0, n - 1);
    printf("Sorted (First pivot):  ");
    printArray(temp, n);

    copyArray(arr, temp, n);
    quickSortMedian(temp, 0, n - 1);
    printf("Sorted (Median pivot): ");
    printArray(temp, n);

    return 0;
}