//Arnav Babel
//Student ID # 1225345329

#include "util.h"
#include "data_structures.h"
#include "heap.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <string>

using namespace std;

//method declaration
void read(HEAP*, char**, double, int);
void write(HEAP*, char**);

//main method
int main(int argc, char** argv) {
    //variable declaration
    HEAP* heap;
    double key;
    int returnV;
    char Word[100];
    int flag;
    int realKey;

    if (argc < 4) { //checks if the number of arguments passed is less than 4
        fprintf(stderr, "Usage: %s <ifile> <ofile>\n", argv[0]); //prints the files that have to be passed
        exit(0); //exits the program
    }

    flag = atoi(argv[1]); //stores the value of the flag into a variable
    if ((flag != 0) && (flag != 1) && (flag != 2) && (flag != 3)) { //checks if the value of flag is not 0, 1, 2, or 3
        fprintf(stderr, "Error: flag value should be 0, 1, 2, or 3"); //prints that the value of the flag should be 0, 1, 2, or 3
        exit(0); //exits the program
    }

    heap = nullptr; //initializes the heap as empty

    heap = (HEAP*)calloc(1, sizeof(HEAP)); //allocates memory for the heap
    if (heap == nullptr) { //checks if memory for the heap was not allocated
        fprintf(stderr, "Error: calloc failed\n"); //prints that memory was not allocated
        exit(0); //exits the program
    }

    heap->capacity = 0; //sets the capacity of the heap to be 0
    heap->size = 0; //sets the size of the heap to be 0
    heap->H = nullptr; //sets each element of the heap to be null 

    while (1) {
        returnV = nextInstruction(Word, &key, &realKey); //calls the nextInstruction to store the user's inputted instructions and values

        if (returnV == 0) { //checks if the instruction that the user entered exists
            fprintf(stderr, "Warning: Invalid instruction: %s\n", Word); //prints that the instruction was invalid
            continue; //continues the program
        }

        if (strcmp(Word, "Stop") == 0) { //checks if Stop was entered by the user
            fprintf(stdout, "Instruction: Stop\n"); //prints that the instruction was Stop
            return 0; //exits the program
        }

        if (strcmp(Word, "Init") == 0) { //checks if Init was entered by the user
            heap = init((int)key); //calls the init function and stores the value in heap
            continue; //continues the program
        }

        if (strcmp(Word, "Print") == 0) { //checks if Print was entered by the user
            fprintf(stdout, "Instruction: Print\n"); //prints that the instruction was Print
            printHeap(heap); //calls the printHeap method
            continue; //continues the program
        }

        if (strcmp(Word, "Write") == 0) { //checks if Write was entered by the user
            fprintf(stdout, "Instruction: Write\n"); //prints that the instruction was Write
            write(heap, argv);
            continue; //continues the program
        }

        if (strcmp(Word, "Read") == 0) { //checks if Read was entered by the user
            fprintf(stdout, "Instruction: Read\n"); //prints that the instructoin was Read
            read(heap, argv, key, flag); //calls the read function
            continue; //continues the program
        }


        if (strcmp(Word, "Insert") == 0) { //checks if Insert was entered by the user
            fprintf(stdout, "Instruction: Insert %lf\n", key); //prints that the instruction Insert was called, and prints the value being inserted
            if (heap == nullptr) { //checks if the heap exists
                fprintf(stderr, "Error: heap is NULL\n"); //prints that the heap is empty
                continue; //continues the program
            }

            if (heap->size == heap->capacity) { //checks if the size of the heap is the same as the capacity
                fprintf(stderr, "Error: heap is full\n"); //prints that the heap is full
                continue; //continues the program
            }

            ELEMENT* element = (ELEMENT*)malloc(sizeof(ELEMENT)); //allocates memory for the new element
            if (element == nullptr) { //checks if memory was successfully allocated for the new element
                fprintf(stderr, "Error: Memory allocation failed\n"); //prints that memory could not be allocated
                continue; //continues the program
            }

            element->key = key; //stores the value of the key as the element's key

            int location = insertKey(heap, element); //calls insertKey and stores the position where it was inserted

            if (flag == 1 || flag == 3) { //checks if the value of the flag is 1 or 3
                fprintf(stdout, "Element with key %lf inserted at location %d of the heap array\n", key, location); //prints the key that was inserted and it's location in the array
            }
            else {
                fprintf(stdout, "Element with key %lf inserted into the heap\n", key); //prints that the key was inserted into the heap
            }
            continue; //continues the program
        }

        if (strcmp(Word, "ExtractMin") == 0) { //checks if ExtractMin was entered by the user
            fprintf(stdout, "Instruction: ExtractMin\n"); //prints that the instruction ExtractMin was called
            
            if (heap == nullptr) { //checks if the heap exists
                fprintf(stderr, "Error: heap is NULL\n"); //prints that the heap is empty
                continue; //continues the program
            }

            if (heap->size == 0) { //checks if the size of the heap is 0
                fprintf(stderr, "Error: heap is empty\n"); //prints that the heap is empty
                continue; //continues the program
            }

            extractMin(heap, flag); //calls extractMin
            continue; //continues the program
        }

        if (strcmp(Word, "DecreaseKey") == 0) { //checks if DecreaseKey was entered by the user
            fprintf(stdout, "Instruction: DecreaseKey %d %lf\n", realKey, key); //prints that DecreaseKey was called, and prints the value being decreased to the new position
            
            realKey = realKey - 1; //decreases the value of realKey by 1
            
            if (heap == nullptr) { //checks if the heap exists
                fprintf(stderr, "Error: heap is NULL\n"); //prints that the heap is empty
                continue; //continues the program
            }

            if (heap->size == 0) { //checks if the size of the heap is 0
                fprintf(stderr, "Error: heap is empty\n"); //prints that the heap is empty
                continue; //continues the program
            }

            if (realKey < 0 || realKey >= heap->size || heap->H[realKey]->key <= key) { //checks if the current position is correct, or if the node's key is smaller than the key being decreased
                fprintf(stderr, "Error: invalid call to DecreaseKey\n"); //prints that DecreaseKey could not execute
                continue; //continues the program
            }

            decreaseKey(heap, realKey, key); //calls decreaseKey
            continue; //continues the program
        }
    }

    return 1; //exits the loop
}

