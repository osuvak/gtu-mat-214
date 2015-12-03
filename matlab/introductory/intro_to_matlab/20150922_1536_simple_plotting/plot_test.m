close all
clear variables
clear all

t = 0:0.01:2;

x1 = sin(2*pi*t);
x2 = cos(2*pi*t);

%  x1(1:5)
%  x1(1,1:5)

disp('Last 5 entries of x1')
disp(x1(end-4:end))

noVal = 6;

disp(sprintf('Last %d entries of x1',noVal))
disp(x1(1,end-noVal+1:end))

%  plotting functions

%  figure(101);
figure;
plot(t,x1)
%  plot(t(2:end),x1(2:end))
%  plot(t(2:end),x1(2:length(x1)))

figure;
plot(t,x2)

figure;
h1 = plot(t,x1);
hold on;
%  plot(t,x2,'r')
h2 = plot(t,x2,'Color','r');
hold off;

legend([h1 h2],'x1','x2','Location','South','Orientation','Horizontal')

%  triangular
tt = linspace(-2,2,500);
xx = func_triangular(tt);

figure;
plot(tt,xx)
xlabel('tt')
ylabel('xx')
title('Plot of func triangular')

grid on