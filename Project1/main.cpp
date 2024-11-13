#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "list_read.h"
#include "list_write.h"

int main(int argc, char **argv){
    FILE *fp;
    LIST *pLIST;
    NODE *pNODE;
    double key, max, min, sum;
    int    returnV;
    char Word[100];

    printf("argc=%d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("The str value of argv[%d] is %s\n", i, argv[i]);
        printf("The int value of argv[%d] is %d\n\n", i, atoi(argv[i]));
    }

    if (argc < 3){
        fprintf(stderr, "Usage: %s <ifile> <ofile>\n", argv[0]);
        exit(0);
    }

    pLIST  = NULL;
    pNODE  = NULL;
    fp     = NULL;

    // Open the input file for reading.
    fp = fopen(argv[1], "r");
    if (!fp){
        fprintf(stderr, "Error: cannot open file %s\n", argv[1]);
        exit(0);
    }

    // Allocate memory for pLIST.
    pLIST = (LIST *) calloc(1, sizeof(LIST));
    if (!pLIST){
        fprintf(stderr, "Error: calloc failed\n");
        exit(0);
    }
    pLIST->head = NULL;
    pLIST->tail = NULL;


    // Read in the list from the input file, one node at a time.
    while ((returnV = fscanf(fp, "%lf", &key)) == 1){
        // The above line allocates memory for a new NODE
        pNODE = (NODE *) calloc(1, sizeof(NODE));
        // Fill in the fields of the new NODE
        pNODE->next = NULL;
        pNODE->key  = key;

        if (pLIST->head == NULL){
            // pLIST is an empty list (pLIST is not NULL).
            // pLIST->head == NULL implies pLIST->tail == NULL
            pLIST->head = pNODE;
            pLIST->tail = pNODE;
            // Now pLIST has one NODE.
        }else{
            // pLIST is a non-empty list (pLIST is at least one NODE).
            // pLIST->head != NULL implies pLIST->tail != NULL
            pLIST->tail->next = pNODE;
            pLIST->tail = pNODE;
            // Now pLIST has one additional NODE appended at the tail.
        }
    }
    // Always remember to close the file.
    fclose(fp);


    while (1){
        returnV = nextInstruction(Word, &key);

        if (returnV == 0){
            fprintf(stderr, "Warning: Invalid instruction: %s\n", Word);
            continue;
        }


        if (strcmp(Word, "Stop")==0){
            return 0;
        }


        if (strcmp(Word, "Print")==0){
            listPrint(stdout, pLIST);
            continue;
        }


        if (strcmp(Word, "Max")==0){
            max = listMax(pLIST);
            fprintf(stdout, "Max=%lf\n", max);
            continue;
        }


        if (strcmp(Word, "Min")==0){
            min = listMin(pLIST);
            fprintf(stdout, "Min=%lf\n", min);
            continue;
        }


        if (strcmp(Word, "Sum")==0){
            sum = listSum(pLIST);
            fprintf(stdout, "Sum=%lf\n", sum);
            continue;
        }


        if (strcmp(Word, "Write")==0){
            fp = fopen(argv[2], "w");
            if (!fp){
                fprintf(stderr, "Error: cannot open file %s\n", argv[2]);
                exit(0);
            }
            pNODE = pLIST->head;
            while (pNODE){
                fprintf(fp, "%lf\n", pNODE->key);
                pNODE = pNODE->next;
            }
            fclose(fp);
            continue;
        }


        if (strcmp(Word, "Search")==0){
            pNODE = NULL;
            pNODE = listSearch(pLIST, key);
            continue;
        }


        if (strcmp(Word, "Insert")==0){
            pNODE = listInsert(pLIST, key);
            continue;
        }


        if (strcmp(Word, "Append")==0){
            pNODE = listAppend(pLIST, key);
            continue;
        }


        if (strcmp(Word, "Delete")==0){
            pNODE = listDelete(pLIST, key);
            if (pNODE){
                free(pNODE);
            }
            continue;
        }
    }

    return 1;
}
