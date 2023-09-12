#include <stdio.h>
#include <math.h>

double f(double x1) {
	double f1;
	if(x1==0)
	f1 = 0.0;
	else
	f1 = pow(x1,3)/(exp(x1)-1.0);
	return f1;
}

int main() {
	int N,i;
	double h, x, a, b, peso, integral;
	double pi;
	printf(" Introduzca el valor de h:\n");
	scanf(" %lf",&h);
	printf(" Introduzca el valor de a (limite inferior de la integral):\n");
	scanf(" %lf",&a);
	printf(" Introduzca el valor de b (limite superior de la integral):\n");
	scanf(" %lf",&b);
	
	N = (b-a)/h;
	if(N%2==1)
	N = N+1;
	h = (b-a)/N;
	
	//formula simpson-compuesto
	integral = (f(a) + f(b));
	
	//inicio del bucle
	x=a;
	for (i=1;i<=N-1;i++){
		x=x+h;
		if(i%2==1)
			peso = 4.0;
		else
			peso = 2.0;
		integral = integral + peso*f(x);
	}
	//fin del bucle
	
	integral = integral*h/3.0;
	
	printf("h = %.9lf, N = %9d \n",h,N);
	printf("I = %18.14lf \n",integral);
	
	pi = acos(-1.0);
	printf("valor exacto en [0,infinito) = %18.14lf \n", pow(pi,4)/15.0);
	
	return 0;
}
