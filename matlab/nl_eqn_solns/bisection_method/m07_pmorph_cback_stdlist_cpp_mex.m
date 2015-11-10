close all
clear variables
clear all

format long e

%{
This calls the mex function in which the bisection method has already been implemented in C++.
The user defined values are given as arguments to the mex function.

The objective function (func_bias_diode) is hardcoded into the mex lib.
This is a disadvantage. If another objective function is desired, one must
modify the C++ code and compile/link it again.
%}

%  user sets these values
limleft  = 0.65;
limright = 0.9;

abstol = 1e-30;
reltol = 1e-6;
ftol   = 1e-8;

maxIter = 50;

%  plot the function values inside the given interval (for graphical view)
N = 1000;
x = linspace( limleft , limright , N );
y = func_bias_diode(x);

figure;
plot(x,y)
xlabel('x')
ylabel('y')
title('function values')
grid on;

%  solve (call mex function)
ch = 2;
switch lower(ch)
    case 5
        [soln,flag] = ...
            bisection_pmorph_cback_stdlist_cpp_mex ...
                ( ...
                limleft , limright , abstol , reltol , ftol , maxIter ...
                );
    case 4
        [soln,flag] = ...
            bisection_pmorph_cback_stdlist_cpp_mex ...
                ( ...
                limleft , limright , abstol , reltol , ftol ...
                );
    case 3
        [soln,flag] = ...
            bisection_pmorph_cback_stdlist_cpp_mex ...
                ( ...
                limleft , limright , abstol , reltol ...
                );
    case 2
        [soln,flag] = ...
            bisection_pmorph_cback_stdlist_cpp_mex ...
                ( ...
                limleft , limright , abstol ...
                );
    otherwise
        [soln,flag] = ...
            bisection_pmorph_cback_stdlist_cpp_mex ...
                ( ...
                limleft , limright ...
                );
end

%  check flag
if -2 == flag
    warning('A satisfactory soln could not be computed. Maximum number of iterations reached...')
end

if -1 == flag
    error('The initial interval is not valid.')
end
        
%  plot errors in iterates and function values at the iterates
figure;
semilogy( 1:length(soln) , [soln(:).err_x] , 'LineWidth' , 4 )
hold on;
semilogy...
    ( 1:length(soln) , [soln(:).err_x] , ...
    'o' , 'LineWidth' , 2 , 'MarkerSize' , 12 , 'MarkerFaceColor' , 'r' ...
    )
hold off;
xlabel('iteration')
ylabel('error')
title('Relative Errors in Iterates')
grid on;

figure;
semilogy( 1:length(soln) , [soln(:).err_f] , 'LineWidth' , 4 )
hold on;
semilogy...
    ( 1:length(soln) , [soln(:).err_f] , ...
    'o' , 'LineWidth' , 2 , 'MarkerSize' , 12 , 'MarkerFaceColor' , 'r' ...
    )
hold off;
xlabel('iteration')
ylabel('error')
title('Relative Errors in Function Values')
grid on;
