//Programa escrito por Alejandro Otero Vazquez

#include<stdio.h>
#include<math.h>

// Funciona auxiliar vectorial para calcular F
void F(double t, double X[], double f[]) {
f[0] = 0.0;
f[1] = 0.0;
f[2] = 0.0;
f[3] = 0.0;
}

// y(0.01) = 0.001 (condicion inicial)


int main() {

int M=4;

// Declaracion de variables 
double h, t0, tf, tmax;
double x0[M], xf[M], f[M], xaux[M];
double k1[M], k2[M], k3[M], k4[M];
int i, j, N;

FILE * datos; 
datos = fopen("solucion.dat","w");

/*estructura del fichero solucion
t		x0		x1	...	xM-1
----------------------------
0.00	1		2	...	4
0.01	1.1		1.9	...	4.2
....
*/


// Lectura de datos iniciales 
printf("Introduzca el valor del incremento h:\n");
scanf("%lf",&h);
printf("Introduzca t0:\n");
scanf("%lf",&t0);
printf("Introduzca tmax:\n");
scanf("%lf",&tmax);
for(j=0;j<M;j++){
	printf("Introduzca el valor inicial de x[%d]: \n",j);
	scanf("%lf",&x0[j]);
}

N = ((tmax-t0)/h)+1.2;


// Condicion inicial
fprintf(datos, "%lf ", t0);
for(j=0;j<M;j++){
	fprintf(datos, "%lf ",x0[j]);
}
fprintf(datos, "\n");

for (i=1;i<=N;i++) {
tf = t0+h;

// Ecuaciones metodo RK4
F(t0,x0,f);

//k1
for(j=0;j<M;j++){
	k1[j] = f[j];
}

//k2
for(j=0;j<M;j++){
	xaux[j] = x0[j]+ 0.5*h*k1[j];
}
F(t0+0.5*h,xaux,f);
for(j=0;j<M;j++){
	k2[j] = f[j];
}

//k3
for(j=0;j<M;j++){
	xaux[j] = x0[j]+ 0.5*h*k2[j];
}
F(t0+0.5*h,xaux,f);
for(j=0;j<M;j++){
	k3[j] = f[j];
}

//k4
for(j=0;j<M;j++){
	xaux[j] = x0[j]+ h*k3[j];
}
F(t0+h,xaux,f);
for(j=0;j<M;j++){
	k4[j] = f[j];
}

for(j=0;j<M;j++){
	xf[j] = x0[j] + h*(k1[j]+2.0*k2[j]+2.0*k3[j]+k4[j])/6.0;
}

// Salida de datos al fichero
fprintf(datos, "%lf ", tf);
for(j=0;j<M;j++){
	fprintf(datos, "%lf ",xf[j]);
}
fprintf(datos, "\n");

// Se asignan valores de x0 para siguiente iteracion
t0 = tf;
for(j=0;j<M;j++){
x0[j] = xf[j];
}

} //Fin del bucle RK4

fclose(datos);

return 0;
}

