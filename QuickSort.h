#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <iostream>
#include <vector>
using namespace std;

void swap(int& x, int& y) {
    int const z = x;
    x = y;
    y = z; 
}

int partition(vector<int> &arr, int low, int high) {
    int pivot = arr[high]; //selecting last element as the pivot
    int i = low - 1; //index of element before the last element, used for swapping
    for(int j = low; j <= high - 1; j++) {
        //if current element is smaller or equal to pivot
        if(arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    //put pivot to its position
    swap(arr[i+1], arr[high]);

    //return the point of partition
    return (i+1);
}

void quickSort(vector<int> &arr, int low, int high) {
    //base case
    if(low < high) {
        //partitioning index
        int index = partition(arr, low, high);
        quickSort(arr, low, index - 1);
        quickSort(arr, index + 1, high);
    }
}

#endif