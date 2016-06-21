#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "parameters.h"
#include "load_params.h"
#include "PCM_Error.h"

double PCM_Error(const char Ffile[], const char Cfile[], const char comparator[], struct parameters params){

    FILE * fPointer;
    fPointer = fopen(Ffile, "r");
    int i;
    char c;
    for(i = 0; i < 23; i++){
        do{
            c = fgetc(fPointer);
        }while(c != '\n');
    }
    int sizeOfResults = ceil(params.tfinal / params.tstep);
    double time1[sizeOfResults], tempW1[sizeOfResults], tempP1[sizeOfResults], eW1[sizeOfResults], eP1[sizeOfResults], tNoPCM[sizeOfResults], eNoPCM[sizeOfResults];
    double meltFrac, eTot;
    int iteration;
    int counter1 = 0;
    while(!feof(fPointer)){
        fscanf(fPointer, "%lf %d %lf %lf %lf %lf %lf %lf %lf %lf", &time1[counter1], &iteration, &tempW1[counter1], &tempP1[counter1], &eP1[counter1], &eW1[counter1], &eTot, &meltFrac, &tNoPCM[counter1], &eNoPCM[counter1]);
        counter1++;
    }
    fclose(fPointer);


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
        error = errorCalc(tempW1, tempW2, sizeOfResults);
    }
    else if(strcmp("TPCM", comparator) == 0){
        error = errorCalc(tempP1, tempP2, sizeOfResults);
    }
    else if(strcmp("EWat", comparator) == 0){
        error = errorCalc(eW1, eW2, sizeOfResults);
    }
    else if(strcmp("EPCM", comparator) == 0){
        error = errorCalc(eP1, eP2, sizeOfResults);
    }
    else if(strcmp("TWatNoP", comparator) == 0){
        error = errorCalc(tNoPCM, tempW2, sizeOfResults);
    }
    else if(strcmp("EWatNoP", comparator) == 0){
        error = errorCalc(eNoPCM, eW2, sizeOfResults);
    }

    return error;
}

double errorCalc(double result1[], double result2[], int sizeOfResults){
    double delta[sizeOfResults];
    double deltaSumSquares = 0;
    double resultSumSquares = 0;
    int i;
    for(i = 0; i < sizeOfResults; i++){
        delta[i] = fabs(result1[i] - result2[i]);
        deltaSumSquares += pow(delta[i], 2);
        resultSumSquares += pow(result1[i], 2);
    }
    double deltaNorm, resultNorm;
    deltaNorm = sqrt(deltaSumSquares);
    resultNorm = sqrt(resultSumSquares);
    double error;
    error = deltaNorm / resultNorm;
    return error;
}
