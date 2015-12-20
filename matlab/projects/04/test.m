close all
clear variables
clear all

format long e
rng('shuffle');

%  function info
a = 0;
b = 0.75;

func = @(x) sin(2*pi*x);

N = 150;
N_ref = 10;

tol = 4e-2;
abstol = 5e-2;

ch = 2;

%  randomizer
xval = rand(1,N-2) * (b-a) + a;
xval = sort(xval,'ascend');
xval = [ a xval b ];

kk = 2;
switch lower(ch)

case 1
while 1
    if kk >= length(xval)
        break;
    end
    logicVal_p = ( ( norm(xval(kk)-xval(kk-1)) ) < (norm(xval(kk))+norm(xval(kk-1))) / 2 * tol + abstol );
    if logicVal_p
        xval = [ xval(1:kk-1) xval(kk+1:end) ];
    else
        kk = kk + 1;
    end
end
logicVal_n = ( ( norm(xval(end-1)-xval(end)) ) < (norm(xval(end-1))+norm(xval(end))) / 2 * tol + abstol );
if logicVal_n
    xval = [ xval(1:end-2) xval(end:end) ];
end

case 2
while 1
    if kk >= length(xval)
        break;
    end
    logicVal_p = ( norm(xval(kk)-xval(kk-1)) < norm(b-a)/N_ref );
    if logicVal_p
        xval = [ xval(1:kk-1) xval(kk+1:end) ];
    else
        kk = kk + 1;
    end
end
logicVal_n = ( norm(xval(end-1)-xval(end)) < norm(b-a)/N_ref );
if logicVal_n
    xval = [ xval(1:end-2) xval(end:end) ];
end

otherwise
    error('No such method for sparsification.');
end

fval = func(xval);

figure;
plot(xval,fval,'o','MarkerSize',6,'LineWidth',2)
grid on;

%  compute
[soln,vec] = interpinteg(xval,fval);

disp('Size intended')
disp(N)
disp('Size actual')
disp(length(xval))
disp('Vector')
disp(vec)
disp('Result')
disp(soln)