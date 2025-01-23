#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Struct to hold date (day, month, year)
typedef struct {
    int day;
    int month;
    int year;
} Date;

// Function prototypes
int readDatesFromFile(const char *filename, Date **dates);
void bubbleSort(Date arr[], int n);
void insertionSort(Date arr[], int n);
void quickSort(Date arr[], int low, int high);
int partition(Date arr[], int low, int high);
void selectionSort(Date arr[], int n);
void mergeSort(Date arr[], int left, int right);
void merge(Date arr[], int left, int mid, int right);
void heapSort(Date arr[], int n);
void heapify(Date arr[], int n, int i);
void countingSort(Date arr[], int n);
void printDates(Date arr[], int n);
void bucketSort(Date arr[], int n);
void radixSort(Date arr[], int n);
void countingRadixSort(Date arr[], int n, int type);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <sort_type>\n", argv[0]);
        fprintf(stderr, "sort_type: 1 for Bubble Sort, 2 for Insertion Sort, 3 for Quick Sort, 4 for Selection Sort, 5 for Merge Sort, 6 for Heap Sort, 7 for Counting Sort\n");
        return 1;
    }

    Date *dates;
    int numDates = readDatesFromFile(argv[1], &dates);
    if (numDates == -1) {
        return 1;
    }

    // Choose sorting algorithm based on user input
    if (strcmp(argv[2], "1") == 0) {
        bubbleSort(dates, numDates);
        printf("Sorted dates using Bubble Sort:\n");
    } else if (strcmp(argv[2], "2") == 0) {
        insertionSort(dates, numDates);
        printf("Sorted dates using Insertion Sort:\n");
    } else if (strcmp(argv[2], "3") == 0) {
        quickSort(dates, 0, numDates - 1);
        printf("Sorted dates using Quick Sort:\n");
    } else if (strcmp(argv[2], "4") == 0) {
        selectionSort(dates, numDates);
        printf("Sorted dates using Selection Sort:\n");
    } else if (strcmp(argv[2], "5") == 0) {
        mergeSort(dates, 0, numDates - 1);
        printf("Sorted dates using Merge Sort:\n");
    } else if (strcmp(argv[2], "6") == 0) {
        heapSort(dates, numDates);
        printf("Sorted dates using Heap Sort:\n");
    } else if (strcmp(argv[2], "7") == 0) {
        countingSort(dates, numDates);
        printf("Sorted dates using Counting Sort:\n");
    } else if (strcmp(argv[2], "8") == 0) {
        bucketSort(dates, numDates);
        printf("Sorted dates using Bucket Sort:\n");
    } else if (strcmp(argv[2], "9") == 0) {
        radixSort(dates, numDates);
        printf("Sorted dates using Radix Sort:\n");
    } else {
        fprintf(stderr, "Invalid sort_type. Use 1 for Bubble Sort, 2 for Insertion Sort, 3 for Quick Sort, 4 for Selection Sort, 5 for Merge Sort, 6 for Heap Sort, or 7 for Counting Sort.\n");
        free(dates);
        return 1;
    }

    // Print the sorted dates
    printDates(dates, numDates);

    // Free allocated memory
    free(dates);
    return 0;
}

// Function to read dates from a file and return an array of Date structs
int readDatesFromFile(const char *filename, Date **dates) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    // Count how many lines are in the file (for array size)
    int count = 0;
    char buffer[50];
    while (fgets(buffer, sizeof(buffer), file)) {
        count++;
    }

    // Allocate memory for the date array
    *dates = (Date *)malloc(count * sizeof(Date));
    if (!*dates) {
        perror("Memory allocation failed");
        fclose(file);
        return -1;
    }

    // Rewind file and read the dates
    rewind(file);
    int i = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = 0;

        // Parse the date (d/m/y format)
        sscanf(buffer, "%d/%d/%d", &(*dates)[i].day, &(*dates)[i].month, &(*dates)[i].year);
        i++;
    }

    fclose(file);
    return count;
}

