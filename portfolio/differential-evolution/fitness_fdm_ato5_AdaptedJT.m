%fitness function for the ATO -FDM

 function [cost]=fitness_fdm_ato5_AdaptedJT(x,y);

% the cost function was calculated respect to the 
% results obtained from the gains used in the paper or SPEC2018
% The inputs of the cost function are k0n, k1n and k2n, which
% are normalized in the range [0 2]. These gains are the gains
% of the ATO proposed in the SPEC2018. Those gains are normalized. 
% Normalized gains used in SPEC 2018:
%clc; close all;
% k0n = 640/1e3;    % normalized gains used
% k1n = 787200/1e6; % in SPEC 2018
% k2n = 5.99e7/1e8;
%================================================

% Variable assignment
k0n=x(1);
k1n=x(2);
k2n=x(3);

%% Denormalization
k0 = k0n*1e3;   %denormalization of k0 
k1 = k1n*1e6;   %denormalization of k1 
k2 = k2n*1e8;   %denormalization of k2 

%% Resolver signals and currents:
T = 1/50000;    % sampling period
Tfinal = 2;     % simulation goes from 0 to Tfinal
t = 0:T:Tfinal; % time vector
L = length(t);  % number of samples in simulation
wr = 2*pi*2500; % resolver excitation frequency
w0 = 2*pi*60;   % fundamental frequency
cost = 0;
ang=zeros(size(t));
for i=1:L;
    if t(i) < 0.1
        ang(i)=0;
    else
        ang(i)=100*t(i)-10;    
    end
end

ve=cos(wr.*t);      %resolver signals: ve
vs=sin(ang).*ve;    %vs
vc=cos(ang).*ve;    %vc

%stator currents
ia = cos(w0.*t); %+ 0.01.*cos(2.*wr.*t);
ib = cos(w0.*t + (2*pi/3));% + 0.01.*cos(2.*wr.*t + (2*pi/3));

%% Discrete-time model of the ATO
r = 1/(1+(k0*T));
b0 = (k1*T*T*r)+(k2*T*T*T*r);
b1 = 0-k1*T*T*r;
a1 = 0-(2+r);
a2 = 1+(r+r);
a3 = 0-r;
%numerator and denominator of the ATO
num_ATO=[b0 b1 0 0];
den_ATO=[1 a1 a2 a3];
poles_closed_loop=roots(num_ATO+den_ATO); %closed-loop poles
pmax=max(abs(poles_closed_loop)); %magnitude of the poles
% If pmax >1 then at least 1 poles is outside the unitary circle
% Then, the system is unstable

if pmax > 0.999
    cost = 10000; 
else
    % Test without crosstalk
    u0=0; u1=0; y0=0; y1=0; y2=0; y3=0;
    ange1=zeros(size(t));  %estimated angle
    for i=1:L
        s1 = vs(i); s2 = vc(i);
        u0 = ((cos(y0).*s1)-(sin(y0).*s2)).*ve(i); % u = fe
        y0 = (b0*u0 + b1*u1)-(a1*y1 + a2*y2 + a3*y3); %ATO output
        ange1(i)= y1; %estimated angle
        u1 = u0; %updating the past values of the signals
        y3 = y2;
        y2 = y1;
        y1 = y0;
    end
    error_1 = ang-ange1;            % error without perturbations
    abs_error_1= abs(error_1);      % absolute error
    peak_error = max(abs_error_1);  % maximum error peak
    
    % Settling time:
     final=0;
     i=L;
     set_time = Tfinal;
     while (final==0)
         i = i-1;
         if abs_error_1(i)> 0.001
            set_time = i*T-0.1;
            final=1; %finish the search
         end
     end

     
    % Test with crosstalk  ---------------------------------------
    u0=0; u1=0; y0=0; y1=0; y2=0; y3=0;
    iass=0;  ibss=0; 
    ange2=zeros(size(t));  %estimated angle
    for i=1:L
        s1 = vs(i) + ia(i);     % multiplexed signal
        s2 = vc(i) + ib(i);     % multiplexed signal
         
        if abs( ve(i) )<1e-5; %synchronous sampling
             iass=s1; 
             ibss=s2;
        end
        
        h1=s1-iass; %estimations of the resolver signals
        h2=s2-ibss; 
        u0 = ((cos(y0).*h1)-(sin(y0).*h2)).*ve(i); % u = fe
        y0 = (b0*u0 + b1*u1)-(a1*y1 + a2*y2 + a3*y3); %ATO output
        ange2(i)= y1; %estimated angle
        u1 = u0; %updating the past values of the signals
        y3 = y2;
        y2 = y1;
        y1 = y0;
    end
    error2 = ang-ange2; %estimation error with crosstalk
    sample = error2(L-90000:L); %take a sample of the steady-state condition
    crosstalk = max(abs(sample)); %maximum interference
    %cost=(0.25*peak_error/0.197915) + (0.25*set_time/0.06006) + (0.5*crosstalk/1.6383e-4);
    cost=(0.35*peak_error/0.197915) + (0.3*set_time/0.06006) + (0.35*crosstalk/1.6383e-4);
    % visualization
%     peak_error,
%     set_time,
%     crosstalk,
%     figure(100); 
%     subplot(211); plot(t, ang-ange1); grid on;
%     subplot(212); plot(t, ang-ange2); grid on;
end

%% Cost function 

end
    
