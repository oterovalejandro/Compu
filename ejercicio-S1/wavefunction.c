//Programa escrito por Alejandro Otero Vazquez

#include<stdio.h>
#include<math.h>

// Funcion auxiliar para calcular f(x,y,z)
double f(double x, double y, double z) {
	double func;
	func = z;
	return func;
}

// Funcion auxiliar para calcular g(x,y,z)
double g(double x, double y, double z, double E) {
	double func, V;
	
	if(x>=-1.0 && x<=1.0){
		V = 0.0;}
	else{
		V = 10.0;}
	
	func = -2.0*(E-V)*y;
	
	return func;
}

int main() {
	
	// Declaracion de variables 
	double h, x0, y0, z0, xf, yf, zf, xmax;
	double k1, k2, k3, k4;
	double l1, l2, l3, l4;
	int i, N, nivel;
	double E,V0;
	V0 = 10.0;
	
	// Lectura de datos iniciales 
	printf("Defina el nivel de energía del sistema: \n");
	scanf("%d",&nivel);
	switch (nivel){
		case 0: E=0.81974007376663;
		break;
		case 1: E=3.22093997858959;
		break;
		case 2: E=6.94576649122619;
		break;
	}
	printf("E = %lf \n",E);
	
	h = 0.0001;
	x0 = -4.0;
	xmax = 4.0;
	
	y0 = exp(x0*sqrt(2*(V0-E)));	
	z0 = sqrt(2*(V0-E))*exp(x0*sqrt(2*(V0-E)));

	N = ((xmax-x0)/h)+1.2;
	//printf("N = %d \n",N);
	
	double x[N+1], psi[N+1];

	// x0, y0, z0 ->  Valores en el punto anterior (x0, y0, z0)
	// xf, yf, zf ->  Valores en el punto siguiente (xf, yf, zf)

	// Condicion inicial
	x[0] = x0;
	psi[0] = y0;

	for (i=1;i<=N;i++) {
	xf = x0+h;
	// Ecuaciones metodo RK4
	k1 = f(x0,y0,z0);
	l1 = g(x0,y0,z0,E);
	k2 = f(x0+(h/2.0),y0+(h*(k1/2.0)),z0+(h*(l1/2.0)));
	l2 = g(x0+(h/2.0),y0+(h*(k1/2.0)),z0+(h*(l1/2.0)),E);
	k3 = f(x0+(h/2.0),y0+(h*(k2/2.0)),z0+(h*(l2/2.0)));
	l3 = g(x0+(h/2.0),y0+(h*(k2/2.0)),z0+(h*(l2/2.0)),E);
	k4 = f(x0+h,y0+(h*k3),z0+(h*l3));
	l4 = g(x0+h,y0+(h*k3),z0+(h*l3),E);
	yf = y0 + h*((k1+2.0*k2+2.0*k3+k4)/6.0);
	zf = z0 + h*((l1+2.0*l2+2.0*l3+l4)/6.0);
	 
	x[i] = xf;
	psi[i] = yf;

	// Se asignan valores de x0, y0 para siguiente iteracion
	x0 = xf;
	y0 = yf;
	z0 = zf;
	
	}
	
	//INTEGRACIÓN
	x0 = -4.0;
	xmax  = 4.0;
	N = (xmax-x0)/h;
	h = (xmax-x0)/N;
	
	//printf("h =%lf  N=%d  x0=%lf  xmax=%lf  psi=%lf \n",h,N,x0,xmax,psi[40000]);
	
	double I;
	
	//formula trapecio-compuesto
	I = (pow(psi[0],2)+pow(psi[N],2))/2.0;
	
	//inicio del bucle
	for (i=1;i<N;i++){
		I = I + pow(psi[i],2);
	}
	I = I * h;
	
	
	//NORMALIZACIÓN
	FILE * datos; 
	datos = fopen("funcion.dat","w");
	
	double psi_norm[N+1];
	
	for(i=0;i<=N;i++){
		psi_norm[i] = psi[i]/sqrt(I);
		fprintf(datos, "%lf %lf \n", x[i], psi_norm[i]);
	}
	

	//PROBABILIDAD
	double P;
	int a,b;
	a = (3.0/8.0)*N;
	b = (5.0/8.0)*N;
	//printf("a=%d b=%d \n",a,b);
	
	//formula trapecio-compuesto
	P = (pow(psi_norm[b],2)+pow(psi_norm[a],2))/2.0;
	
	//inicio del bucle
	for (i=a+1;i<b;i++){
		P = P + pow(psi_norm[i],2);
	}
	P = P * h;
	P = 1.0 - P;
	
	printf("P´ = %18.14lf \n",P);
	
	
	//VALOR ESPERADO DEL CUADRADO DE LA POSICION
	double I2;
	
	//formula trapecio-compuesto
	I2 = (pow(psi_norm[N]*x[N],2)+pow(psi_norm[0]*x[0],2))/2.0;
	
	//inicio del bucle
	for (i=1;i<N;i++){
		I2 = I2 + pow(psi_norm[i]*x[i],2);
	}
	I2 = I2 * h;
	
	printf("I2 = %18.14lf \n",I2);
	
	fclose(datos);
	return 0;
}

