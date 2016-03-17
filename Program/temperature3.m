%% Temperature ODEs Module, when Tp > Tmelt
% This module uses the input parameters in params to specify the ODE that governs
% the temperature of the water and PCM
%
% Authors: Thulasi Jegatheesan, Spencer Smith and Ned Nedialkov
%
% Data Last Revised: May 20, 2015
%
% Uses: params (Input Parameters Module)
%
% State Variables: none
%
% Environment Variables: none
%
% Governing Equations
%
% $$\frac{dT_W}{dt} = \frac{1}{\tau_W}[(T_C - T_W(t)) + {\eta}(T_P(t) - T_W(t))]$$
%
% $$\frac{dT_P}{dt} = \frac{1}{\tau^L_P}(T_W(t) - T_P(t))$$
%
% T(1) is Tw and T(2) is Tp
%
function dTdt = temperature3(t,T,params)

    dTdt(1)   =   (1/params.tau_w)*((params.Tc - T(1)) + params.eta*(T(2) - T(1)));      %dTw/dt
    dTdt(2)   =   (1/params.tau_pl)*(T(1) - T(2));                                       %dTp/dt if Tp > Tmelt
    dTdt      =   dTdt(:);