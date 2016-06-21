#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "parameters.h"
#include "load_params.h"
#include "PCM_ErrorM.h"
#include "linterp.h"

double PCM_ErrorM(const char Mfile[], const char Cfile[], const char comparator[], struct parameters params){

    FILE * fPointer;
    fPointer = fopen(Mfile, "r");
    int i;
    char c;
    for(i = 0; i < 36; i++){
        do{
            c = fgetc(fPointer);
        }while(c != '\n');
    }
    int sizeOfResults = ceil(params.tfinal / params.tstep)+1;
    double time1[sizeOfResults], tempW1[sizeOfResults], tempP1[sizeOfResults], eW1[sizeOfResults], eP1[sizeOfResults];
    double eTot;
    int counter1 = 0;
    while(!feof(fPointer)){
        fscanf(fPointer, "%lf %lf %lf %lf %lf %lf", &time1[counter1], &tempW1[counter1], &tempP1[counter1], &eP1[counter1], &eW1[counter1], &eTot);
        counter1++;
    }
    fclose(fPointer);

    int sizeOfResultsM = 1;
    while(1){
        if(time1[sizeOfResultsM] == params.tfinal){
            sizeOfResultsM++;
            break;
        }
        sizeOfResultsM++;
    }


    FILE * cPointer;
    cPointer = fopen(Cfile, "r");
    int j;
    char ch;
    for(j = 0; j < 34; j++){
        do{
            ch = fgetc(fPointer);
        }while(ch != '\n');
    }

    double time2[sizeOfResults], tempW2[sizeOfResults], tempP2[sizeOfResults], eW2[sizeOfResults], eP2[sizeOfResults];
    double eTot2;
    int counter2= 0;
    while(!feof(fPointer)){
        fscanf(fPointer, "%lf %lf %lf %lf %lf %lf", &time2[counter2], &tempW2[counter2], &tempP2[counter2], &eW2[counter2], &eP2[counter2], &eTot2);
        counter2++;
    }
    fclose(cPointer);

    double error;

    if(strcmp("TWat", comparator) == 0){
        error = errorCalcInterp(time1, time2, tempW1, tempW2, sizeOfResultsM, sizeOfResults);
    }
    else if(strcmp("TPCM", comparator) == 0){
        error = errorCalcInterp(time1, time2, tempP1, tempP2, sizeOfResultsM, sizeOfResults);
    }
    else if(strcmp("EWat", comparator) == 0){
        error = errorCalcInterp(time1, time2, eW1, eW2, sizeOfResultsM, sizeOfResults);
    }
    else if(strcmp("EPCM", comparator) == 0){
        error = errorCalcInterp(time1, time2, eP1, eP2, sizeOfResultsM, sizeOfResults);
    }
    printf("%f\n", error);
    return error;
}

double errorCalcInterp(double time1[], double time2[], double result1[], double result2[], int sizeOfResultsM, int sizeOfResults){
    double time2Shifted[sizeOfResultsM];
    double result2Interpolated[sizeOfResultsM];
    int i;
    int j = 1;
    for(i = 0; i < sizeOfResultsM; i++){
        time2Shifted[i] = time1[i];
        while(j < sizeOfResults){
                if(time2[j] >= time2Shifted[i]){
                    result2Interpolated[i] = linterp(time2[j-1], time2[j], result2[j-1], result2[j], time2Shifted[i]);
                    break;
                }
                j++;
        }
    }

    double delta[sizeOfResultsM];
    double deltaSumSquares = 0;
    double resultSumSquares = 0;
    int k;
    for(k = 0; k < sizeOfResultsM; k++){
        delta[k] = fabs(result1[k] - result2Interpolated[k]);
        deltaSumSquares += pow(delta[k], 2);
        resultSumSquares += pow(result1[k], 2);
    }
    double deltaNorm, resultNorm;
    deltaNorm = sqrt(deltaSumSquares);
    resultNorm = sqrt(resultSumSquares);
    double error;
    error = deltaNorm / resultNorm;
    return error;
}

