classdef DelayLine < handle
    %DELAYLINE A basic elementwise Delay line
    %   A fixed length delay line
    
    properties
        buffer
        currentPos %offset from the first position in the array
    end
    
    methods
        function obj = DelayLine(delayLineLength)
            %DELAYLINE Initialize the delay line by its length
            obj.buffer = zeros(delayLineLength+1,1);
            obj.currentPos = 0;
        end
              
        function xDelayed = process(obj, x)
            %PROCESS output delayed value given the current input sample
            % @param
            %   obj
            %   x the input value, one sample at a time
            % @Return
            %   xDelayed the delayed value.
            
            delay_amount = length(obj.buffer)-1;
            obj.currentPos = obj.currentPos +1;
            if delay_amount == 0 % If there is no delay
                obj.buffer(mod(obj.currentPos,delay_amount+1)+1) = x;
                xDelayed = obj.buffer(mod(obj.currentPos,delay_amount+1)+1);
            else
                obj.currentPos = mod(obj.currentPos,delay_amount); 
                xDelayed = obj.buffer(mod(obj.currentPos,delay_amount)+1);
                obj.buffer(mod(obj.currentPos,delay_amount)+1) = x;
            end
            
        end
    end
end

