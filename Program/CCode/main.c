/* Control Module

This module coordinates the running of SHS

Authors: Thulasi Jegatheesan, Spencer Smith, Ned Nedialkov, and Brooks MacLachlan

Date Last Revised: June 10, 2016

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parameters.h"
#include "load_params.h"
#include "verify_params.h"
#include "energy1.h"
#include "energy2.h"
#include "energy3.h"
#include "verify_output.h"
#include "plot.h"
#include "output.h"
#include <cvode/cvode.h>
#include <nvector/nvector_serial.h>
#include <cvode/cvode_dense.h>
#include <sundials/sundials_dense.h>
#include <sundials/sundials_types.h>

#define Ith1(v,i)    NV_Ith_S(v,i-1)
#define IJth1(A,i,j) DENSE_ELEM(A,i-1,j-1)
#define Ith2(v,i)    NV_Ith_S(v,i-1)
#define IJth2(A,i,j) DENSE_ELEM(A,i-1,j-1)
#define Ith3(v,i)    NV_Ith_S(v,i-1)
#define IJth3(A,i,j) DENSE_ELEM(A,i-1,j-1)

int temperature1(realtype t, N_Vector yPhase1, N_Vector yPhase1dot, void *user_data);

int temperature2(realtype t, N_Vector yPhase2, N_Vector yPhase2dot, void *user_data);

int temperature3(realtype t, N_Vector yPhase3, N_Vector yPhase3dot, void *user_data);

int Jac1(long int N, realtype t,
               N_Vector yPhase1, N_Vector fy, DlsMat J, void *user_data,
               N_Vector tmp1, N_Vector tmp2, N_Vector tmp3);

int Jac2(long int N, realtype t,
               N_Vector yPhase2, N_Vector fy, DlsMat J, void *user_data,
               N_Vector tmp1, N_Vector tmp2, N_Vector tmp3);

int Jac3(long int N, realtype t,
               N_Vector yPhase3, N_Vector fy, DlsMat J, void *user_data,
               N_Vector tmp1, N_Vector tmp2, N_Vector tmp3);

int main()
{
    printf("Enter the name of your input file:\n");
    fflush(stdout);
    char filename[20];
    scanf(" %s", filename);
    struct parameters params;
    params = load_params(filename);

    int dotFinder;
    char outputFilename[strlen(filename)+2];
    for(dotFinder = 0; dotFinder < strlen(filename); dotFinder++){
        outputFilename[dotFinder] = filename[dotFinder];
        if(filename[dotFinder] == '.'){
            break;
        }
    }

    strcat(outputFilename, "out");

    verify_params(params);

    // When Tp < Tmelt

    realtype reltol, t, tout, nout;
    N_Vector yPhase1, abstol1;
    void *cvode_mem;
    int counter, N1, N2;
    realtype tinit = RCONST(0.0);

    N1 = 2;
    N2 = 3;

    yPhase1 = abstol1 = NULL;
    cvode_mem = NULL;

    yPhase1 = N_VNew_Serial(N1);
    abstol1 = N_VNew_Serial(N1);

    /* Initialize y */
    Ith1(yPhase1,1) = Ith1(yPhase1,2) = RCONST(params.Tinit);

    // Set tolerances
    reltol = RCONST(params.RelTol);
    Ith1(abstol1,1) = Ith1(abstol1,2) = RCONST(params.AbsTol);

    cvode_mem = CVodeCreate(CV_BDF, CV_NEWTON);

    CVodeInit(cvode_mem, temperature1, tinit, yPhase1);

    CVodeSVtolerances(cvode_mem, reltol, abstol1);

    CVDense(cvode_mem, N1);

    CVDlsSetDenseJacFn(cvode_mem, Jac1);

    counter = 1;  tout = RCONST(params.tstep); nout = RCONST(params.tfinal / tout);
    int num1 = nout;
    int counter1 = 0;
    float time[num1]; float tempW[num1]; float tempP[num1];
    time[0] = 0.0;
    tempW[0] = params.Tinit;
    tempP[0] = params.Tinit;
    float tstep = params.tstep;
    while(1) {
      CVode(cvode_mem, tout, yPhase1, &t, CV_NORMAL);
      time[counter] = t;
      tempW[counter] = Ith1(yPhase1,1);
      tempP[counter] = Ith1(yPhase1,2);
      tout += tstep;
      if(tempP[counter] >= params.Tmelt){
        counter++;
        counter1++;
        printf("PCM has started melting at time %f\n", tout - tstep);
        break;
      }
      counter++;
      counter1++;
      if(counter > num1){
        printf("PCM has not started melting\n");
        break;
      }
    }

    float eW1[counter1], eP1[counter1], eTot1[counter1];
    int j;
    for(j = 0; j <= counter1; j++){
        eW1[j] = energy1Wat(tempW[j], params);
        eP1[j] = energy1PCM(tempP[j], params);
        eTot1[j] = eW1[j] + eP1[j];
    }

    /* Free integrator memory */
    CVodeFree(&cvode_mem);

    // When Tp = Tmelt

    N_Vector yPhase2, abstol2;

    yPhase2 = abstol2 = NULL;
    cvode_mem = NULL;

    yPhase2 = N_VNew_Serial(N2);
    abstol2 = N_VNew_Serial(N2);

     /* Initialize y */
    Ith2(yPhase2,1) = Ith1(yPhase1,1);
    Ith2(yPhase2,2) = Ith1(yPhase1,2);
    Ith2(yPhase2,3) = RCONST(0.0);

    // Set tolerances
    Ith2(abstol2,1) = Ith2(abstol2,2) = Ith2(abstol2,3) = RCONST(params.AbsTol);

    cvode_mem = CVodeCreate(CV_BDF, CV_NEWTON);

    CVodeInit(cvode_mem, temperature2, tout-tstep, yPhase2);

    CVodeSVtolerances(cvode_mem, reltol, abstol2);

    CVDense(cvode_mem, N2);

    CVDlsSetDenseJacFn(cvode_mem, Jac2);

    float latentHeat[num1]; float phi;
    int counter2 = 0;
    while(1) {
      CVode(cvode_mem, tout, yPhase2, &t, CV_NORMAL);
      time[counter] = t;
      tempW[counter] = Ith2(yPhase2,1);
      tempP[counter] = Ith2(yPhase2,2);
      tout += tstep;
      latentHeat[counter] = Ith2(yPhase2,3);
      phi = latentHeat[counter] / (params.Hf * params.Mp);
      if(phi >= 1.0){
        counter++;
        counter2++;
        printf("PCM has finished melting at time %f\n", tout - tstep);
        break;
      }
      counter++;
      counter2++;
      if(counter > num1){
        printf("%f%% of the PCM has melted at time %f\n", phi*100, params.tfinal);
        break;
      }
    }

    float eW2[counter2], eP2[counter2], eTot2[counter2];
    int j2;
    for(j2 = 0; j2 <= counter2; j2++){
        eW2[j2] = energy2Wat(tempW[j2+counter1], params);
        eP2[j2] = energy2PCM(latentHeat[j2+counter1], params);
        eTot2[j2] = eW2[j2] + eP2[j2];
    }
    /* Free integrator memory */
    CVodeFree(&cvode_mem);

    // When Tp > Tmelt

    N_Vector yPhase3, abstol3;

    yPhase3 = abstol3 = NULL;
    cvode_mem = NULL;

    yPhase3 = N_VNew_Serial(N1);
    abstol3 = N_VNew_Serial(N1);

     /* Initialize y */
    Ith3(yPhase3,1) = Ith2(yPhase2,1);
    Ith3(yPhase3,2) = Ith2(yPhase2,2);

    // Set tolerances
    Ith3(abstol3,1) = Ith3(abstol3,2) = RCONST(params.AbsTol);

    cvode_mem = CVodeCreate(CV_BDF, CV_NEWTON);

    CVodeInit(cvode_mem, temperature3, tout-tstep, yPhase3);

    CVodeSVtolerances(cvode_mem, reltol, abstol3);

    CVDense(cvode_mem, N1);

    CVDlsSetDenseJacFn(cvode_mem, Jac3);

    int counter3 = 0;
    while(1) {
      CVode(cvode_mem, tout, yPhase3, &t, CV_NORMAL);
      time[counter] = t;
      tempW[counter] = Ith3(yPhase3,1);
      tempP[counter] = Ith3(yPhase3,2);
      tout += tstep;
      counter++;
      counter3++;
      if(counter > num1){
        break;
      }
    }

    float eW3[counter3], eP3[counter3], eTot3[counter3];
    int j3;
    for(j3 = 0; j3 <= counter3; j3++){
        eW3[j3] = energy3Wat(tempW[j3+counter1+counter2], params);
        eP3[j3] = energy3PCM(tempP[j3+counter1+counter2], params);
        eTot3[j3] = eW3[j3] + eP3[j3];
    }

    /* Free y and abstol vectors */
    N_VDestroy_Serial(yPhase1);
    N_VDestroy_Serial(abstol1);
    N_VDestroy_Serial(yPhase2);
    N_VDestroy_Serial(abstol2);
    N_VDestroy_Serial(yPhase3);
    N_VDestroy_Serial(abstol3);

    /* Free integrator memory */
    CVodeFree(&cvode_mem);

    float eW[num1], eP[num1], eTot[num1];
    int k;
    for(k = 0; k <= num1; k++){
        if(k < counter1){
            eW[k] = eW1[k];
            eP[k] = eP1[k];
            eTot[k] = eTot1[k];
        }
        else if(k < counter1+counter2){
            eW[k] = eW2[k-counter1];
            eP[k] = eP2[k-counter1];
            eTot[k] = eTot2[k-counter1];
        }
        else{
            eW[k] = eW3[k-counter1-counter2];
            eP[k] = eP3[k-counter1-counter2];
            eTot[k] = eTot3[k-counter1-counter2];
        }
    }

    // Output Results and plots

    float sizeOfResults = sizeof(time) / sizeof(time[0]);
    verify_output(tempW, tempP, eW, eP, params, sizeOfResults);
    plot(time, tempW, tempP, eW, eP, params, sizeOfResults, outputFilename);
    output(outputFilename, time, tempW, tempP, eW, eP, eTot, params, sizeOfResults);

    return 0;
}

