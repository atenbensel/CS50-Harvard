#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NUMBERS 1000000

// Function prototypes
void selectionSort(int arr[], int n);
void bubbleSort(int arr[], int n);
void mergeSort(int arr[], int l, int r);
void isSorted(int arr[], int n);

int main(int argc, char *argv[])
{
    // Check for correct number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./analyze_sort <filename>\n");
        return 1;
    }

    // Open file for reading
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error: Couldn't open file.\n");
        return 1;
    }

    // Read numbers from file
    int numbers[MAX_NUMBERS];
    int n = 0;
    while (fscanf(file, "%d", &numbers[n]) != EOF && n < MAX_NUMBERS)
    {
        n++;
    }
    fclose(file);

    // Measure time taken by each sorting algorithm
    clock_t start, end;
    double cpu_time_used;

    // Selection Sort
    int selectionSorted[MAX_NUMBERS];
    memcpy(selectionSorted, numbers, n * sizeof(int));
    start = clock();
    selectionSort(selectionSorted, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Selection Sort took %f seconds.\n", cpu_time_used);

    // Bubble Sort
    int bubbleSorted[MAX_NUMBERS];
    memcpy(bubbleSorted, numbers, n * sizeof(int));
    start = clock();
    bubbleSort(bubbleSorted, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Bubble Sort took %f seconds.\n", cpu_time_used);

    // Merge Sort
    int mergeSorted[MAX_NUMBERS];
    memcpy(mergeSorted, numbers, n * sizeof(int));
    start = clock();
    mergeSort(mergeSorted, 0, n - 1);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Merge Sort took %f seconds.\n", cpu_time_used);

    return 0;
}

// Function to perform Selection Sort
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

// Function to perform Bubble Sort
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to perform Merge Sort
void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void merge(int arr[], int l, int m, int r)
{
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
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Function to check if the array is sorted
bool isSorted(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < arr[i - 1])
        {
            return false;
        }
    }
    return true;
}
