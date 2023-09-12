#include <stdio.h>
#include <math.h>
 
void Function(double x[], double f[],double C[][3],double R[]) {
	for(int i=0;i<3;i++){
	f[i] = pow(x[0]-C[i][0],2) + pow(x[1]-C[i][1],2) + pow(x[2]-C[i][2],2) - pow(R[i],2);
	}
}

void matrixmult(int N, double A[][N], double B[][N], double C[][N]) {
int i,j,k;
for(i=0;i<N;i++) {
  for(j=0;j<N;j++) {
    C[i][j] = 0.0;
    for(k=0;k<N;k++) {
      C[i][j] = C[i][j] + A[i][k]*B[k][j];
    }
  }
}
}

void LU_decomp(int N, double A[][N], double L[][N], double U[][N], int P[], double *par, int *sing) {
 int i, j, k, imax, l;
 double Umax, temp;
 double A2[N][N];
 *par = 1.0; // Paridad inicial igual a 1
 for(i=0;i<N;i++) { P[i] = i; } // Inicializacion de vector P
 // Copiamos A en nuevo array A2 para no modificar el array A original en main 
 for(i=0;i<N;i++) {
   for(j=0;j<N;j++) {
     A2[i][j] = A[i][j];   
   }
 }
 for (j=0;j<N;j++) { // Bucle sobre columnas de A 
   L[j][j] = 1.0;
   Umax = A2[j][j]; // Inicio en fila j de busqueda de pivote
   imax = j;
   for(i=j+1;i<N;i++) { // Bucle de busqueda de pivotes
     if(fabs(A2[i][j])>fabs(Umax)) {Umax = A2[i][j]; imax=i;}
   } // Umax contiene ahora A[i][j] de mayor valor absoluto (con i>=j)
   if(j!=imax) { // Se intercambian filas si el pivote no es diagonal
     *par = -*par; // Cambio de paridad (para calculo de determinante)
     for (k=0;k<N;k++) { // Permutamos filas imax, j de A
       temp = A2[imax][k];
       A2[imax][k] = A2[j][k];
       A2[j][k] = temp; }
     for(k=0;k<j;k++) { // Permutamos filas imax, j de L (tan solo
       temp = L[imax][k]; // los elementos de las primeras j columnas)
       L[imax][k] = L[j][k];
       L[j][k] = temp; }
     l = P[imax]; // Terminamos permutando elementos imax, j del array P
     P[imax]=P[j];
     P[j] = l;
   } // Fin de condicional if
   for (i=0;i<=j;i++) { // Comienzo de algoritmo de Crout
     U[i][j] = A2[i][j];
     for (k=0;k<i;k++) {
       U[i][j] = U[i][j] - L[i][k]*U[k][j]; }
   }
   for (i=j+1;i<N;i++) {
     L[i][j] = A2[i][j];
     for (k=0;k<j;k++) {
       L[i][j] = L[i][j] - L[i][k]*U[k][j]; }
       L[i][j] = L[i][j]/U[j][j];
   } // Fin de algoritmo de Crout
   if(fabs(U[j][j])<1e-10) { // Si Ujj es casi cero, A es singular
   *sing=1; } // Devolvemos entonces valor no nulo de *sing
 } // Fin de bucle sobre columnas de A
// Anulamos los coeficientes no calculados de L y U
 for (j=1;j<N;j++) {
   for (i=0;i<j;i++) {
     L[i][j] = 0.0;
     U[j][i] = 0.0; }
 }
}

void LU_solve(int N, double L[][N], double U[][N], int P[], double b[], double x[]) {
 double sum, y[N], bp[N];
 int i, j;
// Aplicamos permutación al vector b:
 for(i=0;i<N;i++) {
     bp[i] = b[P[i]];
  }
// Sustitución progresiva
 for (i=0;i<N;i++) {
   sum = 0; 
   for (j=0;j<i;j++) {
     sum = sum + L[i][j]*y[j];
   }
   y[i] = (bp[i] - sum)/L[i][i];
 }
// Sustitución regresiva
 for(i=N-1;i>=0;i--) {
   sum = 0;
   for(j=i+1;j<N;j++) {
     sum = sum + U[i][j]*x[j]; 
   }
   x[i] = (y[i]-sum)/U[i][i];
 }
}

