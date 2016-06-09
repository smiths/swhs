#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void verify_output(float tempW[], float tempP[], float eW[], float eP[], struct parameters params, int sizeOfResults){

    int deltaTime = params.tstep;

    float eCoil[sizeOfResults-1], ePCM[sizeOfResults-1], eWater[sizeOfResults-1];
    int i;
    for(i = 0; i < sizeOfResults-1; i++){
        eCoil[i] = params.hc * params.Ac * deltaTime * (params.Tc - tempW[i+1] + params.Tc - tempW[i]) / 2;
        ePCM[i] = params.hp * params.Ap * deltaTime * (tempW[i+1] - tempP[i+1] + tempW[i] - tempP[i]) / 2;
        eWater[i] = eCoil[i] - ePCM[i];
    }
    float eWaterTotal, ePCMTotal = 0;
    int j;
    for(j = 0; j < sizeOfResults-1; j++){
        eWaterTotal += eWater[j];
        ePCMTotal += ePCM[j];
    }

    float errorWater, errorPCM;

    errorWater = fabs(eWaterTotal - eW[sizeOfResults]) / eW[sizeOfResults] * 100;

    errorPCM = fabs(ePCMTotal - eP[sizeOfResults]) / eP[sizeOfResults] * 100;

    printf("%f \t %f \t %f \n", errorPCM, ePCMTotal, eP[sizeOfResults]);

    if(errorWater > params.ConsTol){
        printf("Warning: There is greater than %f%% relative error between the energy in the water output and the expected output based on the law of conservation of energy.\n", params.ConsTol);
    }

    if(errorPCM > params.ConsTol){
        printf("Warning: There is greater than %f%% relative error between the energy in the PCM output and the expected output based on the law of conservation of energy.\n", params.ConsTol);
    }

    return;
}
