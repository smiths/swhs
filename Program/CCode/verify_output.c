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
#include "verify_output.h"

int verify_output(double tempW[], double tempP[], double eW[], double eP[], struct parameters params, int sizeOfResults){

    int deltaTime = params.tstep;

    /* Using malloc() here to increase max array size. Should work as long as tstep is 1.0 or greater.
        If these arrays are initialized simply by "float eCoil[sizeOfResults-1]", for example, the program will
        require that tstep be at least 1.3 */
    double *eCoil, *ePCM, *eWater;
    eCoil = (double *) malloc((sizeOfResults - 1) * sizeof(double));
    ePCM = (double *) malloc((sizeOfResults - 1) * sizeof(double));
    eWater = (double *) malloc((sizeOfResults - 1) * sizeof(double));
    int i;
    for(i = 0; i < sizeOfResults-1; i++){
        eCoil[i] = params.hc * params.Ac * deltaTime * (params.Tc - tempW[i+1] + params.Tc - tempW[i]) / 2;
        ePCM[i] = params.hp * params.Ap * deltaTime * (tempW[i+1] - tempP[i+1] + tempW[i] - tempP[i]) / 2;
        eWater[i] = eCoil[i] - ePCM[i];
    }

    double eWaterTotal = 0;
    double ePCMTotal = 0;
    int j;
    for(j = 0; j < sizeOfResults-1; j++){
        eWaterTotal += eWater[j];
        ePCMTotal += ePCM[j];
    }

    double errorWater, errorPCM;

    errorWater = fabs(eWaterTotal - eW[sizeOfResults-1]) / eW[sizeOfResults-1] * 100;

    errorPCM = fabs(ePCMTotal - eP[sizeOfResults-1]) / eP[sizeOfResults-1] * 100;

    printf("%f, %f\n", errorPCM, errorWater);

    int warnings = 0;

    if(errorWater > params.ConsTol){
        printf("Warning: There is greater than %f%% relative error between the energy in the water output and the expected output based on the law of conservation of energy.\n", params.ConsTol);
        warnings += 1;
    }

    if(errorPCM > params.ConsTol){
        printf("Warning: There is greater than %f%% relative error between the energy in the PCM output and the expected output based on the law of conservation of energy.\n", params.ConsTol);
        warnings += 2;
    }

    return warnings;
}
