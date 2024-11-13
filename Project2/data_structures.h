//Arnav Babel
//Student ID # 1225345329

#ifndef _data_structures_h
#define _data_structures_h

typedef struct TAG_ELEMENT{
    double key;
}ELEMENT;

typedef struct TAG_HEAP{
    int capacity; /* capacity of the heap */
    int size; /* current size of the heap */
    int* array; /* pointer to the heap array */
    ELEMENT **H; /* array of pointers to ELEMENT */
}HEAP;
#endif 