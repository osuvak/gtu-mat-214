close all
clear variables
clear all

format long e

%{
This is a preparation exercise for Gaussian elimination.
Two methods are considered for subtracting a specified vector 'a' from a
subvector of each row of a matrix. The coefficient multiplying the vector
'a' can be set to some special value or one.
%}

%  set values
chMethod = 2;
flagSetMultiplier = 1;

nExtraEntries = 2;
nScale = 10;
nRows = 3;

a = 0.5:0.5:2.5;

%  compute
nCols = length(a) + nExtraEntries;

B = nScale * rand( nRows , nCols );
C = B;

switch lower(chMethod)

    case 1
        %  add (this method uses a for loop)
        for kk = 1:size(B,1)
            if flagSetMultiplier
                coef = C(kk,end-length(a)+1) / a(1);
                
                C(kk,end-length(a)+1) = 0;
                C(kk,end-length(a)+2:end) = C(kk,end-length(a)+2:end) - coef * a(2:end);

%                  C(kk,end-length(a)+1:end) = C(kk,end-length(a)+1:end) - coef * a;
            else
                coef = 1;
                C(kk,end-length(a)+1:end) = C(kk,end-length(a)+1:end) - coef * a;
            end
        end
        
    case 2
        %  add(this method requires extra memory but does not use a for loop)
        if flagSetMultiplier
            temp = kron( C(:,end-length(a)+1) / a(1) , a(2:end) );
            C(:,end-length(a)+1) = zeros(size(C,1),1);
            C(:,end-length(a)+2:end) = C(:,end-length(a)+2:end) - temp;
            
%              temp = kron( C(:,end-length(a)+1) / a(1) , a );
%              C(:,end-length(a)+1:end) = C(:,end-length(a)+1:end) - temp;
        else
            temp = kron( ones(size(C,1),1) , a );
            C(:,end-length(a)+1:end) = C(:,end-length(a)+1:end) - temp;
        end
        
    otherwise
        error('No such method');
        
end

disp('Vector a')
disp(a)
disp('Matrix B')
disp(B)
disp('Matrix C')
disp(C)
disp('Matrix B-C')
disp(B-C)
