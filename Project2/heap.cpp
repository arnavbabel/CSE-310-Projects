//Arnav Babel
//Student ID # 1225345329

#include "heap.h"

#include <stdio.h>
#include <stdlib.h>

//method declaration
int numHeapifyCalls = 0;

//function that initializes the capacity of the heap
HEAP* init(int capacity) {
	fprintf(stdout, "Instruction: Init %d\n", capacity); //prints that the instruction is Init, and prints the capacity

	HEAP* heap = (HEAP*)malloc(sizeof(HEAP)); //allocates memory for the new heap
	if (heap == nullptr) { //checks if the heap exists
		return nullptr; //returns null
	}
	heap->capacity = capacity; //sets the heap's capacity to the value of capacity
	heap->size = 0; //sets the size of the heap to be 0
	heap->H = (ELEMENT**)malloc(capacity * sizeof(ELEMENT)); //allocates memory for the size of the heap
	return heap; //returns the heap
}

//function that prints the heap
void printHeap(HEAP* heap) {
	fprintf(stdout, "%d\n", heap->size); //prints the size of the heap
	for (int i = 0; i < heap->size; i++) { //loops while i is less than the size of the heap
		fprintf(stdout, "%lf\n", heap->H[i]->key); //prints each key value in the heap
	}
}

//function that inserts a key into the heap
int insertKey(HEAP* heap, ELEMENT* element) {
	heap->size++; //increases the size of the heap by 1
	int i = heap->size - 1; //decreases the size of the heap by 1 and stores the value into a variable
	heap->H[i] = element; //stores the element into the heap

	while (i != 0 && heap->H[(i - 1) / 2]->key > heap->H[i]->key) { //loops while the node's child has a greater key value than the current node
		ELEMENT* tempElement = heap->H[i]; //creates a new element that stores the node
		heap->H[i] = heap->H[(i - 1) / 2]; //stores the child in the current position
		heap->H[(i - 1) / 2] = tempElement; //stores the node in tempElement in the child's former position
		i = (i - 1) / 2; //stores the node's child in i
	}
	return i + 1; //returns i + 1
}

//function that gets the smallest value from the heap
void extractMin(HEAP* heap, int flag) {
	if (heap->size <= 0) { //checks if the size of the heap is 0
		fprintf(stderr, "Error: heap is empty\n"); //prints that the heap is empty
		return; //exits the function
	}

	if (heap->size == 1) { //checks if there is only one element in the heap
		fprintf(stdout, "Element with key %lf extracted from the heap\n", heap->H[0]->key); //prints that the element was removed, and prints the value of the key
		heap->size = heap->size - 1; //decreases the size of the heap by 1
		if (flag == 2 || flag == 3) { //checks if the value of the flag is 2 or 3
			fprintf(stdout, "Number of Heapify calls triggered by ExtractMin: %d\n", numHeapifyCalls); //prints the number of heapify calls made
		}
		return; //exits the function
	}

	fprintf(stdout, "Element with key %lf extracted from the heap\n", heap->H[0]->key); //prints that the element was removed, and prints the value of the key
	heap->H[0] = heap->H[heap->size - 1]; //decreases the size of the heap by 1 and stores it in the first index of the heap
	heap->size = heap->size - 1; //decreases the size of the heap by 1

	numHeapifyCalls = 0; //resets the number of heapify calls back to 0
	heapify(heap, 0); //calls heapify on the heap

	if (flag == 2 || flag == 3) { //checks if the value of the flag is 2 or 3
		fprintf(stdout, "Number of Heapify calls triggered by ExtractMin: %d\n", numHeapifyCalls); //prints the number of heapify calls made
	}
}

//function that decreases the key to a specific location in the heap
void decreaseKey(HEAP* heap, int position, double newKey) {
	heap->H[position]->key = newKey; //sets the value of the key with a new value

	while (position != 0 && heap->H[(position - 1) / 2]->key > heap->H[position]->key) { //loops while the child's key value is larger than the current key's value
		ELEMENT* tempElement = heap->H[position]; //stores the position in a temporary element
		heap->H[position] = heap->H[(position - 1) / 2]; //stores the child in the current position
		heap->H[(position - 1) / 2] = tempElement; //stores the node in tempElement in the child's former position
		position = (position - 1) / 2; //stores the position in a variable
	}
}

//function that performs heapify on the heap
HEAP* heapify(HEAP* heap, int index) {
	numHeapifyCalls++; //increments the number of heapify calls by 1 whenever the method is called
	int smallest = index; //stores the index into a variable
	int left = 2 * index + 1; //stores the left child
	int right = 2 * index + 2; //stores the right child

	if (left < heap->size && heap->H[left]->key < heap->H[smallest]->key) //checks if the left child's key is smaller than the current smallest key
		smallest = left; //sets the left node as the smallest node
	if (right < heap->size && heap->H[right]->key < heap->H[smallest]->key) //checks if the right child's key is smaller than the current smallest key
		smallest = right; //sets the right node as the smallest node

	if (smallest != index) { //checks if the smallest nodex is not the current index
		ELEMENT* tempElement = heap->H[index]; //stores the current index into a temporary element
		heap->H[index] = heap->H[smallest]; //stores the smallest node into the current index
		heap->H[smallest] = tempElement; //sets the node in temporary as the smallest node
		heapify(heap, smallest); //calls heapify on the heap
	}
	return heap; //returns the heap
}

//function that builds the heap
int buildHeap(HEAP* heap) {
	numHeapifyCalls = 0; //resets the number of heapify calls made to 0

	for (int i = heap->size / 2 - 1; i >= 0; i--) { //loops while the current node is not a leaf node
		heapify(heap, i); //calls heapify
	}
	return numHeapifyCalls; //returns the number of heapify calls made
}

//function that checks if the heap is a min heap
int isMinHeap(HEAP* heap) {
	for (int i = 0; i <= (heap->size - 2) / 2; i++) { //loops while the current node is not a leaf node
		if (heap->H[i]->key > heap->H[2 * i + 1]->key || (2 * i + 2 < heap->size && heap->H[i]->key > heap->H[2 * i + 2]->key)) //checks if the minHeap holds up
			return 0; //exits the loop
	}
	return 1; //exits the function
}