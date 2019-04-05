classdef FractionalDelayLine < handle
    %DELAYLINE A basic elementwise Delay line
    %   A fixed length delay line
    
    properties
        buffer
        onex % x delayed by one sample 
        oney % y delayed by one sample
        currentPos % offset from the first position in the array
        frac % fractional part of delay line length
        method % first order allpass or linear interpolation
    end
    
    methods
        function obj = FractionalDelayLine(delayLineLength, interpolationMethod)
            % Compute frac first
            obj.frac=delayLineLength-floor(delayLineLength);
            
            % Initialize buffers and pointer
            obj.buffer = zeros(floor(delayLineLength)+1,1);
            obj.onex=0;
            obj.oney=0;
            obj.currentPos = 0;

            obj.method=interpolationMethod;
        end
        
        function xDelayed = process(obj, x)
            %PROCESS output delayed value given the current input sample
            % @param
            %   obj
            %   x the input value, one sample at a time
            % @Return
            %   xDelayed the delayed value.
            
            %integer part
            %save value to the buffer
            obj.buffer(mod(obj.currentPos,length(obj.buffer))+1)=x;
            
            %load value from buffer and output
            x_current=obj.buffer(mod(obj.currentPos+1,length(obj.buffer))+1);
            
            if strcmp(obj.method,'firstOrderAllpass')
                %calculate the delay using first order allpass method
                xDelayed=(1-obj.frac)/(1+obj.frac)*(x_current-obj.oney)+obj.onex;
            elseif strcmp(obj.method,'linearInterp')
                %calculate the delay using linear interpolation
                xDelayed=(1-obj.frac)*x_current+obj.frac*obj.onex;
            end
            
            % update buffers with delayed (by one sample) input  
            obj.onex=x_current;
            obj.oney=xDelayed;
            
            % update postion
            obj.currentPos=obj.currentPos+1;
        end
    end
end

