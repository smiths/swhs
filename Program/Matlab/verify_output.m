%% Output Verification Module

% This module verifies that the output results for water and PCM 
% conform to the law of conservation of energy and throws
% warnings if either does not.

%

% Authors: Thulasi Jegatheesan, Spencer Smith, Ned Nedialkov, and Brooks

% MacLachlan

%

% Date Last Revised: June 7, 2016

%

% Uses: params (Input Parameters Module)

%

% State Variables: none

%

% Environment Variables: none

%

function verify_output(params,t,T,Ew,Ep)



for i = 1:(length(t)-1)

    delta_t(i) = t(i+1) - t(i);

    i = i + 1;

end



for i = 1:length(delta_t)

    coil_E(i) = params.hc * params.Ac * delta_t(i) * (params.Tc - T(i+1,1) + params.Tc - T(i,1)) / 2;

    pcm_E(i) = params.hp * params.Ap * delta_t(i) * (T(i+1,1) - T(i+1,2) + T(i,1) - T(i,2)) / 2;

end



water_E = coil_E - pcm_E;



tot_water_E = sum(water_E);



water_error = abs(tot_water_E - Ew(end))/Ew(end)*100;



tot_pcm_E = sum(pcm_E);



pcm_error = abs(tot_pcm_E - Ep(end))/Ep(end)*100;



if(water_error > params.ConsTol)

    warning('output:Ew', 'There is greater than %f%% relative error between the Ew output and the expected output based on the law of conservation of energy.', params.ConsTol)
end



if(pcm_error > params.ConsTol)

    warning('output:Ep', 'There is greater than %f%% relative error between the Ep output and the expected output based on the law of conservation of energy.', params.ConsTol)

end
end