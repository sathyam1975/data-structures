#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function prototypes for sorting algorithms
void selectionSort(int arr[], int n);
void bubbleSort(int arr[], int n);
void insertionSort(int arr[], int n);
void quickSort(int arr[], int low, int high);
void mergeSort(int arr[], int l, int r);
int partition(int arr[], int low, int high);
void merge(int arr[], int l, int m, int r);

// Utility function to swap elements
void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Utility function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Utility function to copy an array
void copyArray(int src[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

// Function to generate a random array
void generate_random_array(int arr[], int size, int min_value, int max_value) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        arr[i] = min_value + rand() % (max_value - min_value + 1);
    }
}

int main() {
    int sizes[] = {100, 1000, 5000, 10000,50000,100000}; // Array sizes to test
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];
        int arr[size], temp[size];

        // Generate a random array
        generate_random_array(arr, size, 1, 10000);

        // Measure time for Selection Sort
        copyArray(arr, temp, size);
        clock_t start = clock();
        selectionSort(temp, size);
        clock_t end = clock();
        printf("Selection Sort for %d elements took %f seconds\n", size, ((double)(end - start)) / CLOCKS_PER_SEC);

        // Measure time for Bubble Sort
        copyArray(arr, temp, size);
        start = clock();
        bubbleSort(temp, size);
        end = clock();
        printf("Bubble Sort for %d elements took %f seconds\n", size, ((double)(end - start)) / CLOCKS_PER_SEC);

        // Measure time for Insertion Sort
        copyArray(arr, temp, size);
        start = clock();
        insertionSort(temp, size);
        end = clock();
        printf("Insertion Sort for %d elements took %f seconds\n", size, ((double)(end - start)) / CLOCKS_PER_SEC);

        // Measure time for Quick Sort
        copyArray(arr, temp, size);
        start = clock();
        quickSort(temp, 0, size - 1);
        end = clock();
        printf("Quick Sort for %d elements took %f seconds\n", size, ((double)(end - start)) / CLOCKS_PER_SEC);

        // Measure time for Merge Sort  
        copyArray(arr, temp, size);
        start = clock();
        mergeSort(temp, 0, size - 1);
        end = clock();
        printf("Merge Sort for %d elements took %f seconds\n", size, ((double)(end - start)) / CLOCKS_PER_SEC);

        printf("\n");
    }

    return 0;
}

// Implementation of Selection Sort
void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        swap(&arr[min_idx], &arr[i]);
    }
}

// Implementation of Bubble Sort
void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

// Implementation of Insertion Sort
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Implementation of Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Implementation of Merge Sort
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
