function tests = compareSolversTest
tests = functiontests(localfunctions)
end

function setupOnce(testCase)
addpath('Matlab');
addpath('..');
end

function e = getEpsilon
e = 0.001;
end


function testCompareSolvers(testCase)
main('M01.txt');
main23('M0123.txt');
delta = PCM_ErrorMM('M0123.out', 'M01.out', 'Twat')
verifyLessThanOrEqual(testCase, delta, getEpsilon)
delta = PCM_ErrorMM('M0123.out', 'M01.out', 'TPCM')
verifyLessThanOrEqual(testCase, delta, getEpsilon)
delta = PCM_ErrorMM('M0123.out', 'M01.out', 'Ewat')
verifyLessThanOrEqual(testCase, delta, getEpsilon)
delta = PCM_ErrorMM('M0123.out', 'M01.out', 'EPCM')
verifyLessThanOrEqual(testCase, delta, getEpsilon)
delta = PCM_ErrorMM('M0123.out', 'M01.out', 'Etot')
verifyLessThanOrEqual(testCase, delta, getEpsilon)
end

function teardownOnce(testCase)
delete('M01.out', 'M0123.out');
end