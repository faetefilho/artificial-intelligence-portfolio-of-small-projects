    
    VTR = 1.e-6;
	D = 3; 
	XVmin = [0 0 0]; 
	XVmax = [2 2 2]; 
	y=[];
	NP = 10*D; 
	itermax = 100; 
	F = 0.5; % default 0.8
	CR = 0.5; % default 0.5
	strategy = 7;
	refresh = 1; 
    
    [bestmem,bestval,nfeval,Alldata] = devec3_AdaptedJT('fitness_fdm_ato5_AdaptedJT',VTR,D,XVmin,XVmax,y,NP,itermax,F,CR,strategy,refresh);
    
    % Output data results of DE algorithm
    subplot(1,2,1);
    plot(Alldata(:,1),Alldata(:,2))
    grid on
    xlabel('Iterations')
    ylabel('Cost Function (best individual)')
    % ylim([0 1])
    subplot(1,2,2);
    plot(Alldata(:,1),Alldata(:,3),Alldata(:,1),Alldata(:,4),Alldata(:,1),Alldata(:,5))
    grid on
    xlabel('Iterations')
    ylabel('Population best individual, normalized (k0, k1 & k2)')
    legend('k0','k1','k2')
    
    %
    % costfunall=[0.648199 0.648189 0.648215 0.648208 0.648239 0.648288]