int Jac1(long int N, realtype t,
               N_Vector yPhase1, N_Vector fy, DlsMat J, void *user_data,
               N_Vector tmp1, N_Vector tmp2, N_Vector tmp3)
{
    realtype y1, y2;

    struct parameters params;
    params = load_params("test.in");

    y1 = Ith1(yPhase1,1); y2 = Ith1(yPhase1,2);

    IJth1(J,1,1) = -RCONST((1 + params.eta) / params.tau_w);
    IJth1(J,1,2) = RCONST(params.eta / params.tau_w);
    IJth1(J,2,1) = RCONST(1 / params.tau_ps);
    IJth1(J,2,2) = -RCONST(1 / params.tau_ps);

  return(0);
}

int Jac2(long int N, realtype t,
               N_Vector yPhase2, N_Vector fy, DlsMat J, void *user_data,
               N_Vector tmp1, N_Vector tmp2, N_Vector tmp3)

{
    realtype y1, y2, y3;

    struct parameters params;
    params = load_params("test.in");

    y1 = Ith2(yPhase2,1); y2 = Ith2(yPhase2,2); y3 = Ith2(yPhase2,3);

    IJth2(J,1,1) = -RCONST((1 + params.eta) / params.tau_w);
    IJth2(J,1,2) = RCONST(params.eta / params.tau_w);
    IJth2(J,1,3) = RCONST(0.0);
    IJth2(J,2,1) = RCONST(0.0);
    IJth2(J,2,2) = RCONST(0.0);
    IJth2(J,2,3) = RCONST(0.0);
    IJth2(J,3,1) = RCONST(params.hp * params.Ap);
    IJth2(J,3,2) = RCONST(0.0);
    IJth2(J,3,3) = RCONST(0.0);

  return(0);
}

