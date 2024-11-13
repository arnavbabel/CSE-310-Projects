#include "list_read.h"
#include <stdio.h>
#include <stdlib.h>

int listPrint(FILE *pFILE, LIST *pLIST){
    NODE *pNODE;

    if (!pLIST){
        // This should not happen, if called correctly.
        fprintf(stderr, "Error in listPrint: NULL list\n");
        return 0;
    }else{
        pNODE = pLIST->head;
        while (pNODE){
            fprintf(pFILE, "%lf\n", pNODE->key);
            pNODE = pNODE->next;
        }
    }
    return 1;
}


NODE * listSearch(LIST *pLIST, double query){
    NODE *pNODE;

    if (pLIST == NULL){
        // This should not happen, if called correctly.
        fprintf(stderr, "Error in listSearch: NULL list\n");
        exit (0);
    }

    pNODE = pLIST->head;
    while (pNODE){
        if (pNODE->key == query){
            // Successful search.
            fprintf(stdout, "Query %lf FOUND in list\n", pNODE->key);
            return pNODE;
        }
        pNODE = pNODE->next;
    }

    // Unsuccessful search.
    fprintf(stdout, "Query %lf NOT FOUND in list\n", query);
    pNODE = NULL;
    return pNODE;
}


double listMax(LIST *pLIST){
    double max;
    NODE *pNODE;

    max = -DBL_MAX;

    if (pLIST == NULL){
        // This should not happen, if called correctly.
        fprintf(stderr, "Error in listMax: NULL list\n");
        exit(0);
    }else if (pLIST->head == NULL){
        // This may happen.
        fprintf(stderr, "Warning in listMax: DBL_MIN is taken as the max of an empty list\n");
    }else{
        pNODE = pLIST->head;
        max   = pNODE->key;
        while (pNODE){
            if (pNODE->key > max) max = pNODE->key;
            pNODE = pNODE->next;
        }
    }
    return max;
}


double listMin(LIST *pLIST){
    double min;
    NODE *pNODE;

    min = DBL_MAX;

    if (pLIST == NULL){
        // This should not happen, if called correctly.
        fprintf(stderr, "Error in listMin: NULL list\n");
        exit(0);
    }else if (pLIST->head == NULL){
        // This may happen.
        fprintf(stderr, "Warning in listMin: DBL_MAX is taken as the min of an empty list\n");
    }else{
        pNODE = pLIST->head;
        min   = pNODE->key;
        while (pNODE){
            if (pNODE->key < min) min = pNODE->key;
            pNODE = pNODE->next;
        }
    }
    return min;
}


double listSum(LIST *pLIST){
    double sum;
    NODE *pNODE;

    sum = 0;
    if (pLIST == NULL){
        // This should not happen, if called correctly.
        fprintf(stderr, "Error in listSum: NULL list\n");
        exit(0);
    }else{
        pNODE = pLIST->head;
        while (pNODE){
            sum = sum + pNODE->key;
            pNODE = pNODE->next;
        }
    }
    return sum;
}


