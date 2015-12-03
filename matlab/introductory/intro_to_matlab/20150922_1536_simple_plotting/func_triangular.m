function m = func_triangular(x)

m = zeros(size(x));

for kk = 1:numel(x)
    if x(kk) < -1
        m(kk) = 0;
    elseif ( x(kk) >= -1 ) && ( x(kk) < 0 )
        m(kk) = 1 + x(kk);
    elseif ( x(kk) >=  0 ) && ( x(kk) < 1 )
        m(kk) = 1 - x(kk);
    else
        m(kk) = 0;
    end
end

%  return m;

end