int Jac3(long int N, realtype t,
               N_Vector yPhase3, N_Vector fy, DlsMat J, void *user_data,
               N_Vector tmp1, N_Vector tmp2, N_Vector tmp3)
{
    realtype y1, y2;

    struct parameters params;
    params = load_params("test.in");

    y1 = Ith3(yPhase3,1); y2 = Ith3(yPhase3,2);

    IJth3(J,1,1) = -RCONST((1 + params.eta) / params.tau_w);
    IJth3(J,1,2) = RCONST(params.eta / params.tau_w);
    IJth3(J,2,1) = RCONST(1 / params.tau_pl);
    IJth3(J,2,2) = -RCONST(1 / params.tau_pl);

  return(0);
}

/* Temperature ODEs Module, when Tp < Tmelt

This module uses the input parameters in params to specify the ODEs
that govern the temperature of the water and PCM.

Authors: Thulasi Jegatheesan, Spencer Smith, Ned Nedialkov, and Brooks
MacLachlan

Date Last Revised: June 10, 2016

Governing Equations:

dTwdt = (1 / tau_w) * ((Tc - Tw(t)) + eta * (Tp(t) - Tw(t)))

dTpdt = (1 / tau_ps) * (Tw(t) - Tp(t))

*/

int temperature1(realtype t, N_Vector yPhase1, N_Vector yPhase1dot, void *user_data){

    realtype y1, y2, yd1, yd2;

    struct parameters params;
    params = load_params("test.in");

    y1 = Ith1(yPhase1,1); y2 = Ith1(yPhase1,2);

    yd1 = Ith1(yPhase1dot,1) = RCONST(params.Tc / params.tau_w) - RCONST((1 + params.eta) / params.tau_w) * y1 + RCONST(params.eta / params.tau_w) * y2;
    yd2 = Ith1(yPhase1dot,2) = RCONST(1 / params.tau_ps) * y1 - RCONST(1 / params.tau_ps) * y2;

    return(0);
}

