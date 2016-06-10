/* Output Verification Module

This module verifies that the output results for water and PCM conform
to the law of conservation of energy, and throws warnings if either
does not.

Authors: Thulasi Jegatheesan, Spencer Smith, Ned Nedialkov, and Brooks
MacLachlan

Date Last Revised: June 10, 2016

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "parameters.h"

void verify_output(float tempW[], float tempP[], float eW[], float eP[], struct parameters params, int sizeOfResults){

    int deltaTime = params.tstep;

    /* Using malloc() here to increase max array size. Should work as long as tstep is 1.0 or greater.
        If these arrays are initialized simply by "float eCoil[sizeOfResults-1]", for example, the program will
        require that tstep be at least 1.3 */
    float *eCoil, *ePCM, *eWater;
    eCoil = (float *) malloc((sizeOfResults - 1) * sizeof(float));
    ePCM = (float *) malloc((sizeOfResults - 1) * sizeof(float));
    eWater = (float *) malloc((sizeOfResults - 1) * sizeof(float));
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

    if(errorWater > params.ConsTol){
        printf("Warning: There is greater than %f%% relative error between the energy in the water output and the expected output based on the law of conservation of energy.\n", params.ConsTol);
    }

    if(errorPCM > params.ConsTol){
        printf("Warning: There is greater than %f%% relative error between the energy in the PCM output and the expected output based on the law of conservation of energy.\n", params.ConsTol);
    }

    return;
}
