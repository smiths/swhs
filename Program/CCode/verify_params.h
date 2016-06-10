/* Input Verification Module

This module verifies that the input parameters comply with physical and
software constraints by throwing errors and warnings, respectively, if
any parameter does not.

Authors: Thulasi Jegatheesan, Spencer Smith, Ned Nedialkov, and Brooks
MacLachlan

Date Last Revised: June 10, 2016

*/

#include <stdio.h>
#include <stdlib.h>
#include "parameters.h"
#include "load_params.h"

void verify_params(struct parameters params){

    // Check that inputs are valid

    if(params.L <= 0){
        printf("Error: Tank length must be > 0");
        exit(EXIT_FAILURE);
    }
    else if(params.diam <= 0){
        printf("Error: Tank diameter must be > 0");
        exit(EXIT_FAILURE);
    }
    else if(params.Vp <= 0){
        printf("Error: PCM volume must be > 0");
        exit(EXIT_FAILURE);
    }
    else if(params.Vp >= params.Vt){
        printf("Error: PCM volume must be < tank volume");
        exit(EXIT_FAILURE);
    }
    else if(params.Ap <= 0){
        printf("Error: PCM area must be > 0");
        exit(EXIT_FAILURE);
    }
    else if(params.rho_p <= 0){
        printf("Error: rho_p must be > 0");
        exit(EXIT_FAILURE);
    }
    else if(params.Tmelt <= 0 || params.Tmelt >= params.Tc){
        printf("Error: Tmelt must be > 0 and < Tc");
        exit(EXIT_FAILURE);
    }
    else if(params.Tc <= params.Tinit){
        printf("Error: Tc must be > Tinit");
        exit(EXIT_FAILURE);
    }
    else if(params.Tc >= 100 || params.Tc <= 0){
        printf("Error: Tc must be > 0 and < 100");
        exit(EXIT_FAILURE);
    }
    else if(params.C_ps <= 0){
        printf("Error: C_ps must be > 0");
        exit(EXIT_FAILURE);
    }
    else if(params.C_pl <= 0){
        printf("Error: C_pl must be > 0");
        exit(EXIT_FAILURE);
    }
    else if(params.Hf <= 0){
        printf("Error: Hf must be > 0");
        exit(EXIT_FAILURE);
    }
    else if(params.Ac <= 0){
        printf("Error: Ac must be > 0");
        exit(EXIT_FAILURE);
    }
    else if(params.rho_w <= 0){
        printf("Error: rho_w must be > 0");
        exit(EXIT_FAILURE);
    }
    else if(params.C_w <= 0){
        printf("Error: C_w must be > 0");
        exit(EXIT_FAILURE);
    }
    else if(params.hc <= 0){
        printf("Error: hc must be > 0");
        exit(EXIT_FAILURE);
    }
    else if(params.hp <= 0){
        printf("Error: hp must be > 0");
        exit(EXIT_FAILURE);
    }
    else if(params.Tinit <= 0 || params.Tinit >= 100){
        printf("Error: Tinit must be > 0 and < 100");
        exit(EXIT_FAILURE);
    }
    else if(params.tfinal <= 0){
        printf("Error: tfinal must be > 0");
        exit(EXIT_FAILURE);
    }
    else if(params.Tinit > params.Tmelt){
        printf("Tinit must be < Tmelt");
        exit(EXIT_FAILURE);
    }

    // Software Constraints

    if(params.L < 0.1 || params.L > 50){
        printf("Warning: It is recommended that 0.1 <= L <= 50");
    }
    if(params.diam / params.L < 0.002 || params.diam / params.L > 200){
        printf("Warning: It is recommended that 0.002 <= D/L <= 200");
    }
    if(params.Vp < pow(10, -6) * params.Vt){
        printf("Warning: It is recommended that Vp be >= 0.000001 of Vt");
    }
    if(params.Vp > params.Ap || params.Ap > (2/0.001) * params.Vp){
        printf("Warning: It is recommended that Vp <= Ap <= (2/0.001) * Vp");
    }
    if(params.rho_p <= 500 || params.rho_p >= 20000){
        printf("Warning: It is recommended that 500 < rho_p < 20000");
    }
    if(params.C_ps <= 100 || params.C_ps >= 4000){
        printf("Warning: It is recommended that 100 < C_ps < 4000");
    }
    if(params.C_pl <= 100 || params.C_pl >= 5000){
        printf("Warning: It is recommended that 100 < C_pl < 5000");
    }
    /*if(params.Hf <= ADD WHEN DECIDED){
        warning
    }*/
    if(params.Ac > pi * pow(params.diam / 2, 2)){
        printf("Warning: It is recommended that Ac <= pi * (D/2)^2");
    }
    if(params.rho_w <= 950 || params.rho_w > 1000){
        printf("Warning: It is recommended that 950 < rho_w <= 1000");
    }
    if(params.C_w <= 4170 || params.C_w >= 4210){
        printf("Warning: It is recommended that 4170 < C_w < 4210");
    }
    if(params.hc <= 10 || params.hc >= 10000){
        printf("Warning: It is recommended that 10 <= hc <= 10000");
    }
    if(params.hp <= 10 || params.hp >= 10000){
        printf("Warning: It is recommended that 10 <= hp <= 10000");
    }
    if(params.tfinal <= 0 || params.tfinal >= 86400){
        printf("Warning: It is recommended that 0 < tfinal < 86400");
    }

    return;
}