// Counting Sort function for sorting dates (with fixed year range)
void countingSort(Date arr[], int n) {
    int minYear = 2000;
    int maxYear = 2025;
    int minMonth = 1;
    int maxMonth = 12;
    int minDay = 1;
    int maxDay = 31;

    // Arrays to count occurrences for year, month, and day
    int yearRange = maxYear - minYear + 1;
    int monthRange = maxMonth - minMonth + 1;
    int dayRange = maxDay - minDay + 1;

    // Create the count array (3D array for year, month, day)
    int ***count = (int ***)malloc(yearRange * sizeof(int **));
    for (int i = 0; i < yearRange; i++) {
        count[i] = (int **)malloc(monthRange * sizeof(int *));
        for (int j = 0; j < monthRange; j++) {
            count[i][j] = (int *)calloc(dayRange, sizeof(int));
        }
    }

    // Count the occurrences of each date
    for (int i = 0; i < n; i++) {
        int yearIndex = arr[i].year - minYear;
        int monthIndex = arr[i].month - minMonth;
        int dayIndex = arr[i].day - minDay;
        count[yearIndex][monthIndex][dayIndex]++;
    }

    // Reconstruct the sorted array
    int index = 0;
    for (int year = 0; year < yearRange; year++) {
        for (int month = 0; month < monthRange; month++) {
            for (int day = 0; day < dayRange; day++) {
                while (count[year][month][day] > 0) {
                    arr[index].year = minYear + year;
                    arr[index].month = minMonth + month;
                    arr[index].day = minDay + day;
                    index++;
                    count[year][month][day]--;
                }
            }
        }
    }

    // Free the memory for the count array
    for (int i = 0; i < yearRange; i++) {
        for (int j = 0; j < monthRange; j++) {
            free(count[i][j]);
        }
        free(count[i]);
    }
    free(count);
}

