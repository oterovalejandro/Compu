#include<stdio.h>
#include<math.h>

// Escritura de matrices en fichero de salida
void write(FILE * out, int N, double A[][N]){
int i,j;
 for(i=0;i<N;i++) {
  for(j=0;j<N;j++) {
     fprintf(out,"%9.5lf  ",A[i][j]);
  }
  fprintf(out,"\n");
 }
}

// Multiplicación matricial de dos matrices NxN
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

// Copia una matriz sobre otra
void copy(int N, double A[][N], double B[][N]) {
int i,j;
for(i=0;i<N;i++) {
  for(j=0;j<N;j++) {
    A[i][j] = B[i][j];
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

int i, j ,n;

// Solucion escrita en fichero auxiliar output.dat
FILE * output;
output = fopen("output.dat","w");

printf("Introduzca la dimensión de la matriz: \n");
scanf("%d",&n); 

double A[n][n];
double X[n][n];
double B[n][n];
double L[n][n];
double U[n][n];
double LtimesU[n][n];
int P[n];
double par;
int sing = 0;

double b[n];
double x[n];
double inv[n][n];
double determ=1.0;
double Af[n][n];

// se genera la matriz A
for(i=0;i<n;i++){
	for(j=0;j<n;j++){
		A[i][j] = 0;
	}
}
for(i=0;i<n;i++){
	int k = 0;
	for(j=i;j<n;j++){
		A[i][j] = 4.0/pow(2,k);
		A[j][i] = A[i][j];
		k++;
		if(k>2) break;
	}
}
// se genera la matriz X0
for(i=0;i<n;i++){
	for(j=0;j<n;j++){
		X[i][j] = 0.0;
	}
	X[i][i] = 1.0;
}

fprintf(output,"Matriz A: \n");
write(output,n,A);

int p = 0;
do{
// Descomposicion LU
LU_decomp(n,X,L,U,P,&par,&sing);

matrixmult(n,L,U,LtimesU);

// Calculo de determinante 
for(i=0;i<n;i++) {
 determ = determ*U[i][i];
}
determ = determ*par;

// Calculo de matriz inversa en array inv
for(j=0;j<n;j++) { // Bucle en columnas de X^-1
 for(i=0;i<n;i++) {  // Calculo de e_j
 if(i==j) b[i] = 1.0;
 else b[i] = 0.0;
 }
 LU_solve(n,L,U,P,b,x);  // Resolucion de sistema
 for(i=0;i<n;i++) {   // Construccion de inversa con vector x 
 inv[i][j] = x[i];
 }
} // Fin de bucle en columnas de X^-1
matrixmult(n,inv,A,B);

for(j=0;j<n;j++) {
 for(i=0;i<n;i++) { 
	 X[i][j] = (B[i][j] + X[i][j])/2;
 }
}
p++;
} while(p<10);

// Comprobacion
matrixmult(n,X,X,Af);
fprintf(output,"Matriz X: \n");
write(output,n,X);
fprintf(output,"Matriz X·X = A: \n");
write(output,n,Af);

fclose(output);

}
