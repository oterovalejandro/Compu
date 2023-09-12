#include <stdio.h>
#include <math.h>

#include "stefan.h"

int main() {
	int N,i;
	double h, x, a, b, integral;
	double pi;
	printf(" Introduzca el valor de h:\n");
	scanf(" %lf",&h);
	printf(" Introduzca el valor de a (limite inferior de la integral):\n");
	scanf(" %lf",&a);
	printf(" Introduzca el valor de b (limite superior de la integral):\n");
	scanf(" %lf",&b);
	
	N = (b-a)/h;
	h = (b-a)/N;
	
	//formula trapecio-compuesto
	integral = (f(a)+f(b))/2.0;
	
	//inicio del bucle
	for (i=1;i<N;i++){
		x = a+h;
		integral = integral + f(x);
		a = x;
	}
	//fin del bucle
	
	integral = integral * h;
	
	printf("h = %.9lf, N = %9d \n",h,N);
	printf("I = %18.14lf \n",integral);
	
	pi = acos(-1.0);
	printf("valor exacto en [0,infinito) = %18.14lf \n", pow(pi,4)/15.0);
	
	return 0;
}
		
