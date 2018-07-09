// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2015/03/02 Yu-Hao Ho]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
#include<climits> // used in Merge (INT_MAX as infinity)
#include<cmath> 
// used in SortSubVector, Max_Heapify, and Build_Max_Heap (floor() as lower bound bracket)

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here

    // Textbook page 18 psuedo code
    for (int j = 1; j < data.size(); j++){
        int key = data[j];
        // Insert data[j] into the sorted sequence data[1, ..., j-1]
        int i = j - 1;
        while (i >= 0 && data[i] > key){
            data[i + 1] = data[i];
            i--;
        }
        data[i + 1] = key;
    }
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    SortSubVector(data, 0, data.size() - 1);
}

// Sort subvector
void SortTool::SortSubVector(vector<int>& data, int low, int high) {
    // Function : Sort subvector
    // TODO : Please complete SortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed

    // Textbook page 34 psuedo code
    if (low < high){
        int middle1 = floor((low + high)/2);
        int middle2 = middle1 + 1;
        SortSubVector(data, low, middle1);
        SortSubVector(data, middle2, high);
        Merge(data, low, middle1, middle2, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function

    // Textbook page 31 psuedo code
    int count1 = middle2 - low;
    int count2 = high - middle1;
    int left[count1 + 1], right[count2 + 1];
    for (int i = 0; i < count1; i++){
        left[i] = data[low + i];
    }
    for (int j = 0; j < count2; j++){
        right[j] = data[middle2 + j];
    }
    left[count1] = right[count2] = INT_MAX; //INT_MAX works as infinity
    for (int k = low, i = 0, j = 0; k <= high; k++){
        if (left[i] <= right[j]){
            data[k] = left[i];
            i++;
        } 
        else {
            data[k] = right[j];
            j++;
        }
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    Build_Max_Heap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        Max_Heapify(data,0);
    }
}

// Textbook page 152 for three tool functions
int parent(int child){
    return floor((child-1)/2);
}
int left(int node){
    return 2*node + 1;
}
int right(int node){
    return 2*(node + 1);
}

//Max heapify
void SortTool::Max_Heapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here

    // Textbook page 154 psuedo code
    int l = left(root);
    int r = right(root);
    int largest = 0;
    if (l < heapSize && data[l] > data[root]){
        largest = l;
    }
    else{
        largest = root;
    }
    if (r < heapSize && data[r] > data[largest]){
        largest = r;
    }
    if (largest != root){
        swap(data[root], data[largest]);
        Max_Heapify(data, largest);
    }
}

//Build max heap
void SortTool::Build_Max_Heap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete Build_Max_Heap code here

    // Textbook page 157 psuedo code
    for (int i = ceil(heapSize/2); i >= 0; i--){
        Max_Heapify(data, i);
    }
}
