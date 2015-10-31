close all
clear variables
clear all

format long e

%{
This script implements the bisection method on the diode biasing circuit example.
The function to use is now user-settable through a function handle.
Two functions describing the same problem are tested, one with the log
function, the other with exp. The choice of user inputs set is decided
with the 'ch' variable and user settings remain in switch cases.

Error checks for both iterates and function values at the
iterates are utilized, and both checks must be satisfied to terminate
the bisection method.

In addition, a maximum number of iterations check is incorporated
to be able to terminate with failure if the soln is not found
(error checks are not satisfied) in so many iterations.
%}

%  user sets these values
ch = 1;

switch lower(ch)
    case 1
        fhandle = @func_bias_diode;
        intervalInit.left.val  = 0.65;
        intervalInit.right.val = 0.9;

        abstol = 1e-30;
        reltol = 1e-6;
        ftol = 1e-8;

        maxIter = 50;
        
    case 2
        fhandle = @func_bias_diode_with_exp;
        intervalInit.left.val  = 0.65;
        intervalInit.right.val = 0.9;

        abstol = 1e-30;
        reltol = 1e-6;
        ftol = 1e-8;

        maxIter = 50;
        
    otherwise
        error('No such choice.')
        
end

%  plot the function values inside the given interval (for graphical view)
N = 1000;
x = linspace( intervalInit.left.val , intervalInit.right.val , N );
y = fhandle(x);

figure;
plot(x,y)
xlabel('x')
ylabel('y')
title('function values')
grid on;

%  pre-process
interval = intervalInit;
interval.left.fval  = fhandle( interval.left.val );
interval.right.fval = fhandle( interval.right.val );
interval.left.sign  = sign( interval.left.fval );
interval.right.sign = sign( interval.right.fval );

%  record the function value to compare to fval in iterates
fval_ref = min( abs( [ interval.left.fval interval.right.fval ] ) );

%  check if initial interval is valid
if interval.left.sign * interval.right.sign ~= -1
    error('The interval is not valid and may not contain a root. Cannot continue...');
end

%  initialize soln array
arrsoln = [];
arrerr  = [];

flag_SolnFound = 0;

%  iterate (will break when the script finds out an iterate satisfies the cond.)
while length(arrsoln) < maxIter
    disp(sprintf('The soln is between %.6e and %.6e',interval.left.val,interval.right.val))

    interval.mid.val  = 1 / 2 * ( interval.left.val + interval.right.val );
    interval.mid.fval = fhandle( interval.mid.val );
    interval.mid.sign = sign( interval.mid.fval );
    
    if isempty(arrsoln)
        % there is no data yet, initialize the arrays with the first arriving data
        arrsoln(1).data = interval.mid;
        
        arrsoln(end).data.err_x = 0;
        arrsoln(end).data.err_f = 0;
        
        arrerr(length(arrsoln)).err_x = arrsoln(end).data.err_x;
        arrerr(length(arrsoln)).err_f = arrsoln(end).data.err_f;
    else
        arrsoln(end+1).data = interval.mid;
        
        % check tolerances and quit the iterations if cond are satisfied
        % check - relative error in iterate
        x_lhs = norm( arrsoln(end).data.val - arrsoln(end-1).data.val );
        x_rhs = 0.5 * ( norm(arrsoln(end).data.val) + norm(arrsoln(end-1).data.val) );
        logicVal1 = ( x_lhs < reltol * x_rhs + abstol );
        % check - relative error in function value at the iterate
        f_lhs = norm( arrsoln(end).data.fval );
        f_rhs = fval_ref;
        logicVal2 = ( f_lhs < ftol * f_rhs );
        
        % record relative errors in both arrays
        arrsoln(end).data.err_x = x_lhs / x_rhs;
        arrsoln(end).data.err_f = f_lhs / f_rhs;
        
        arrerr(length(arrsoln)).err_x = arrsoln(end).data.err_x;
        arrerr(length(arrsoln)).err_f = arrsoln(end).data.err_f;
        
%          disp('Logic values check:')
%          disp(logicVal1)
%          disp(logicVal2)
        
        % actually check errors and break if necessary
        if logicVal1 && logicVal2
            disp(sprintf('Soln found in %d iterations.',length(arrsoln)));
            flag_SolnFound = 1;
            break;
        end
    end
    
    % error check failed - prepare intervals for the next iteration
    if interval.left.sign * interval.mid.sign == -1
%          interval.right.val  = interval.mid.val;
%          interval.right.fval = interval.mid.fval;
%          interval.right.sign = interval.mid.sign;
        
        interval.right = interval.mid;
    else
%          interval.left.val   = interval.mid.val;
%          interval.left.fval  = interval.mid.fval;
%          interval.left.sign  = interval.mid.sign;
        
        interval.left = interval.mid;
    end
end

%  check if soln found and issue warning
if ~flag_SolnFound
    warning('A satisfactory soln could not be computed. Maximum number of iterations reached...')
end

%  plot errors in iterates and function values at the iterates
figure;
semilogy( 1:length(arrerr) , [arrerr(:).err_x] , 'LineWidth' , 4 )
hold on;
semilogy...
    ( 1:length(arrerr) , [arrerr(:).err_x] , ...
    'o' , 'LineWidth' , 2 , 'MarkerSize' , 12 , 'MarkerFaceColor' , 'r' ...
    )
hold off;
xlabel('iteration')
ylabel('error')
title('Relative Errors in Iterates')
grid on;

figure;
semilogy( 1:length(arrerr) , [arrerr(:).err_f] , 'LineWidth' , 4 )
hold on;
semilogy...
    ( 1:length(arrerr) , [arrerr(:).err_f] , ...
    'o' , 'LineWidth' , 2 , 'MarkerSize' , 12 , 'MarkerFaceColor' , 'r' ...
    )
hold off;
xlabel('iteration')
ylabel('error')
title('Relative Errors in Function Values')
grid on;