int main() {

int N,op,i,j;
double x[3],f[3],C[3][3],R[3];
double dat[3][4];
double J[3][3],Jinv[3][3];
double det=1.0;
double tol;
double L[3][3];
double U[3][3];
double LtimesU[3][3];
int P[3];
double par;
int sing = 0;

double b[3];
double xl[3];

FILE * input;
input = fopen("datos.dat","r");

printf("Seleccione la opcion que prefiera:\n");
printf("1.- Leer datos de un ficherpo (datos.dat)\n");
printf("2.- Introducir datos manualmente\n");
scanf("%d", &op);

switch(op) {
	case 1:
	for(i=0;i<3;i++) {
		for(j=0;j<4;j++) {
			fscanf(input,"%lf", &dat[i][j]);
		}
	}
	for(i=0;i<3;i++) {
		R[i] = dat[i][3];
		for(j=0;j<3;j++) {
			C[i][j] = dat[i][j];
		}
	}
	break;
	
	case 2:
	for(i=0;i<3;i++) {
		printf("Coordenadas de la %dª esfera: \n", i+1);
		scanf("%lf %lf %lf", &C[i][0], &C[i][1], &C[i][2]);
		printf("Radio de la %dª esfera: \n", i+1);
		scanf("%lf", &R[i]);
	}
	break;
	
	default:
	printf("Seleccione una opcion correcta\n");
	break;	
}
printf("Valores iniciales de las coordenadas x y z \n");
scanf("%lf %lf %lf", &x[0], &x[1], &x[2]);

tol = 1.0e-12;

// Inicializamos a 0 el contador de iteraciones
N=0;

// Bucle do while del metodo de Newton-Raphson 
do {

// Evaluamos el valor de la funcion y de la inversa del jacobiano: 
Function(x,f,C,R);

// Calculo del Jabobiano:
for(i=0;i<3;i++) {
	for(j=0;j<3;j++) {
		J[i][j] = 2*(x[j]-C[i][j]);
	}
}

//Calculo de inversa de jacobiano	
LU_decomp(3,J,L,U,P,&par,&sing);
matrixmult(3,L,U,LtimesU);

for(i=0;i<3;i++) {
 det = det*U[i][i];
}
det = det*par;

for(j=0;j<3;j++) { 
 for(i=0;i<3;i++) { 
 if(i==j) b[i] = 1.0;
 else b[i] = 0.0;
 }
 LU_solve(3,L,U,P,b,xl); 
 for(i=0;i<3;i++) { 
 Jinv[i][j] = xl[i];
 }
} 

// Incrementamos el contador de iteraciones en 1
N++;

printf("N = %d x = %.8lf y = %.8lf z = %.8lf f(0) = %.12lf f(1) = %.12lf f(2) = %.12lf \n",N,x[0],x[1],x[2],f[0],f[1],f[2]);

// Paramos el bucle para mas de 100 iteraciones 
if (N>100) {
printf("Numero maximo de Iteraciones alcanzado \n");
return 0;
}

// Evaluamos con el metodo de Newton-Raphson el valor de (x,y,z) 
// para la siguiente iteracion del bucle, calculando el producto 
// matricial Jminus*F
x[0] = x[0] - Jinv[0][0]*f[0] - Jinv[0][1]*f[1] - Jinv[0][2]*f[2];
x[1] = x[1] - Jinv[1][0]*f[0] - Jinv[1][1]*f[1] - Jinv[1][2]*f[2];
x[2] = x[2] - Jinv[2][0]*f[0] - Jinv[2][1]*f[1] - Jinv[2][2]*f[2];


} while ((fabs(f[0])>tol)||(fabs(f[1])>tol)||(fabs(f[2])>tol));
for(int i=0;i<3;i++){
 printf("f[%d] = %lf\n",i,pow(x[0]-C[i][0],2) + pow(x[1]-C[i][1],2) + pow(x[2]-C[i][2],2) - pow(R[i],2));
 printf("centro %d: %lf %lf %lf \n",i+1,C[i][0],C[i][1],C[i][2]);
}
fclose(input);

return 0;

}
