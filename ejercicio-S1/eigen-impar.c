#include<stdio.h>
#include<math.h>

// Funcion f(x)
double f(double E) {
double f1,L,V0;
L = 2.0; V0 = 10.0;
f1 = sqrt(2.0*(V0-E)) + sqrt(2.0*E)*(cos(L/2.0*sqrt(2.0*E)))/(sin(L/2.0*sqrt(2.0*E)));
return f1;
}

// Derivada g(x) = f'(x) 
double g(double E) {
double g1,L,V0;
L = 2.0; V0 = 10.0;
g1 = sqrt(2.0)*(pow(tan((L*sqrt(E))/sqrt(2.0)),-1.0))/(2.0*sqrt(E))-1.0/(2.0*sqrt(V0-E))-(L*pow(sin((L*sqrt(E))/sqrt(2.0)),-2.0)/pow(2.0,(3.0/2.0)));
return g1;	
}	


int main() {

int N; 
double x, tol, func, deriv;
tol = 1.0e-14;

printf("Introduzca la energía  inicial \n");
scanf("%lf",&x);

N = 0;

// Bucle newton-raphson
do {
func = f(x);
deriv = g(x);
// Contador iteraciones y salida de informacion
N = N + 1;
printf("N = %d  E = %.14lf  f(x) = %.14lf \n",N,x,func);

// Proteccion contra bucle infinito
if (N>10000) {
	printf("No converge tras 10000 pasos \n");
	break;  // (return 0 funciona igual)
	}

x = x - func/deriv; // Calculo v para siguiente iteracion 

// Fin de bucle do ... while
} while (fabs(func)>tol);



}
