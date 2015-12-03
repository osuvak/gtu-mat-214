close all
clear variables
clear all

format long e

%  user-defined
T = 10;
N = logspace(1.5,4.8);

a = -1e0;

initVal = 5;

%  compute
for kk = 1:3
    e(kk).val = [];
end
tic;
for ll = 1:length(N)

    %  preliminary computations
    t  = linspace(0,T,N(ll));
    dt = diff(t);
    dt = dt(1);

    %  solve
    s_e = initVal * exp( a * t );

    s(1).val    = zeros(size(t));
    s(1).val(1) = initVal;
    s(2).val    = s(1).val;
    s(3).val    = s(1).val;
    for kk = 2:length(t)
        s(1).val(kk) = ( 1 + a * dt ) * s(1).val(kk-1);
        s(2).val(kk) = 1 / ( 1 - a * dt ) * s(2).val(kk-1);
        s(3).val(kk) = ( 1 + a * dt / 2 ) / ( 1 - a * dt / 2 ) * s(3).val(kk-1);
    end

    for kk = 1:3
        tmp = max( abs( s(kk).val - s_e ) );
        e(kk).val = [ e(kk).val tmp ];
    end
end
toc;

dt_arr = T ./ ( N - 1 );

figure;
h1 = loglog(dt_arr(end:-1:1),e(1).val(end:-1:1),'Color','b','LineWidth',2);
hold off;
hold on;
h2 = loglog(dt_arr(end:-1:1),e(2).val(end:-1:1),'Color','r','LineWidth',2);
hold off;
hold on;
h3 = loglog(dt_arr(end:-1:1),e(3).val(end:-1:1),'Color','m','LineWidth',2);
hold off;

axis equal;

xlabel('time step')
ylabel('Max Abs Error')
title('Max Abs Error vs. time step')
legend([h1 h2 h3],'FE','BE','Trap','Location','South','Orientation','Horizontal')
grid on;