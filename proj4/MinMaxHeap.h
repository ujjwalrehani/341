// Ujjwal Rehani
// CMSC 341 Chang
// File: MinMaxHeap.h

#ifndef MinMaxHeap_H
#define MinMaxHeap_H

#include <iostream>
#include <stdexcept>
using namespace std;

template <typename  T>
class MinMaxHeap
{
public:
    MinMaxHeap(int capacity);
    MinMaxHeap(const MinMaxHeap<T>& other);
    ~MinMaxHeap();
    const MinMaxHeap<T>& operator=(const MinMaxHeap<T>& rhs);
    int size();
    void insert(const T& data);
    T deleteMin();
    T deleteMax();
    void dump();
    void locateMin(int pos, T& data, int& index);
    void locateMax(int pos, T& data, int& index);
private:
    T *minHeap;
    int *minHeapIndex;
    T *maxHeap;
    int *maxHeapIndex;
    int curSize;                    // Number of elements in heap
    int capacity;                   // Capacity of the heap
    void doubleCapacity();
    void percolateLargerDown(int hole);
    void percolateSmallerDown(int hole);
}; 
#include "MinMaxHeap.cpp"

#endif

