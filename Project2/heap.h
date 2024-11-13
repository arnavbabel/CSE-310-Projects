//Arnav Babel
//Student ID # 1225345329

#ifndef HEAP_H 
#define HEAP_H 
#include "data_structures.h"

//method declarations for the methods in heap.cpp
HEAP* init(int);
void printHeap(HEAP*);
int insertKey(HEAP*, ELEMENT*);
void extractMin(HEAP*, int);
void decreaseKey(HEAP*, int, double);
HEAP* heapify(HEAP*, int);
int buildHeap(HEAP*);
int isMinHeap(HEAP*);
int getHeapifyCalls();
#endif