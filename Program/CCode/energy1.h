#include <stdio.h>
#include <stdlib.h>
#include "parameters.h"

float energy1Wat(float tWat, struct parameters params){

    float eWat;

    // Change in energy in water when T < Tmelt
    eWat = params.C_w * params.Mw * (tWat - params.Tinit);

    return eWat;
}

float energy1PCM(float tPCM, struct parameters params){

    float ePCM;

    // Change in energy in PCM when T < Tmelt
    ePCM = params.C_ps * params.Mp * (tPCM - params.Tinit);

    return ePCM;
}
