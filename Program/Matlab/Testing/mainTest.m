%I am commenting this code because it seems to have been written when the software was in an older form
%and if I were to modify it to make it work on the current version, I think it would just be redundant
%with the invalidInputTest.m tests. -Brooks

% function tests = mainTest
% tests = functiontests(localfunctions);
% end

% function setupOnce(testCase)
% addpath('Matlab');
% addpath('..');
% end

% % function testNormalInput(testCase)
% % actSolution = dlmread('deltaTestNormal.txt');
% % expSolution = deltaTest([1:2, 5:8])
% % verifyEqual(testCase, actSolution, expSolution)
% % end

% function testTcTinit(testCase)
% f = @()main('M09.txt');
% assertExceptionThrown(f, 'temperature:TcTinit');
% end

% function testBoiling(testCase)
% f = @()main('M03.txt');
% assertExceptionThrown(f, 'temperature:BoilingPt');
% end

% function testFreezing(testCase)
% f = @()main('M04.txt');
% assertExceptionThrown(f, 'temperature:FreezingPt');
% end