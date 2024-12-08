#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H
#include <iostream>
#include <vector>
using namespace std;

void mySwap(int& x, int& y) {
    int z = x;
    x = y;
    y = z;
}

void selectionSort(vector<int>& vec) {
    int n = vec.size();

    for(int i=0; i < n; i++) {
        int minVal = i;
        for(int j=i+1; j < n; j++) {
            if(vec[j] < vec[minVal]) {
                minVal = j;
            }
        }
        if(minVal != i) {
            mySwap(vec[i], vec[minVal]);
        }
    }
}

#endif