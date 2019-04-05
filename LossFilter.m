classdef LossFilter < handle
    %LOSSFILTER A very basic lossfilter used in the homework
    
    properties
           a % filter parameter
           g % filter parameter
           Delayed % for y[n-1]
    end
    
    methods
        function obj = LossFilter(a,g)
            %LOSSFILTER the constructor for the loss filter, which takes
            %values of a and g
            if 0<g && g<1 && -1<a && a<=0 %make sure that a and g are in the range
                obj.a = a;
                obj.g = g;
                obj.Delayed = 0;
            else
                fprinf("not valid input");
                return;
            end
        end
    
        function output = process(obj, x)
           output = obj.g*x*(1+obj.a)-obj.a*obj.Delayed; % LCCDE of loss filter
           obj.Delayed = output; % update y[n-1]
        end
    end
end

