//Arnav Babel
//ASU ID: 1225345329

#include "list_read.h"
#include "list_write.h"
#include <stdio.h>
#include <stdlib.h>

//function that appends a node into the list
NODE * listAppend(LIST *pLIST, double key){
    NODE* pNODE = new NODE; //creates a new node
    pNODE->key = key; //sets the node's key with the user's key
    pNODE->next = NULL; //sets the next node to be null

    if (pLIST->head == NULL) { //checks if the list is empty
        pLIST->head = pNODE; //sets the head to the new node
        pLIST->tail = pNODE; //sets the tail to the new node
    }
    else {
        pLIST->tail->next = pNODE; //sets the node after the tail to be the new tail
        pLIST->tail = pNODE; //sets the new node to be the tail of the list
    }

    fprintf(stdout, "Node with key %lf appended\n", pNODE->key); //prints that the node was appended

    return pNODE; //returns the node
}

//function that deletes a node from the list
NODE* listDelete(LIST* pLIST, double key) {
    NODE* pNODE = pLIST->head; //initializes the head node
    NODE* prev = pLIST->head; //initializes the previous node
    
    while (pNODE != NULL) { //loops while the node is not null
        if (pNODE->key == key) { //checks if the keys match
            fprintf(stdout, "Query %lf FOUND in list\n", pNODE->key); //prints that the node was found
            if (pNODE == pLIST->head) { //checks if the node to be deleted is the head node
                fprintf(stdout, "Node with key %lf deleted\n", pNODE->key); //prints that the node was deleted
                pLIST->head = pNODE->next; //sets the next node to be the new head node
                delete pNODE; //deletes the node
                return 0; //exits the loop
            }
            prev->next = pNODE->next; //updates the pointers
            fprintf(stdout, "Node with key %lf deleted\n", pNODE->key); //prints that the node was deleted
            delete pNODE; //deletes the node
            return 0; //exits the loop
        }
        else {
            prev = pNODE; //sets the previous node to be the current node
            pNODE = pNODE->next; //moves to the next node in the list
        }
    }

    fprintf(stdout, "Query %lf NOT FOUND in list\n", key); //prints that the key was not found
    fprintf(stdout, "There is no node with key %lf in list\n", key); //prints that the node with the key does not exist

    return NULL; //returns null
}

//function that inserts a node into the list
NODE * listInsert(LIST *pLIST, double key){
    NODE* pNODE = (NODE*)malloc(sizeof(NODE)); //allocates memory for the new node

    if (pNODE == NULL) { //checks if the current node is empty
        fprintf(stderr, "Memory allocation failed\n"); //prints that the node could not be inserted
        exit(1); //exits the function
    }

    pNODE->key = key; //sets the node's key to be the user's key
    pNODE->next = pLIST->head; //sets the next node to be the head node;
    pLIST->head = pNODE; //sets the current node to be the head node
    fprintf(stdout, "Node with key %lf inserted\n", pNODE->key); //prints that the node was inserted

    return pNODE; //returns the node
}