close all
clear variables
clear classes
clear all

format long e

%  initialize
ao = EnvelopeDetector();

%  ao.N_big = 50;

ao.setup();

%  solve by fe
tic
xfe = solve_by_fe( @ao.f , ao.t , 0 );
toc

%  solve by ode15s
%    prep
opt = odeset...
    ( ...
    'Jacobian' , @ao.fJac , ...
    'InitialStep' , ao.simEndTime / ao.N_total , ...
    'MaxStep' , ao.simEndTime / ao.N_total ...
    );

%    solve
simEndTime = ao.simEndTime;
tic
[t,x] = ode15s ( @ao.f , [0 simEndTime] , 0 , opt );
toc

%  plot
figure;
ho = plot(t,x,'Color','m','LineWidth',2);
hold off;
hold on;
hofe = plot(ao.t,xfe,'LineWidth',2);
hold off;
hold on;
hi = plot(ao.t,ao.xOutput,'Color','r','LineWidth',2);
hold off;

xlabel('time (sec)')
title('Envelope Detector - Input and Output')
legend([ho hofe hi],'output (ode15s)','output (fe)','input','Location','South','Orientation','Horizontal')
grid on;

%  plot
figure;
ho = plot(t,x,'Color','m','LineWidth',2);
hold off;
hold on;
hi = plot(ao.t,ao.xOutput,'Color','r','LineWidth',2);
hold off;

xlabel('time (sec)')
title('Envelope Detector - Input and Output')
legend([ho hi],'output (ode15s)','input','Location','South','Orientation','Horizontal')
grid on;