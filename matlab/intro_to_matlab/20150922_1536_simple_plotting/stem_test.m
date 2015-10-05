close all
clear variables
clear all

tt = linspace(-2,2,21);
xx = func_triangular(tt);

figure;
stem(tt,xx)

figure;
stem(tt,xx,'filled')

figure;
stem(tt,xx,'filled','Color','r')