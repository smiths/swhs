#include <stdio.h>
#include <stdlib.h>
#include "parameters.h"

float energy3Wat(float tWat, struct parameters params){

    float eWat;

    // Change in energy in water when T > Tmelt
    eWat = params.C_w * params.Mw * (tWat - params.Tinit);

    return eWat;
}

float energy3PCM(float tPCM, struct parameters params){

    float ePCM;

    // Change in energy in PCM when T > Tmelt
    ePCM = params.Epmelt_init + params.Ep_melt3 + params.C_pl * params.Mp * (tPCM - params.Tmelt);

    return ePCM;
}

