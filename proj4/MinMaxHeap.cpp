// Ujjwal Rehani
// CMSC 341 Chang
// File: MinMaxHeap.cpp
//


#include <iostream>
#include <stdexcept>
#include "MinMaxHeap.h"
using namespace std ;

template <typename T>
MinMaxHeap<T>::MinMaxHeap(int capacity) {
    this->capacity = capacity;
    minHeap = new T[capacity+1];
    minHeapIndex = new int[capacity+1];
    maxHeap = new T[capacity+1];
    maxHeapIndex = new int[capacity+1];
    curSize = 0;
    
}

template <typename T>
MinMaxHeap<T>::MinMaxHeap(const MinMaxHeap<T>& other) {
    delete minHeap;
    delete minHeapIndex;
    delete maxHeap;
    delete maxHeapIndex;
    
    this->capacity = other.capacity;
    minHeap = new T[capacity+1];
    minHeapIndex = new int[capacity+1];
    maxHeap = new T[capacity+1];
    maxHeapIndex = new int[capacity+1];
    curSize = other.curSize;
    for (int i=1; i<=curSize; i++) {
        minHeap[i] = other.minHeap[i];
        minHeapIndex[i] = other.minHeapIndex[i];
        maxHeap[i] = other.maxHeap[i];
        maxHeapIndex[i] = other.maxHeapIndex[i];
    }
}

template <typename T>
MinMaxHeap<T>::~MinMaxHeap() {
    delete minHeap;
    delete minHeapIndex;
    delete maxHeap;
    delete maxHeapIndex;
}

template <typename T>
const MinMaxHeap<T>& MinMaxHeap<T>::operator=(const MinMaxHeap<T>& rhs) {
    if(this != &rhs)
    {
        delete minHeap;
        delete minHeapIndex;
        delete maxHeap;
        delete maxHeapIndex;
        
        this->capacity = rhs.capacity;
        minHeap = new T[capacity+1];
        minHeapIndex = new int[capacity+1];
        maxHeap = new T[capacity+1];
        maxHeapIndex = new int[capacity+1];
        curSize = rhs.curSize;
        for (int i=1; i<=curSize; i++) {
            minHeap[i] = rhs.minHeap[i];
            minHeapIndex[i] = rhs.minHeapIndex[i];
            maxHeap[i] = rhs.maxHeap[i];
            maxHeapIndex[i] = rhs.maxHeapIndex[i];
        }
    }
    return *this;
}

template <typename T>
int MinMaxHeap<T>::size() {
    return curSize;
}

template <typename T>
void MinMaxHeap<T>::doubleCapacity() {
    capacity *= 2;
    
    T *minH = minHeap;
    int *minHI = minHeapIndex;
    T * maxH = maxHeap;
    int *maxHI = maxHeapIndex;
    
    minHeap = new T[capacity];
    minHeapIndex = new int[capacity];
    maxHeap = new T[capacity];
    maxHeapIndex = new int[capacity];
    
    for (int i = 1; i <= curSize; i++) {
        minHeap[i] = minH[i];
        minHeapIndex[i] = minHI[i];
        maxHeap[i] = maxH[i];
        maxHeapIndex[i] = maxHI[i];
    }
    
    delete minH;
    delete minHI;
    delete maxH;
    delete maxHI;
}

template <typename T>
void MinMaxHeap<T>::insert(const T& data)
{
    int tempI, minI;
    
    if ( curSize == capacity)
        // doubleCapacity();
        throw std::out_of_range("Heap is Full!");

    int hole = ++curSize;      // Insert into the minHeap
    minHeap[0] = data;
    while (data < minHeap[hole/2]) {
        minHeap[hole] = minHeap[hole/2];
        tempI = minHeapIndex[hole/2];
        minHeapIndex[hole] = tempI;
        maxHeapIndex[tempI] = hole;
        hole /= 2;
    }
    minI = hole;
    minHeap[minI] = minHeap[0];
    
    hole = curSize;           // Insert into the maxHeap
    maxHeap[0] = data;
    while (data > maxHeap[hole/2]) {
        maxHeap[hole] = maxHeap[hole/2];
        tempI = maxHeapIndex[hole/2];
        maxHeapIndex[hole] = tempI;
        minHeapIndex[tempI] = hole;
        hole /= 2;
    }
    maxHeap[hole] = maxHeap[0];
    maxHeapIndex[hole] = minI;
    minHeapIndex[minI] = hole;
}

