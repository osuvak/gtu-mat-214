close all
clear variables
clear all

A = [ 1 2 ; 3 5 ];
b = [ 1 ; 2 ];

x1 = A \ b;

[L,U] = lu(A);
