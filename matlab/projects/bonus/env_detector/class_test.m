close all
clear variables
clear classes
clear all

format long e

%  initialize
ao = EnvelopeDetector();
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
plot(t,x)
hold off;
hold on;
plot(ao.t,ao.xOutput,'Color','r')
hold off;

grid on;