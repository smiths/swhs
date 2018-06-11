function tests = badInputTest
tests = functiontests(localfunctions);
end

function setupOnce(testCase)
addpath('UnrecommendedInput');
addpath('..');
end

function testUI01(testCase)
f = @()main('UI01.txt');
verifyWarning(testCase, f, 'inputwarn:L');
end

function testUI02(testCase)
f = @()main('UI02.txt');
verifyWarning(testCase, f, 'inputwarn:L');
end

function testUI03(testCase)
f = @()main('UI03.txt');
verifyWarning(testCase, f, 'inputwarn:diam');
end

function testUI04(testCase)
f = @()main('UI04.txt');
verifyWarning(testCase, f, 'inputwarn:diam');
end

function testUI05(testCase)
f = @()main('UI05.txt');
verifyWarning(testCase, f, 'inputwarn:VpVt');
end

function testUI06(testCase)
f = @()main('UI06.txt');
verifyWarning(testCase, f, 'inputwarn:VpAp');
end

function testUI07(testCase)
f = @()main('UI07.txt');
verifyWarning(testCase, f, 'inputwarn:VpAp');
end

function testUI08(testCase)
f = @()main('UI08.txt');
verifyWarning(testCase, f, 'inputwarn:rho_p');
end

function testUI09(testCase)
f = @()main('UI09.txt');
verifyWarning(testCase, f, 'inputwarn:rho_p');
end

function testUI10(testCase)
f = @()main('UI10.txt');
verifyWarning(testCase, f, 'inputwarn:C_ps');
end

function testUI11(testCase)
f = @()main('UI11.txt');
verifyWarning(testCase, f, 'inputwarn:C_ps');
end

function testUI12(testCase)
f = @()main('UI12.txt');
verifyWarning(testCase, f, 'inputwarn:C_pl');
end

function testUI13(testCase)
f = @()main('UI13.txt');
verifyWarning(testCase, f, 'inputwarn:C_pl');
end

function testUI16(testCase)
f = @()main('UI16.txt');
verifyWarning(testCase, f, 'inputwarn:Ac');
end

function testUI17(testCase)
f = @()main('UI17.txt');
verifyWarning(testCase, f, 'inputwarn:rho_w');
end

function testUI18(testCase)
f = @()main('UI18.txt');
verifyWarning(testCase, f, 'inputwarn:rho_w');
end

function testUI19(testCase)
f = @()main('UI19.txt');
verifyWarning(testCase, f, 'inputwarn:C_w');
end

function testUI20(testCase)
f = @()main('UI20.txt');
verifyWarning(testCase, f, 'inputwarn:C_w');
end

function testUI21(testCase)
f = @()main('UI21.txt');
verifyWarning(testCase, f, 'inputwarn:hc');
end

function testUI22(testCase)
f = @()main('UI22.txt');
verifyWarning(testCase, f, 'inputwarn:hc');
end

function testUI23(testCase)
f = @()main('UI23.txt');
verifyWarning(testCase, f, 'inputwarn:hp');
end

function testUI24(testCase)
f = @()main('UI24.txt');
verifyWarning(testCase, f, 'inputwarn:hp');
end

function testUI25(testCase)
f = @()main('UI25.txt');
verifyWarning(testCase, f, 'inputwarn:tfinal');
end

function teardownOnce(testCase)
delete UI*.out;
end