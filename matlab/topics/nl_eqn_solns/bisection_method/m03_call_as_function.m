close all
clear variables
clear all

format long e

%{
This script calls the bisection method on the diode biasing circuit example.
The function to use is user-settable through a function handle.
The bisection method is implemented as a function. It returns an
array that accounts for the iterations and computations, and also
a status flag informing the user if this is a normal return.

The bisection method function has 3 compulsory arguments,
the others are optional. If these optional inputs are not provided
then a default value for each unprovided input is used.
Unprovided inputs are decided they are to be defaulted to if
they are missing in the list of arguments. The arguments
can be missing from the end of the list only.

The output argument flag is also optional. The bisection function
may or may not return it as desired by the user.
If no flag is returned, the user decides to plot or not according as
the soln array is empty or not.
%}

%  user sets these values
ch = 1;

switch lower(ch)
    case 1
        fhandle  = @func_bias_diode;
        limleft  = 0.65;
        limright = 0.9;

        abstol   = 1e-30;
        reltol   = 1e-3;
        ftol     = 1e-4;

        maxIter  = 50;
        
    case 2
        fhandle  = @func_bias_diode_with_exp;
        limleft  = 0.65;
        limright = 0.9;

        abstol   = 1e-30;
        reltol   = 1e-6;
        ftol     = 1e-8;

        maxIter  = 50;
        
    case 3
        fhandle  = @func_bias_diode;
        limleft  = 0.75;
        limright = 0.9;

        abstol   = 1e-30;
        reltol   = 1e-6;
        ftol     = 1e-8;

        maxIter  = 20;
        
    otherwise
        error('No such choice.')
end

%  plot the function values inside the given interval (for graphical view)
N = 1000;
x = linspace( limleft , limright , N );
y = fhandle(x);

figure;
plot(x,y)
xlabel('x')
ylabel('y')
title('function values')
grid on;

%  call as function

%  [s,flag] = ...
%      bisection_method ...
%          ( ...
%          fhandle , limleft , limright , abstol , reltol , ftol , maxIter ...
%          );

%  [s,flag] = ...
%      bisection_method ...
%          ( ...
%          fhandle , limleft , limright , abstol , reltol ...
%          );

%  [s] = ...
%      bisection_method ...
%          ( ...
%          fhandle , limleft , limright , abstol , reltol ...
%          );

[s] = ...
    bisection_method ...
        ( ...
        fhandle , limleft , limright , abstol , reltol , ftol ...
        );

%  check flag
if 1 == exist('flag')
    if -1 == flag
        error('No solution computed. Cannot continue...')
    end
else
    if isempty(s)
        error('No flag returned and no solution computed. Cannot continue...')
    end
end

%  plot errors in iterates and function values at the iterates
figure;
semilogy( 1:length(s) , [s(:).err_x] , 'LineWidth' , 4 )
hold on;
semilogy...
    ( 1:length(s) , [s(:).err_x] , ...
    'o' , 'LineWidth' , 2 , 'MarkerSize' , 12 , 'MarkerFaceColor' , 'r' ...
    )
hold off;
xlabel('iteration')
ylabel('error')
title('Relative Errors in Iterates')
grid on;

figure;
semilogy( 1:length(s) , [s(:).err_f] , 'LineWidth' , 4 )
hold on;
semilogy...
    ( 1:length(s) , [s(:).err_f] , ...
    'o' , 'LineWidth' , 2 , 'MarkerSize' , 12 , 'MarkerFaceColor' , 'r' ...
    )
hold off;
xlabel('iteration')
ylabel('error')
title('Relative Errors in Function Values')
grid on;
