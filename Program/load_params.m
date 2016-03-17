%% Input Format Module
% This module takes a filename and then uses it to load
% the parameter values into the parameters object (params)
%
% Authors: Thulasi Jegatheesan, Spencer Smith and Ned Nedialkov
%
% Date Last Revised: July 2, 2015
%
% Uses: params (Input Parameters Module)
%
% State Variables: none
%
% Environment Variable: the file associated with filename
%
% Assumptions: Once initialized the parameter values are constant
% for the life of the program.
%
% Considerations: The meaning of each parameter is given as a comment in the code below
%
function [ params ] = load_params(filename)
    
    fid = fopen(filename);
    [param] = textscan(fid, '%f', 'Delimiter', '\n', 'CommentStyle', '#');
    param = param{:};
    fclose(fid);

    %parameters from input
    params.L       = param(1); % Length of tank
    params.diam    = param(2); % Diameter of tank
    params.Vp      = param(3); % Volume of PCM
    params.Ap      = param(4); % Surface area of PCM
    params.rho_p   = param(5); % Density of PCM
    params.Tmelt   = param(6); % Melt temperature of PCM
    params.C_ps    = param(7); % Specific heat capacity of solid PCM
    params.C_pl    = param(8); % Specific heat capacity of liquid PCM
    params.Hf      = param(9); % Heat of fusion for PCM
    params.Ac      = param(10); % Area of coil
    params.Tc      = param(11); % Temperature of coil
    params.rho_w   = param(12); % Density of water
    params.C_w     = param(13); % Specific heat capacity of water
    params.hc      = param(14); % Heat transfer coefficient between water and coil
    params.hp      = param(15); % Heat transfer coeeficient between PCM and water
    params.Tinit   = param(16); % Initial temperature of water and PCM
    params.tstep   = param(17); % Time step for simulation
    params.tfinal  = param(18); % Time at which to stop simulation
    params.AbsTol  = param(19); % Absolute tolerance
    params.RelTol  = param(20); % Relative tolerance

    %calculated parameters
    params.Vt      = pi*(params.diam/2)*(params.diam/2)*params.L;       % Total volume of tank, including pcm and water
    params.Mw      = params.rho_w * (params.Vt - params.Vp);            % Mass of water
    params.tau_w   = (params.Mw * params.C_w)/(params.hc * params.Ac);  % ODE parameter for water
    params.eta     = (params.hp * params.Ap)/(params.hc * params.Ac);   % ODE parameter
    params.Mp      = params.rho_p * params.Vp;                          % Mass of pcm
    params.tau_ps  = (params.Mp * params.C_ps)/(params.hp * params.Ap); % ODE parameter for solid pcm
    params.tau_pl  = (params.Mp * params.C_pl)/(params.hp * params.Ap); % ODE parameter for liquid pcm
    
    params.Epmelt_init   = params.C_ps * params.Mp * (params.Tmelt - params.Tinit);
    params.Ep_melt3 = params.Hf * params.Mp;

    params.Mw_noPCM      = params.rho_w * (params.Vt);
    params.tau_w_noPCM   = (params.Mw_noPCM * params.C_w)/(params.hc * params.Ac);

%Check that inputs are valid
if params.L <= 0
    error('input:L', 'Tank length must be > 0');
elseif params.diam <= 0
    error('input:diam', 'Tank diameter must be > 0');
elseif params.Vp <= 0
    error('input:Vp', 'PCM volume must be > 0');
elseif params.Vp >= params.Vt
    error('input:VpVt', 'PCM volume must be < tank volume'); 
elseif params.Ap <= 0
    error('input:Ap', 'PCM area must be > 0');
elseif params.rho_p <= 0
    error('input:rho_p', 'rho_p must be > 0');
elseif params.Tmelt <= 0 || params.Tmelt >= params.Tc
    error('input:Tmelt', 'Tmelt must be > 0 and < Tc')
elseif params.Tc <= params.Tinit
  error('input:TcTinit', 'Tc must be > Tinit');
elseif params.Tc >= 100 || params.Tc <= 0
    error('input:Tc', 'Tc must be > 0 and < 100');
elseif params.C_ps <= 0
    error('input:C_ps', 'C_ps must be > 0');
elseif params.C_pl <= 0
    error('input:C_pl', 'C_pl must be > 0');
elseif params.Hf <= 0
    error('input:Hf', 'Hf must be > 0');
elseif params.Ac <= 0
    error('input:Ac', 'Ac must be > 0');
elseif params.rho_w <= 0
    error('input:rho_w','rho_w must be > 0');
elseif params.C_w <= 0
    error('input:C_w','C_w must be > 0');
elseif params.hc <= 0
    error('input:hc', 'hc must be > 0');
elseif params.hp <= 0
    error('input:hp', 'hp must be > 0');
elseif params.Tinit <= 0 || params.Tinit >= 100
    error('input:Tinit', 'Tinit must be > 0 and < 100');
elseif params.tfinal <= 0
    error('input:tfinal', 'tfinal must be > 0');
elseif params.Tinit > params.Tmelt
    error('input:TinitTmelt', 'Tinit must be < Tmelt');
end

%Software Constraints
if params.L < 0.1 || params.L > 50
    warning('inputwarn:L', 'It is recommended that 0.1 <= L <= 50');
elseif params.diam/params.L < 0.002 || params.diam/params.L > 200
    warning('inputwarn:diam', 'It is recommended that 0.002 <= D/L <= 200');
elseif params.Vp < (10^-6)*params.Vt
    warning('inputwarn:VpVt', 'It is recommended that Vp be >= 0.0001% of Vt');    
elseif params.Vp > params.Ap || params.Ap > (2/0.001)*params.Vp
    warning('inputwarn:VpAp', 'It is recommended that Vp <= Ap <= (2/0.001)*Vp');
elseif params.rho_p <= 500 || params.rho_p >= 20000
    warning('inputwarn:rho_p', 'It is recommended that 500 < rho_p < 20000');
elseif params.C_ps <= 100 || params.C_ps >= 4000
    warning('inputwarn:C_ps', 'It is recommended that 100 < C_ps < 4000');
elseif params.C_pl <= 100 || params.C_pl >= 5000
     warning('inputwarn:C_pl', 'It is recommended that 100 < C_pl < 5000');
%elseif params.Hf <= ADD WHEN DECIDED
      %warning
elseif params.Ac > pi*(params.diam/2)^2
      warning('inputwarn:Ac', 'It is recommended that Ac <= pi*(D/2)^2');
elseif params.rho_w <= 950 || params.rho_w > 1000
      warning('inputwarn:rho_w', 'It is recommended that 950 < rho_w <= 1000');
elseif params.C_w <= 4170 || params.C_w >= 4210
      warning('inputwarn:C_w', 'It is recommended that 4170 < C_w < 4210');
elseif params.tfinal <= 0 || params.tfinal >= 86400
      warning('input:tfinal', 'It is recommended that 0 < tfinal < 86400');
end
