close all
clear variables
clear classes
clear all

format long e

%  initialize
ao = EnvelopeDetector();

%  ao.N_big = 50;

ao.setup();

%  prep
opt = odeset...
    ( ...
    'Jacobian' , @ao.fJac , ...
    'InitialStep' , ao.simEndTime / ao.N_total , ...
    'MaxStep' , ao.simEndTime / ao.N_total ...
    );

%  solve
simEndTime = ao.simEndTime / 1e3 * 980;
tic
[t,x] = ode15s ( @ao.f , [0 simEndTime] , 0 , opt );
toc

%  plot
figure;
ho = plot(t,x,'LineWidth',3);
hold off;
hold on;
hi = plot(ao.t,ao.xOutput,'Color','r','LineWidth',3);
hold off;

xlabel('time (sec)')
title('Envelope Detector - Input and Output')
legend([ho hi],'output','input','Location','South','Orientation','Horizontal')
grid on;