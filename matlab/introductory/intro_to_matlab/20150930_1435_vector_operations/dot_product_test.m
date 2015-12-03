close all
clear variables
clear all

format long e

N = 50;

scale1 = 2;
offset1 = 1.5;
scale2 = 5;
offset2 = -5;

a = ( rand(N,1) + offset1 ) * scale1;
b = ( rand(N,1) + offset2 ) * scale2;

%  method 1
dot1 = a' * b;

%  method 2
dot2 = sum( a .* b );

%  method 3
dot3 = cumsum( a .* b );
dot3 = dot3(end);

%  method 4
dot4 = dot(a,b);

%  check
disp('Check 1 and 2');
disp(dot1-dot2)
disp('Check 1 and 3');
disp(dot1-dot3)
disp('Check 2 and 3');
disp(dot2-dot3)
disp('Check 3 and 4');
disp(dot3-dot4)
