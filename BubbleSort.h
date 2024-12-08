#ifndef BUBBLESORT_H
#define BUBBLESORT_H
#include <iostream>
#include <vector>
using namespace std;

void bubbleSort(vector<int>& vec) {
    int n = vec.size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n - 1 - i; j++) {
            if(vec[j] > vec[j+1]) {
                int const temp = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = temp;
            }
        }
    }
}

#endif