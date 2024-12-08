#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

int binarySearch(vector<int>& vec, int target) {
    sort(vec.begin(), vec.end());
    vector<int> indexes;
    int lo = 0;
    int hi = vec.size() - 1;

    while(lo <= hi) {
        int mid = lo + (hi-lo)/2;
        if(vec[mid] == target) {
            return mid;
        }
        if(vec[mid] <= target) {
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }
    return -1;
}

vector<int> generateUniqueNumbers(int size, int minValue, int maxValue) {
    srand(time(0)); //get a different number each time
    set<int> uniqueNumbers;
    while (uniqueNumbers.size() < size) {
        int num = minValue + rand() % (maxValue - minValue + 1); //ensure the right range for unique numbers
        uniqueNumbers.insert(num);
    }
    return vector<int>(uniqueNumbers.begin(), uniqueNumbers.end());
}

#endif