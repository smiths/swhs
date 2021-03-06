/* Energy Module, when Tp < Tmelt

This module uses the input parameters in params and the temperatures of
water and PCM calculated by main.c and the temperature1 function to specify
the equations that govern the change in energy of the water and PCM.

Authors: Thulasi Jegatheesan, Spencer Smith, Ned Nedialkov, and Brooks
MacLachlan

Date Last Revised: June 10, 2016

Governing Equations:

Ew(t) = Cw * Mw * (Tw(t) - Tinit)

Ep(t) = C_ps * Mp * (Tp(t) - Tinit)

*/

#include <stdio.h>
#include <stdlib.h>
#include "parameters.h"
#include "energy1.h"

double energy1Wat(double tWat, struct parameters params){

    double eWat;

    // Change in energy in water when T < Tmelt
    eWat = params.C_w * params.Mw * (tWat - params.Tinit);

    return eWat;
}

double energy1PCM(double tPCM, struct parameters params){

    double ePCM;

    // Change in energy in PCM when T < Tmelt
    ePCM = params.C_ps * params.Mp * (tPCM - params.Tinit);

    return ePCM;
}
