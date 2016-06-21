#include <stdio.h>
#include <stdlib.h>
#include "parameters.h"
#include "event.h"

/* Event Module, for Tp = Tmelt

This module returns a double that stops integration of the Temperature
ODEs Module, when Tp < Tmelt, once Tp = Tmelt.

Authors: Thulasi Jegatheesan, Spencer Smith, Ned Nedialkov, and Brooks
MacLachlan

Date Last Revised: June 21, 2016

*/

double event1(double tempP, struct parameters params){
    double value = tempP - params.Tmelt;

    return value;
}

/* Event Module, for phi = 1

This module returns a double that stops integration of the Temperature
ODEs Module, when Tp = Tmelt, once melt fraction, phi, is 1.

Authors: Thulasi Jegatheesan, Spencer Smith, Ned Nedialkov, and Brooks
MacLachlan.

Date Last Revised: June 21, 2016

*/

double event2(double latentHeat, struct parameters params){

    double phi = latentHeat / (params.Hf * params.Mp);

    double value = phi - 1;

    return value;
}
