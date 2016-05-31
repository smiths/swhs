#include <stdio.h>
#include <stdlib.h>
#include "load_params.h"

void verify_params(struct parameters params){

    // Check that inputs are valid

    /* Note to self: Consider using printf and exit(EXIT_FAILURE) if perror
    still displays "No error" once you are finished coding the program. */

    if(params.L <= 0){
        perror("Tank length must be > 0");
    }
    else if(params.diam <= 0){
        perror("Tank diameter must be > 0");
    }
    else if(params.Vp <= 0){
        perror("PCM volume must be > 0");
    }
    else if(params.Vp >= params.Vt){
        perror("PCM volume must be < tank volume");
    }
    else if(params.Ap <= 0){
        perror("PCM area must be > 0");
    }
    else if(params.rho_p <= 0){
        perror("rho_p must be > 0");
    }
    else if(params.Tmelt <= 0 || params.Tmelt >= params.Tc){
        perror("Tmelt must be > 0 and < Tc");
    }
    else if(params.Tc <= params.Tinit){
        perror("Tc must be > Tinit");
    }
    else if(params.Tc >= 100 || params.Tc <= 0){
        perror("Tc must be > 0 and < 100");
    }
    else if(params.C_ps <= 0){
        perror("C_ps must be > 0");
    }
    else if(params.C_pl <= 0){
        perror("C_pl must be > 0");
    }
    else if(params.Hf <= 0){
        perror("Hf must be > 0");
    }
    else if(params.Ac <= 0){
        perror("Ac must be > 0");
    }
    else if(params.rho_w <= 0){
        perror("rho_w must be > 0");
    }
    else if(params.C_w <= 0){
        perror("C_w must be > 0");
    }
    else if(params.hc <= 0){
        perror("hc must be > 0");
    }
    else if(params.hp <= 0){
        perror("hp must be > 0");
    }
    else if(params.Tinit <= 0 || params.Tinit >= 100){
        perror("Tinit must be > 0 and < 100");
    }
    else if(params.tfinal <= 0){
        perror("tfinal must be >0");
    }
    else if(params.Tinit > params.Tmelt){
        perror("Tinit must be < Tmelt");
    }

    // Software Constraints

    return;
}
