function [s,varargout] = bisection_method(fhandle,limleft,limright,varargin)

%  user settable values
intervalInit.left.val  = limleft;
intervalInit.right.val = limright;

%  optional inputs (or defaults)
rdc = 3;

cnt = 4;
if nargin >= cnt
    abstol = varargin{cnt-rdc};
else
    abstol = 1e-30;
end

cnt = 5;
if nargin >= cnt
    reltol = varargin{cnt-rdc};
else
    reltol = 1e-6;
end

cnt = 6;
if nargin >= cnt
    ftol = varargin{cnt-rdc};
else
    ftol = 1e-8;
end

cnt = 7;
if nargin >= cnt
    maxIter = varargin{cnt-rdc};
else
    maxIter = 50;
end

%  plot the function values inside the given interval (for graphical view)
%{
N = 1000;
x = linspace( intervalInit.left.val , intervalInit.right.val , N );
y = fhandle(x);

figure;
plot(x,y)
xlabel('x')
ylabel('y')
title('function values')
grid on;
%}

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
    s = [];
    if nargout >= 1
        varargout{1} = -1; % return flag
    end
    warning('The interval is not valid and may not contain a root. Cannot continue...');
    return;
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
        interval.right = interval.mid;
    else
        interval.left = interval.mid;
    end
end

%  check if soln found and issue warning
if ~flag_SolnFound
    warning('A satisfactory soln could not be computed. Maximum number of iterations reached...')
end

%  prepare output
s = [];
for kk= 1:length(arrerr)
    s(kk).val  = arrsoln(kk).data.val;
    s(kk).fval = arrsoln(kk).data.fval;
    
    s(kk).err_x = arrerr(kk).err_x;
    s(kk).err_f = arrerr(kk).err_f;
end

if nargout >= 1
    if flag_SolnFound
        varargout{1} =  0; % return flag
    else
        varargout{1} = -2; % return flag
    end
end

return;

%  plot errors in iterates and function values at the iterates
%{
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
%}

end
