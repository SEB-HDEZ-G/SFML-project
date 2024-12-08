#ifndef LINEARSEARCH_H
#define LINEARSEARCH_H
#include <iostream>
#include <vector>
using namespace std;

vector<int> linearSearch(vector<int>& elements, int target){
    vector<int> indexes;
    for(int i=0; i < elements.size(); ++i) {
        if(elements[i] == target) {
            indexes.push_back(i);
        }
    }
    return indexes;
}

#endif