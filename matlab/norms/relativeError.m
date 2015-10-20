function err = relativeError(a,b)
disp('Independent function ''relativeError'' called.');
err = norm(a-b) / (norm(a)+norm(b)/2);
end 
