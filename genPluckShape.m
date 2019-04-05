function [y] = genPluckShape(n, pos)
%GENPLUCKSHAPE 
%   Generate Pluck Shape for the simple plucked string model
%   @param
%       n  length of the shape
%       pos the plucking position, 0<=pos<=1
%   @Return
%       y the output shape which has a length of n
   x = linspace(0,1,n);
   m1 = 1/pos; % slope for inclining part
   m2 = -1/(x(end)-pos); % slope for declining part
   b = 1/(x(end)-pos); % y intercept for declining part
   for i = 1:n
       if x(i) <= pos
            y(i) = m1*x(i); % linear eqn
       else
           y(i) = m2*x(i) + b; % linear eqn
       end 
   end
  
end

