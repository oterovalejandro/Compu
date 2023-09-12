#include <stdio.h>
#include <math.h>

double f(double x1, double theta1){
	double f1;
	f1 = sqrt(16.0/9.80)/(sqrt(1.0-(pow(sin(theta1/2.0),2)) * pow(sin(x1),2)));
	return f1;
}

int main() {
	int N,i;
	double h, x, a, b, integral;
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
	h = (b-a)/N;
	
	//formula trapecio-compuesto
	integral = (f(a,theta0)+f(b,theta0))/2.0;
	
	//inicio del bucle
	for (i=1;i<N;i++){
		x = a+h;
		integral = integral + f(x,theta0);
		a = x;
	}
	//fin del bucle
	
	integral = integral * h;
	
	printf("h = %.9lf, N = %9d \n",h,N);
	printf("I = %18.14lf \n",integral);
	
	tsencillo = 2.0*pi*sqrt(1.0/9.8);
	printf("T = %18.14lf \n", tsencillo);
	
	return 0;
}
		