// Bubble Sort function for sorting dates
void bubbleSort(Date arr[], int n) {
    int i, j;
    bool swapped;

    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j].year > arr[j + 1].year ||
                (arr[j].year == arr[j + 1].year && arr[j].month > arr[j + 1].month) ||
                (arr[j].year == arr[j + 1].year && arr[j].month == arr[j + 1].month && arr[j].day > arr[j + 1].day)) {
                
                Date temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Insertion Sort implementation
void insertionSort(Date arr[], int n) {
    int i, j;
    Date key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        
        while (j >= 0 && (arr[j].year > key.year || 
              (arr[j].year == key.year && arr[j].month > key.month) ||
              (arr[j].year == key.year && arr[j].month == key.month && arr[j].day > key.day))) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Quick Sort implementation
void quickSort(Date arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(Date arr[], int low, int high) {
    Date pivot = arr[high];
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j].year < pivot.year || 
           (arr[j].year == pivot.year && arr[j].month < pivot.month) ||
           (arr[j].year == pivot.year && arr[j].month == pivot.month && arr[j].day < pivot.day)) {
            i++;
            Date temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    Date temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// Selection Sort implementation
void selectionSort(Date arr[], int n) {
    int i, j, min_idx;
    
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j].year < arr[min_idx].year || 
               (arr[j].year == arr[min_idx].year && arr[j].month < arr[min_idx].month) ||
               (arr[j].year == arr[min_idx].year && arr[j].month == arr[min_idx].month && arr[j].day < arr[min_idx].day)) {
                min_idx = j;
            }
        }
        Date temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

// Merge Sort implementation
void merge(Date arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temp arrays
    Date *L = (Date *)malloc(n1 * sizeof(Date));
    Date *R = (Date *)malloc(n2 * sizeof(Date));
    
    // Copy data to temp arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    i = 0;
    j = 0;
    k = left;
    
    while (i < n1 && j < n2) {
        if (L[i].year < R[j].year || 
           (L[i].year == R[j].year && L[i].month < R[j].month) ||
           (L[i].year == R[j].year && L[i].month == R[j].month && L[i].day < R[j].day)) {
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
    
    free(L);
    free(R);
}

void mergeSort(Date arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Heap Sort implementation
void heapify(Date arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && (arr[left].year > arr[largest].year ||
       (arr[left].year == arr[largest].year && arr[left].month > arr[largest].month) ||
       (arr[left].year == arr[largest].year && arr[left].month == arr[largest].month && 
        arr[left].day > arr[largest].day)))
        largest = left;
    
    if (right < n && (arr[right].year > arr[largest].year ||
       (arr[right].year == arr[largest].year && arr[right].month > arr[largest].month) ||
       (arr[right].year == arr[largest].year && arr[right].month == arr[largest].month && 
        arr[right].day > arr[largest].day)))
        largest = right;
    
    if (largest != i) {
        Date temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(Date arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    for (int i = n - 1; i > 0; i--) {
        Date temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// Function to print the dates
void printDates(Date arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%02d/%02d/%d\n", arr[i].day, arr[i].month, arr[i].year);
    }
}

// Bucket sort implementation:
void bucketSort(Date arr[], int n) {
    if (n <= 0) return;

    // Find min and max years to determine bucket range
    int minYear = arr[0].year;
    int maxYear = arr[0].year;
    for (int i = 1; i < n; i++) {
        if (arr[i].year < minYear) minYear = arr[i].year;
        if (arr[i].year > maxYear) maxYear = arr[i].year;
    }
    
    int numBuckets = maxYear - minYear + 1;
    
    // Create an array of buckets, where each bucket is a dynamic array of dates
    typedef struct {
        Date* dates;
        int size;
        int capacity;
    } Bucket;
    
    Bucket* buckets = (Bucket*)malloc(numBuckets * sizeof(Bucket));
    
    // Initialize buckets
    for (int i = 0; i < numBuckets; i++) {
        buckets[i].dates = (Date*)malloc(n * sizeof(Date));  // Worst case: all dates in one bucket
        buckets[i].size = 0;
        buckets[i].capacity = n;
    }
    
    // Distribute dates into buckets based on year
    for (int i = 0; i < n; i++) {
        int bucketIndex = arr[i].year - minYear;
        buckets[bucketIndex].dates[buckets[bucketIndex].size++] = arr[i];
    }
    
    // Sort each bucket using insertion sort (good for small arrays)
    for (int i = 0; i < numBuckets; i++) {
        // Sort dates within each year bucket by month and day
        for (int j = 1; j < buckets[i].size; j++) {
            Date key = buckets[i].dates[j];
            int k = j - 1;
            
            while (k >= 0 && (
                   buckets[i].dates[k].month > key.month || 
                   (buckets[i].dates[k].month == key.month && 
                    buckets[i].dates[k].day > key.day))) {
                buckets[i].dates[k + 1] = buckets[i].dates[k];
                k--;
            }
            buckets[i].dates[k + 1] = key;
        }
    }
    
    // Gather sorted dates back into original array
    int index = 0;
    for (int i = 0; i < numBuckets; i++) {
        for (int j = 0; j < buckets[i].size; j++) {
            arr[index++] = buckets[i].dates[j];
        }
    }
    
    // Free allocated memory
    for (int i = 0; i < numBuckets; i++) {
        free(buckets[i].dates);
    }
    free(buckets);
}

// Radix sort implementation:
void radixSort(Date arr[], int n) {
    // Sort by day first, then month, then year
    // This ensures correct ordering as we move from least to most significant components
    
    // Sort by day (1-31)
    countingRadixSort(arr, n, 0);
    
    // Sort by month (1-12)
    countingRadixSort(arr, n, 1);
    
    // Sort by year (2000-2025)
    countingRadixSort(arr, n, 2);
}

void countingRadixSort(Date arr[], int n, int type) {
    Date* output = (Date*)malloc(n * sizeof(Date));
    int max, min;
    
    // Determine range based on type (0: day, 1: month, 2: year)
    switch(type) {
        case 0: // day
            min = 1;
            max = 31;
            break;
        case 1: // month
            min = 1;
            max = 12;
            break;
        case 2: // year
            min = 2000;
            max = 2025;
            break;
        default:
            free(output);
            return;
    }
    
    int range = max - min + 1;
    int* count = (int*)calloc(range, sizeof(int));
    
    // Store count of each element
    for (int i = 0; i < n; i++) {
        int value;
        switch(type) {
            case 0:
                value = arr[i].day - min;
                break;
            case 1:
                value = arr[i].month - min;
                break;
            case 2:
                value = arr[i].year - min;
                break;
        }
        count[value]++;
    }
    
    // Modify count array to contain actual positions
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }
    
    // Build output array
    for (int i = n - 1; i >= 0; i--) {
        int value;
        switch(type) {
            case 0:
                value = arr[i].day - min;
                break;
            case 1:
                value = arr[i].month - min;
                break;
            case 2:
                value = arr[i].year - min;
                break;
        }
        output[count[value] - 1] = arr[i];
        count[value]--;
    }
    
    // Copy output array back to original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    
    free(output);
    free(count);
}
