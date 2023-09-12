#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include "generador.h"

int main(){
	
	int i,imax;
	int j;
	
	int N0,Nvivos,Nt;
	int Nb0,Nvivosb,Nbt; //nucleos del producto de las desintegraciones
	
	double lama,lamb,lammin;
	
	
	FILE *salida;
	
	salida = fopen("N1N2.dat","w");
	
	printf("1ª constante de desintegracion: \n");
	scanf("%lf",&lama);
	printf("2ª constante de desintegracion: \n");
	scanf("%lf",&lamb);
	printf("Numero inicial de nucleos radiactivos: \n");
	scanf("%d",&N0);

	Nb0=0;
	
	fprintf(salida,"%d %d %d \n",0,N0,Nb0);
	
	lammin = lama;
	if(lamb<lammin) lammin = lamb;
	
	imax = 5/lammin;
	Nt = N0;
	Nbt = Nb0;
	
	srand48(seed());
	
	for(i=1;i<=imax;i++){	//bucle temporal
		Nvivosb = Nbt;
		for(j=1;j<=Nvivosb;j++){	//bucle sobre nucleos			
			if(drand48()<=lamb){		//se desintegra
				Nbt=Nbt-1;
			}
		}
		Nvivos = Nt;
		for(j=1;j<=Nvivos;j++){	//bucle sobre nucleos			
			if(drand48()<=lama){		//se desintegra
				Nt = Nt-1;
				Nbt = Nbt +1;
			}
		}	
		fprintf(salida,"%d %d %d \n",i,Nt,Nbt);
	}
	
	fclose(salida);
	
return 0;
}
	
