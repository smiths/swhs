function tests = paramsTest
tests = functiontests(localfunctions);
end

function paramTest(testCase)
expParams = struct('L', 1.5,
                'diam', 0.412,
                'Vp', 0.05,
                'Ap', 1.2,
                'rho_p', 1007,
                'Tmelt', 44.2,
                'C_ps', 1760,
                'C_pl', 2270,
                'Hf', 211600,
                'Ac', 0.12,
                'Tc', 50.0,
                'rho_w', 1000,
                'C_w', 4186.0,
                'hc', 1000.0,
                'hp', 1000.0,
                'Tinit', 40.0
                'tstep', 10.0,
                'tfinal', 50000,
                'AbsTol', 1e-10,
                'RelTol, 1e-10,)
actParams = load_params('Testing/Matlab/M01.txt')
verifyEqual(testCase, actParams, expParams)
end