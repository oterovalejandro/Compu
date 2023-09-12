#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include "generador.h"

int main(){
	long long tmax,N,Ninf; 
	long long i,j,k;
	
	double rho,L,tita;
	
	double tini, tend;
	
	FILE *salida;
	salida = fopen("plot.dat","w");
	
	FILE *geom;
	geom = fopen("geom.dat","w");
	
	printf("Numero de particulas: \n");
	scanf ("%lld",&N);
	printf("Densidad de particulas en el recinto: \n");
	scanf ("%lf",&rho);
	printf("Numero de interacciones: \n");
	scanf ("%lld",&tmax);
	
	L = sqrt((double)N/rho);
	
	fprintf(geom,"%lld\n%lld\n%lf\n",N,tmax,L);
	
	double x[N],y[N];
	int inf[N];
	double d;
	
	srand48(seed()); //semilla
	
	tini = timeinseconds();
	
	for(i=0;i<N;i++) inf[i]=0;
	
	
	x[0] = scalerandom(drand48(),0,L);
	y[0] = scalerandom(drand48(),0,L);
	
	for(i=1;i<N;i++){
		do{
			x[i] = scalerandom(drand48(),0,L);
			y[i] = scalerandom(drand48(),0,L);
			d = 0;
			for(j=0;j<i;j++){
				if(sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2))<1.1) d++;
			}
		}
		while(d!=0);
		//fprintf(salida,"%lf %lf \n",x[i],y[i]);
	}
	
	k = scalerandom(drand48(),0,N);
	inf[k] = 1;
	
	for(j=1;j<=tmax;j++){
		Ninf = 0;
		for(i=0;i<N;i++){
			tita = scalerandom(drand48(),0,2*M_PI);
			x[i] = x[i] + cos(tita);
			if(x[i]>L) x[i]=L-0.1;
			if(x[i]<0.0) x[i]=0.1;
			y[i] = y[i] + sin(tita);
			if(y[i]>L) y[i]=L-0.1;
			if(y[i]<0.0) y[i]=0.1;
			for(k=0;k<N;k++){
				if(sqrt(pow(x[k]-x[i],2)+pow(y[k]-y[i],2))<1){
					
					if(inf[k]==1||inf[i]==1) {
						inf[k]=1;
						inf[i]=1;
					}
					else {		//no haria falta ponerlo
						inf[k]=0;
						inf[i]=0;
					}
				}
			}
			fprintf(geom,"%d %lf %lf\n",inf[i],x[i],y[i]);
		}
		for(k=0;k<N;k++){
			Ninf = Ninf + inf[k];
		}
		fprintf(salida,"%lld %lf \n",j,100*(double)Ninf/(double)N);
	}
	
	tend = timeinseconds();
	
	printf("El tiempo de calculo ha sido %lf s \n",tend-tini);
	
	fclose(salida);
	
return 0;
}
		
