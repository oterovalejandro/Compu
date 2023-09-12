#include <stdio.h>
#include <math.h>

#include "pendulo.h"

int main() {
	int N,i;
	double h, x, a, b, peso, integral;
	double pi, theta0;
	double tsencillo;
	pi = acos(-1.0);
	printf(" Introduzca el valor de h:\n");
	scanf(" %lf",&h);
	printf(" Introduzca el valor de a (limite inferior de la integral):\n");
	scanf(" %lf",&a);
	printf(" Introduzca el valor de b (limite superior de la integral en grados):\n");
	scanf(" %lf",&b);
	b = b*pi/180.0;
	
	printf(" Introduzca el valor de theta0 (angulo inicial en grados):\n");
	scanf(" %lf",&theta0);
	theta0 = theta0*pi/180.0;

	N = (b-a)/h;
	if(N%2==1)
	N = N+1;
	h = (b-a)/N;
	
	//formula simpson-compuesto
	integral = (f(a,theta0) + f(b,theta0));
	
	//inicio del bucle
	x=a;
	for (i=1;i<=N-1;i++){
		x=x+h;
		if(i%2==1)
			peso = 4.0;
		else
			peso = 2.0;
		integral = integral + peso*f(x,theta0);
	}
	//fin del bucle
	
	integral = integral*h/3.0;
	
	printf("h = %.9lf, N = %9d \n",h,N);
	printf("I = %18.14lf \n",integral);
	
	tsencillo = 2.0*pi*sqrt(1.0/9.8);
	printf("T = %18.14lf \n", tsencillo);
	
	return 0;	
}
