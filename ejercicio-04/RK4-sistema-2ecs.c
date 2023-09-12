//Programa escrito por Alejandro Otero Vazquez

#include<stdio.h>
#include<math.h>

// Funciona auxiliar para calcular f(x,y,z)
double f(double x, double y, double z) {
double func;
func = - y - z;
return func; }

// Funciona auxiliar para calcular g(x,y,z)
double g(double x, double y, double z) {
double func;
func = 2.0*y - z;
return func; }

int main() {

// Declaracion de variables 
double h, x0, y0, z0, xf, yf, zf, xmax;
double k1, k2, k3, k4;
double l1, l2, l3, l4;
int i, N;

// Lectura de datos iniciales 
printf("Introduzca el valor del incremento h:\n");
scanf("%lf",&h);
printf("Introduzca x0:\n");
scanf("%lf",&x0);
printf("Introduzca xmax:\n");
scanf("%lf",&xmax);
printf("Introduzca y0:\n");
scanf("%lf",&y0);
printf("Introduzca z0:\n");
scanf("%lf",&z0);

N = ((xmax-x0)/h)+1.2;

FILE * datos; 
datos = fopen("rk4.dat","w");

// x0, y0, z0 ->  Valores en el punto anterior (x0, y0, z0)
// xf, yf, zf ->  Valores en el punto siguiente (xf, yf, zf)


// Condicion inicial
fprintf(datos, "%lf %lf %lf \n", x0, y0, z0);

for (i=1;i<=N;i++) {
xf = x0+h;
// Ecuaciones metodo RK4
k1 = f(x0,y0,z0);
l1 = g(x0,y0,z0);
k2 = f(x0+(h/2.0),y0+(h*(k1/2.0)),z0+(h*(l1/2.0)));
l2 = g(x0+(h/2.0),y0+(h*(k1/2.0)),z0+(h*(l1/2.0)));
k3 = f(x0+(h/2.0),y0+(h*(k2/2.0)),z0+(h*(l2/2.0)));
l3 = g(x0+(h/2.0),y0+(h*(k2/2.0)),z0+(h*(l2/2.0)));
k4 = f(x0+h,y0+(h*k3),z0+(h*l3));
l4 = g(x0+h,y0+(h*k3),z0+(h*l3));
yf = y0 + h*((k1+2.0*k2+2.0*k3+k4)/6.0);
zf = z0 + h*((l1+2.0*l2+2.0*l3+l4)/6.0);
// Salida de datos a fichero 
fprintf(datos, "%lf %lf %lf \n", xf, yf, zf); 

// Se asignan valores de x0, y0 para siguiente iteracion
x0 = xf;
y0 = yf;
z0 = zf;
}

fclose(datos);

return 0;
}

