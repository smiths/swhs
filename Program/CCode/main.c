#include <stdio.h>
#include <stdlib.h>
#include "verify_params.h"
#include <cvode/cvode.h>
#include <nvector/nvector_serial.h>
#include <cvode/cvode_dense.h>
#include <sundials/sundials_dense.h>

#define Ith(v,i)    NV_Ith_S(v,i-1)       /* Ith numbers components 1..NEQ */
#define IJth(A,i,j) DENSE_ELEM(A,i-1,j-1) /* IJth numbers rows,cols 1..NEQ */

int temperature1(realtype t, N_Vector y, N_Vector ydot, void *user_data);

int Jac1(long int N, realtype t,
               N_Vector y, N_Vector fy, DlsMat J, void *user_data,
               N_Vector tmp1, N_Vector tmp2, N_Vector tmp3);

int main()
{
    struct parameters params;
    params = load_params("test.in");

    verify_params(params);

    realtype reltol, t, tout, nout;
    N_Vector y, abstol;
    void *cvode_mem;
    int flag, flagr, iout, N1, N2;
    realtype tinit = RCONST(0.0);

    N1 = 2;
    N2 = 3;

    y = abstol = NULL;
    cvode_mem = NULL;

    y = N_VNew_Serial(N1);
    abstol = N_VNew_Serial(N1);

    /* Initialize y */
    Ith(y,1) = Ith(y,2) = RCONST(params.Tinit);

    //Set tolerances
    reltol = RCONST(params.RelTol);
    Ith(abstol,1) = Ith(abstol,2) = RCONST(params.AbsTol);

    cvode_mem = CVodeCreate(CV_BDF, CV_NEWTON);

    CVodeInit(cvode_mem, temperature1, tinit, y);

    CVodeSVtolerances(cvode_mem, reltol, abstol);

    CVDense(cvode_mem, N1);

    CVDlsSetDenseJacFn(cvode_mem, Jac1);

    iout = 0;  tout = RCONST(params.tstep); nout = RCONST(params.tfinal / tout);
    while(1) {
      CVode(cvode_mem, tout, y, &t, CV_NORMAL);
      iout++;
      if(iout >= nout) break;
    }

    /* Free y and abstol vectors */
    N_VDestroy_Serial(y);
    N_VDestroy_Serial(abstol);

    /* Free integrator memory */
    CVodeFree(&cvode_mem);

    return 0;
}

int Jac1(long int N, realtype t,
               N_Vector y, N_Vector fy, DlsMat J, void *user_data,
               N_Vector tmp1, N_Vector tmp2, N_Vector tmp3)
{
  realtype y1, y2, y3;

  y1 = Ith(y,1); y2 = Ith(y,2);

  IJth(J,1,1) = RCONST(-0.04);
  IJth(J,1,2) = RCONST(1.0e4)*y3;
  IJth(J,2,1) = RCONST(0.04);
  IJth(J,2,2) = RCONST(-1.0e4)*y3-RCONST(6.0e7)*y2;

  return(0);
}

int temperature1(realtype t, N_Vector y, N_Vector ydot, void *user_data){
    realtype y1, y2, yd1, yd2;

    y1 = Ith(y0,1); y2 = Ith(y0,2);

    yd1 = Ith(ydot,1) = RCONST(params.Tc / params.tau_w) - RCONST(1 / params.tau_w - params.eta) * y1 + RCONST(params.eta) * y2;
    yd2 = Ith(ydot,2) = RCONST(1 / params.tau_ps) * y1 - RCONST(1 / params.tau_ps) * y2;

    return(0);
}
