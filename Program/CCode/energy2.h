#include <stdio.h>
#include <stdlib.h>
#include "parameters.h"

float energy2Wat(float tWat, struct parameters params){

    float eWat;

    // Change in energy in water when T = Tmelt
    eWat = params.C_w * params.Mw * (tWat - params.Tinit);

    return eWat;
}

float energy2PCM(float latentHeat, struct parameters params){

    float ePCM;

    // Change in energy in PCM when T = Tmelt
    ePCM = params.Epmelt_init + latentHeat;

    return ePCM;
}
