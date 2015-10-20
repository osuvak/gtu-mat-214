function norms_test

%  %  do not clear inside a function
%  close all
%  clear variables
%  clear all

N = 1000;
c = 4.5;

%  create random vector
rng('shuffle');
v = c * rand(N,1);

%  compute norms in several ways and put them in a struct array
norms = [];
norms(1).val = norm(v);
norms(2).val = norm(v,2);
norms(3).val = sqrt(sum(v.*v));
norms(4).val = sqrt(sum(v.^2));

%  call the nested function to compute errors
disp('1 and 2')
disp(relativeError(norms(1).val,norms(2).val))
disp('2 and 3')
disp(relativeError(norms(2).val,norms(3).val))
disp('3 and 4')
disp(relativeError(norms(3).val,norms(4).val))

%  inner function in nested functions
function err = relativeError(a,b)
disp('Nested function ''relativeError'' called.');
err = norm(a-b) / (norm(a)+norm(b)/2);
end

end