#include "parameters.h"

#ifndef PCM_ERROR_H_INCLUDED
#define PCM_ERROR_H_INCLUDED

double PCM_Error(const char Ffile[], const char Cfile[], const char comparator[], struct parameters params);
double errorCalc(double result1[], double result2[], int sizeOfResults);

#endif // PCM_ERROR_H_INCLUDED
