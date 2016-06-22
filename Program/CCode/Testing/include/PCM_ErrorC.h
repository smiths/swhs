#include "parameters.h"

#ifndef PCM_ERRORC_H_INCLUDED
#define PCM_ERRORC_H_INCLUDED

double PCM_ErrorC(const char Cfile1[], const char Cfile2[], const char comparator[], struct parameters params);
double errorCalcC(double result1[], double result2[], int sizeOfResults);

#endif // PCM_ERRORC_H_INCLUDED
