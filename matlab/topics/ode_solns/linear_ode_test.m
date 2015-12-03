close all
clear variables
clear all

format long e

%  user-defined
T = 10;
N = 51;

a = -1e0;

initVal = 5;

%  preliminary computations
t  = linspace(0,T,N);
dt = diff(t);
dt = dt(1);

%  solve
s_e = initVal * exp( a * t );

s(1).val    = zeros(size(t));
s(1).val(1) = initVal;
s(2).val    = s(1).val;
s(3).val    = s(1).val;
for kk = 2:length(t)
    s(1).val(kk) = ( 1 + a * dt ) * s(1).val(kk-1);
    s(2).val(kk) = 1 / ( 1 - a * dt ) * s(2).val(kk-1);
    s(3).val(kk) = ( 1 + a * dt / 2 ) / ( 1 - a * dt / 2 ) * s(3).val(kk-1);
end

%  plot
figure;
he = plot(t,s_e,'Color','k','LineWidth',2);
hold off;
hold on;
h1 = plot(t,s(1).val,'Color','b','LineWidth',2);
hold off;
hold on;
h2 = plot(t,s(2).val,'Color','r','LineWidth',2);
hold off;
hold on;
h3 = plot(t,s(3).val,'Color','m','LineWidth',2);
hold off;

xlabel('time (sec)')
title('Exact and Numerical Solutions')
legend([he h1 h2 h3],'exact','FE','BE','Trap','Location','NorthEast')
grid on;


figure;
hh1 = plot(t,s(1).val-s_e,'Color','b','LineWidth',2);
hold off;
hold on;
hh2 = plot(t,s(2).val-s_e,'Color','r','LineWidth',2);
hold off;
hold on;
hh3 = plot(t,s(3).val-s_e,'Color','m','LineWidth',2);
hold off;

xlabel('time (sec)')
title('Errors in the Numerical Solutions')
legend([hh1 hh2 hh3],'FE','BE','Trap','Location','NorthEast')
grid on;