template <typename T>
T MinMaxHeap<T>::deleteMin()
{
    if(curSize == 0)
        throw std::out_of_range("Empty Heap!");

    int tempI;
    T minItem = minHeap[1];
    int maxDeleteIndex = minHeapIndex[1];
    minHeap[1] = minHeap[curSize];
    tempI = minHeapIndex[curSize];
    minHeapIndex[1] = tempI;
    maxHeapIndex[tempI] = 1;
    curSize--;
    percolateLargerDown(1);
    if (maxDeleteIndex <= curSize) {
        maxHeap[maxDeleteIndex] = maxHeap[curSize+1];
        tempI = maxHeapIndex[curSize+1];
        maxHeapIndex[maxDeleteIndex] = tempI;
        minHeapIndex[tempI] = maxDeleteIndex;
        percolateSmallerDown(maxDeleteIndex);
    }
    return minItem;
}

template <typename T>
T MinMaxHeap<T>::deleteMax()
{
    if(curSize == 0)
        throw std::out_of_range("Empty Heap!");

    int tempI;
    T maxItem = maxHeap[1];
    int minDeleteIndex = maxHeapIndex[1];
    maxHeap[1] = maxHeap[curSize];
    tempI = maxHeapIndex[curSize];
    maxHeapIndex[1] = tempI;
    minHeapIndex[tempI] = 1;
    curSize--;
    percolateSmallerDown(1);
    if (minDeleteIndex <= curSize) {
        minHeap[minDeleteIndex] = minHeap[curSize+1];
        tempI = minHeapIndex[curSize+1];
        minHeapIndex[minDeleteIndex] = tempI;
        maxHeapIndex[tempI] = minDeleteIndex;
        percolateLargerDown(minDeleteIndex);
    }
    return maxItem;
}

template <typename T>
void MinMaxHeap<T>::percolateLargerDown(int hole)
{
    int child, tempI;
    T tmp = minHeap[hole];
    int tmpI = minHeapIndex[hole];
    while (hole * 2 <= curSize) {
        child = hole * 2;
        if( child != curSize && minHeap[child + 1] < minHeap[child])
            ++child;
        if( minHeap[child] < tmp ) {
            minHeap[hole] = minHeap[child];
            tempI = minHeapIndex[child];
            minHeapIndex[hole] = tempI;
            maxHeapIndex[tempI] = hole;
        }
        else break;
        hole = child;
    }
    minHeap[hole] = tmp;
    minHeapIndex[hole] = tmpI;
    maxHeapIndex[tmpI] = hole;
}

template <typename T>
void MinMaxHeap<T>::percolateSmallerDown(int hole)
{
    int child, tempI;
    T tmp = maxHeap[hole];
    int tmpI = maxHeapIndex[hole];
    while (hole * 2 <= curSize) {
        child = hole * 2;
        if( child != curSize && maxHeap[child + 1] > maxHeap[child])
            ++child;
        if( maxHeap[child] > tmp ) {
            maxHeap[hole] = maxHeap[child];
            tempI = maxHeapIndex[child];
            maxHeapIndex[hole] = tempI;
            minHeapIndex[tempI] = hole;
        }
        else break;
        hole = child;
    }
    maxHeap[hole] = tmp;
    maxHeapIndex[hole] = tmpI;
    minHeapIndex[tmpI] = hole;
}

template <typename T>
void MinMaxHeap<T>::dump()
{
    cout << endl << "... MinMaxHeap::dump() ..." << endl;
    
    cout << endl << "------------Min Heap------------" << endl;
    cout << "size = " << curSize << ", capacity = " << capacity << endl;
    for (int i = 1; i <= curSize; i++) {
        cout << "Heap[" << i << "] = (" << minHeap[i] << ", " << minHeapIndex[i] << ")" << endl;
    }
    cout << endl << "------------Max Heap------------" << endl;
    cout << "size = " << curSize << ", capacity = " << capacity << endl;
    for (int i = 1; i <= curSize; i++) {
        cout << "Heap[" << i << "] = (" << maxHeap[i] << ", " << maxHeapIndex[i] << ")" << endl;
    }
    cout << endl;
}

template <typename T>
void MinMaxHeap<T>::locateMin(int pos, T& data, int& index)
{
     data = minHeap[pos];
     index = minHeapIndex[pos];
}

template <typename T>
void MinMaxHeap<T>::locateMax(int pos, T& data, int& index)
{
     data = maxHeap[pos];
     index = maxHeapIndex[pos];
}