void read(HEAP* heap, char** argv, double key, int flag) {
    if (heap == nullptr) { //checks if the heap exists
        fprintf(stderr, "Error: heap is NULL\n"); //prints that the heap is null
    }

    FILE* readFile = fopen(argv[2], "r"); //stores the file to be read from into a variable
    if (!readFile) { //checks if the file can be opened
        fprintf(stderr, "Error: cannot open file %s\n", argv[2]); //prints that the file could not be opened
    }

    int n = 0;
    fscanf(readFile, "%d", &n); //scans the file

    if (heap->capacity < n) { //checks if the heap's capacity is less than n
        heap->capacity = n; //sets the capacity to be the value of n
        heap->H = (ELEMENT**)realloc(heap->H, heap->capacity * sizeof(ELEMENT*)); //reallocates memory for the heap's capacity
        if (heap->H == nullptr) { //checks if the heap exists
            fprintf(stderr, "Error: Memory reallocation failed\n"); //prints that the heap's memory reallocation failed
            fclose(readFile); //closes the file
        }
    }

    for (int i = 0; i < n; i++) { //loops while i is less than the capacity
        fscanf(readFile, "%lf", &key); //reads each key value from the file
        
        ELEMENT* element = (ELEMENT*)malloc(sizeof(ELEMENT)); //allocates memory for a new element

        if (element == nullptr) { //checks if element exists
            fprintf(stderr, "Error: Memory allocation failed\n"); //prints that memory could not be allocated for element
            fclose(readFile); //closes the file
            continue; //continues the program
        }
        element->key = key; //stores each key in element
        heap->H[i] = element; //stores each element in the heap
    }

    heap->size = n; //sets the size of the heap to be n

    if (!isMinHeap(heap)) { //checks if the heap is a minHeap
        if (flag == 2 || flag == 3) { //checks if the value of the flag is 2 or 3
            fprintf(stdout, "Input array is NOT a MinHeap\n"); //prints that the heap is not a minHeap
            fprintf(stdout, "Call BuildHeap\n"); //prints that buildHeap will be called
        }

        int numHeapifyCalls = buildHeap(heap); //stores the value build returns into a variable
        if (flag == 2 || flag == 3) { //checks if the value of the flag is 2 or 3
            fprintf(stdout, "Number of Heapify calls triggered by BuildHeap: %d\n", numHeapifyCalls); //prints the number of calls to heapify
        }
    }

    fclose(readFile); //closes the file
}

void write(HEAP* heap, char** argv) {
    if (heap == nullptr) { //checks if the heap exists
        fprintf(stderr, "Error: heap is NULL"); //prints that the heap is null
    }

    FILE* writeFile = fopen(argv[3], "w"); //stores the file to be written to into a variable
    if (!writeFile) { //checks if the file can be opened
        fprintf(stderr, "Error: cannot open file %s\n", argv[3]); //prints that the file could not be opened
    }

    fprintf(writeFile, "%d\n", heap->size); //prints the heap size in the file
    
    for (int i = 0; i < heap->size; i++) { //loops while i is less than the size of the heap
        fprintf(writeFile, "%lf\n", heap->H[i]->key); //prints each key value from the file
    }
    fclose(writeFile); //closes the file
}