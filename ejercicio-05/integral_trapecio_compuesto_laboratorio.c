#include <stdio.h>
#include <math.h>

// sea f(V) la función que define la diferencia entre los dos polinomios
double f(double V){
	double f, f1, f2;
	f1 = 1.5232 - 0.11878*V + 0.0027679*V*V;
	f2 = 1.3239 - 0.0689578*V;
	f = f1 - f2;
	return f;
}


double F(double V){
	double F, f1, f2;
	f1 = 1.5232*V - 0.11878*V*V/2.0 + 0.0027679*V*V*V/3.0;
	f2 = 1.3239*V - 0.0689578*V*V/2.0;
	F = f1 - f2;
	return F;
}
	
	
int main(){
	int N,i;
	double h, x, a, b, integral;
	double integral_F;

	printf(" Introduzca el valor de h:\n");
	scanf(" %lf",&h);
	printf(" Introduzca el valor de a (limite inferior de la integral):\n");
	scanf(" %lf",&a);
	printf(" Introduzca el valor de b (limite superior de la integral):\n");
	scanf(" %lf",&b);
	
	integral_F = F(b) - F(a);
	
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
	
	printf("valor exacto en [6,12] = %18.14lf \n", integral_F);
	
	return 0;
}
		
