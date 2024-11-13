#ifndef _list_read_h
#define _list_read_h 1
#include <stdio.h>
#include <float.h>
#include "structs.h"

int    listPrint(FILE *, LIST *);
NODE * listSearch(LIST *pLIST, double query);
double listMax(LIST *);
double listMin(LIST *);
double listSum(LIST *);

#endif
