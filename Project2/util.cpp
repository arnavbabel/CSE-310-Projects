//Arnav Babel
//Student ID # 1225345329

#include "util.h"

#include <stdio.h>
#include <string.h>

//function that collects and stores the user's inputted values
int nextInstruction(char* Word, double* Key, int* position) {
    int returnV; //variable that stores the inputted values

    fscanf(stdin, "%s", Word); //scans for the user's inputted function

    if (strcmp(Word, "Stop") == 0) return 1; //checks if stop was entered by the user
    if (strcmp(Word, "Print") == 0) return 1; //checks if print was entered by the user
    if (strcmp(Word, "Write") == 0) return 1; //checks if write was entered by the user
    if (strcmp(Word, "Read") == 0) return 1; //checks if read was entered by the user
    if (strcmp(Word, "ExtractMin") == 0) return 1; //checks if extract min was entered by the user

    if (strcmp(Word, "Init") == 0) { //checks if Init was inputted by the user
        returnV = fscanf(stdin, "%lf", Key); //scans for the value of the key and stores it in returnV
        if (returnV == 1) { //checks if a value was read
            return 1; //returns 1 if read
        }
        else {
            return 0; //returns 0 if not read
        }
    }

    if (strcmp(Word, "Insert") == 0) { //checks if Insert was inputted by the user
        returnV = fscanf(stdin, "%lf", Key); //scans for the value of the key and stores it in returnV
        if (returnV == 1) { //checks if a value was read
            return 1; //returns 1 if read
        }
        else {
            return 0; //returns 0 if not read
        }
    }

    if (strcmp(Word, "DecreaseKey") == 0) { //checks if DecreaseKey was inputted by the user
        returnV = fscanf(stdin, "%d %lf", position, Key); //scans for the value of the position and key, and stores them in returnV
        if (returnV == 2) { //checks if two values were read
            return 1; //returns 1 if read
        }
        else {
            return 0; //returns 0 if not read
        }
    }

    return 0; //exits the function
}