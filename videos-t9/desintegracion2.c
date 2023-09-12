#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include "generador.h"

int main(){
	
	int i,imax;
	int j;
	
	int N0,Nvivos,Nt;
	int Nb0,Nbt; //nucleos del producto de las desintegraciones
	int Nc0,Nct;
	
	double lam;
	
	double prob; //probabilidad del compuesto b
	
	FILE *salida;
	
	salida = fopen("PadreHijo.dat","w");
	
	printf("Constante de desintegracion: \n");
	scanf("%lf",&lam);
	printf("Numero inicial de nucleos radiactivos: \n");
	scanf("%d",&N0);
	printf("Probabilidad de que un nucleo se desintegre en el compuesto B: \n");
	scanf("%lf",&prob);
	
	Nb0=0;
	Nc0=0;
	
	fprintf(salida,"%d %d %d %d \n",0,N0,Nb0,Nc0);
	
	imax = 5/lam;
	Nt = N0;
	Nbt = Nb0;
	Nct = Nc0;
	
	srand48(seed());
	
	for(i=1;i<=imax;i++){	//bucle temporal
		Nvivos = Nt;
		for(j=1;j<=Nvivos;j++){	//bucle sobre nucleos
			if(drand48()<=lam){		//se desintegra
				Nt=Nt-1;
				if(drand48()<=prob){
					Nbt=Nbt+1;		//se aumentan los nucleos de tipo b
				}
				else Nct=Nct+1;
			}
		}
		fprintf(salida,"%d %d %d %d\n",i,Nt,Nbt,Nct);
	}
	
	fclose(salida);
	
	printf("Probabilidad de cada compuesto: \n");
	printf("B: %lf \n", 100*(double)Nbt/(double)N0);
	printf("C: %lf \n", 100.0 - 100*(double)Nbt/(double)N0);
	
return 0;
}
	
