#include "parameters.h"

#ifndef PCM_ERRORM_H_INCLUDED
#define PCM_ERRORM_H_INCLUDED

double PCM_ErrorM(const char Mfile[], const char Cfile[], const char comparator[], struct parameters params);
double errorCalcInterp(double time1[], double time2[], double result1[], double result2[], int sizeOfResults1, int sizeOfResults2);

#endif // PCM_ERRORM_H_INCLUDED