/* Temperature ODEs Module, when Tp = Tmelt

This module uses the input parameters in params to specify the ODEs
that govern the temperature of the water and PCM.

Authors: Thulasi Jegatheesan, Spencer Smith, Ned Nedialkov, and Brooks
MacLachlan

Date Last Revised: June 10, 2016

Governing Equations:

dTw/dt = (1 / tau_w) * ((Tc - Tw(t)) + eta * (Tp(t) - Tw(t)))

dTp/dt = 0

dQp/dt = hp * Ap * (Tw(t) - Tmelt)

*/


int temperature2(realtype t, N_Vector yPhase2, N_Vector yPhase2dot, void *user_data){

    realtype y1, y2, y3, yd1, yd2, yd3;

    struct parameters params;
    params = load_params("test.in");

    y1 = Ith2(yPhase2,1); y2 = Ith2(yPhase2,2); y3 = Ith2(yPhase2,3);

    yd1 = Ith2(yPhase2dot,1) = RCONST(params.Tc / params.tau_w) - RCONST((1 + params.eta) / params.tau_w) * y1 + RCONST(params.eta / params.tau_w) * y2;
    yd2 = Ith2(yPhase2dot,2) = RCONST(0.0);
    yd3 = Ith2(yPhase2dot,3) = RCONST(params.hp * params.Ap) * y1 - RCONST(params.hp * params.Ap * params.Tmelt);


    return(0);
}

/* Temperature ODEs Module, when Tp > Tmelt

This module uses the input parameters in params to specify the ODEs
that govern the temperature of the water and PCM.

Authors: Thulasi Jegatheesan, Spencer Smith, Ned Nedialkov, and Brooks
MacLachlan

Date Last Revised: June 10, 2016

Governing Equations:

dTw/dt = (1 / tau_w) * ((Tc - Tw(t)) + eta * (Tp(t) - Tw(t)))

dTp/dt = (1 / tau_pl) * (Tw(t) - Tp(t))

*/

int temperature3(realtype t, N_Vector yPhase3, N_Vector yPhase3dot, void *user_data){

    realtype y1, y2, yd1, yd2;

    struct parameters params;
    params = load_params("test.in");

    y1 = Ith3(yPhase3,1); y2 = Ith3(yPhase3,2);

    yd1 = Ith3(yPhase3dot,1) = RCONST(params.Tc / params.tau_w) - RCONST((1 + params.eta) / params.tau_w) * y1 + RCONST(params.eta / params.tau_w) * y2;
    yd2 = Ith3(yPhase3dot,2) = RCONST(1 / params.tau_pl) * y1 - RCONST(1 / params.tau_pl) * y2;

    return(0);
}
