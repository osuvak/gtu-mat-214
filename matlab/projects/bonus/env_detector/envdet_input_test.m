close all
clear variables
clear all

format long e

%  user-defined
simEndTime = 1e-6;

N_small = 3;
N_big   = 20;

ptsPerPerPeriod = 1e3;

offset = 2;
a = -8e5;

%  preliminary computation
N_total = N_big * 1e3;

t = linspace(0,simEndTime,N_total);

xSignal = sin( t * 2 * pi / ( simEndTime / N_small ) ) .* exp(a*t) + offset;
xCarrier= sin( t * 2 * pi / ( simEndTime / N_big ) );

xOutput = xSignal .* xCarrier;

%  plot
figure;
hs = plot(t,xOutput,'LineWidth',2);
hold off;
hold on;
he = plot( t , +xSignal , 'Color','r','LineWidth',2);
hold off;
hold on;
plot( t , -xSignal , 'Color','r','LineWidth',2)
hold off;

xlabel('time (sec)')
title('Signal and Its Envelope')
legend([hs he],'signal','envelope','Location','South','Orientation','Horizontal')
grid on;

fileID = fopen('input.cir','w');
fprintf(fileID,'vin 1 0 pwl\n+(\n');
for kk = 1:numel(t)
    fprintf(fileID,'+ %.8e %.8e\n',t(kk),xOutput(kk));
end
fprintf(fileID,'+)');
fclose(fileID);