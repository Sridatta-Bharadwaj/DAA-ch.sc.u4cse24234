#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
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

int quickSelect(int arr[], int low, int high, int k) {
    if (low == high) return arr[low];

    int pi = partition(arr, low, high);
    int pos = pi - low + 1;

    if (pos == k)
        return arr[pi];
    else if (k < pos)
        return quickSelect(arr, low, pi - 1, k);
    else
        return quickSelect(arr, pi + 1, high, k - pos);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {64, 25, 12, 22, 11, 90, 45};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k;

    printf("Array: ");
    printArray(arr, n);

    printf("Enter k (1 to %d): ", n);
    scanf("%d", &k);

    if (k < 1 || k > n) {
        printf("Invalid k\n");
        return 1;
    }

    int result = quickSelect(arr, 0, n - 1, k);
    printf("The %d-th smallest element is: %d\n", k, result);

    return 0;
}