classdef CommutedString < handle
    %COMMUTEDSTRING Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        delayline
        lossfilter
        previous
    end
    
    methods
        function obj = CommutedString(delayLineLength, a,g)
            %COMMUTEDSTRING 
            %   @param
            %       delayLineLength length of the delay line
            %       a,g parameters of the loss filter
            obj.lossfilter = LossFilter(a,g);
            obj.delayline = FractionalDelayLine(2*delayLineLength,'firstOrderAllpass');
            obj.previous = 0;
        end
        
        function y = process(obj,x)
            %PROCESS output the current output value given current input sample
            % @param
            %   obj
            %   x the input value, one sample at a time
            % @Return
            %   y the current output value(1 sample)
            filtered = obj.lossfilter.process(obj.previous);
            delayed = obj.delayline.process(filtered);
            y = delayed + x;
            obj.previous = y;
        end
    end
end

