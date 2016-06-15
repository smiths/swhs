/* Energy Module, when Tp = Tmelt

This module uses the input parameters in params and the temperatures of
water and PCM calculated by main.c and the temperature2 function to specify
the equations that govern the change in energy of the water and PCM

Authors: Thulasi Jegatheesan, Spencer Smith, Ned Nedialkov, and Brooks
MacLachlan

Date Last Revised: June 10, 2016

Governing Equations:

Ew(t) = Cw * Mw * (Tw(t) - Tinit)

Ep(t) = Epmelt_init + Qp(t)

*/

#include <stdio.h>
#include <stdlib.h>
#include "parameters.h"
#include "energy2.h"

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
