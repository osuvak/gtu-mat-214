classdef EnvelopeDetector < handle

    properties(SetAccess=public,GetAccess=public)
    
        simEndTime = 1e-6

        N_small = 3
        N_big   = 20

        ptsPerPerPeriod = 1e3

        offset = 2
        a = -8e5

        C = 1e-10
        R = 1e3
        
        IS = 1e-14
        VT = 25e-3
        
    end
    
    properties(SetAccess=private,GetAccess=public)
        N_total
        
        t
        
        xSignal
        xCarrier
        xOutput
    end
    
    methods (Access=public)
        function obj = EnvelopeDetector()
            disp(sprintf('Creating %s object.',class(obj)))
        end
        
        function delete(obj)
            disp(sprintf('Destroying %s object.',class(obj)))
        end
        
        function setup(obj)
            obj.N_total = obj.N_big * 1e3;

            obj.t = linspace(0,obj.simEndTime,obj.N_total);
            
            t = obj.t;

            obj.xSignal = sin( t * 2 * pi / ( obj.simEndTime / obj.N_small ) ) .* exp(obj.a*t) + obj.offset;
            obj.xCarrier= sin( t * 2 * pi / ( obj.simEndTime / obj.N_big ) );

            obj.xOutput = obj.xSignal .* obj.xCarrier;
        end
        
        function m = f(obj,t,v)
            m = -1 / (obj.R * obj.C) * v + obj.IS / obj.C * exp( (obj.interpInput(t)-v) / obj.VT );
        end
        
        function m = fJac(obj,t,v)
            m = -1 / (obj.R * obj.C) + obj.IS / obj.C * ( -1 / obj.VT ) * exp( (obj.interpInput(t)-v) / obj.VT );
        end
    end
    
    methods (Access=private)
        function m = interpInput(obj,t)
            indices = find( t > obj.t );
            if isempty(indices)
                m = obj.xOutput(1);
            elseif numel(indices) == numel(obj.t)
                m = obj.xOutput(end);
            else
                k = indices(end);
                m = ( obj.xOutput(k+1) - obj.xOutput(k) ) / ( obj.t(k+1) - obj.t(k) ) * ( t - obj.t(k) ) + obj.xOutput(k);
            end
        end
    end

end
