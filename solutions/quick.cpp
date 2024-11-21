
// quick.c
#include "sort.h"
#include <stdio.h>

void quickSort(int *arr, int low, int high) {
  if (low < high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
      if (arr[j] <= pivot) {
        i++;
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    quickSort(arr, low, i);
    quickSort(arr, i + 2, high);
  }
}

void sort(int *arr, int len) {
    FILE *fp = fopen("/tmp/sort_log.txt", "a");
    fprintf(fp, "sort called\n");
    fclose(fp);
    quickSort(arr, 0, len - 1);
}
