function la_with_norms_check
%  linear algebra (Ax=b) with norms check for the solution
%  computes x using several of the available methods (all based on G.E.)
%  and then checks if the computed solutions are almost the same
format long e

N = 100;
c1 = 4.5;
c2 = 2.5;

%  create random vector and matrix
rng('shuffle');
b = c1 * rand(N,1);
A = c2 * rand(N);

%  compute the solution in several ways
x = [];

%  backslash
x(1).val = A \ b;

%  with LU decomp
[L,U] = lu(A);
x(2).val = U \ (L \ b);

%  with LU decomp (partial pivoting - indices returned as a vector)
[L,U,p] = lu(A,'vector');
x(3).val = U \ (L \ b(p));

%  with LU decomp (partial pivoting - permutation matrix returned)
[L,U,P] = lu(A);
x(4).val = U \ (L \ (P * b) );

%  call the independent function to compute errors
disp('1 and 2')
disp(relativeError(x(1).val,x(2).val))
disp('2 and 3')
disp(relativeError(x(2).val,x(3).val))
disp('3 and 4')
disp(relativeError(x(3).val,x(4).val))

end
