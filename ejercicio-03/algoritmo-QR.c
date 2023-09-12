#include<stdio.h>
#include<math.h>

void write(FILE * out, int N, double A[][N]){
int i,j;
 for(i=0;i<N;i++) {
  for(j=0;j<N;j++) {
     fprintf(out,"%13.8lf  ",A[i][j]);
  }
  fprintf(out,"\n");
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

void matrixcopy(int N, double A[][N], double B[][N]) {
int i,j;
for(i=0;i<N;i++) {
  for(j=0;j<N;j++) {
    B[i][j] = A[i][j];
  }
}
}

void traspuesta(int N, double A[][N], double B[][N]) {
int i,j;
for(i=0;i<N;i++) {
  for(j=0;j<N;j++) {
    B[i][j] = A[j][i];
  }
}
}

double norm(int N, double v[]){
int k;
double norma = 0.0;
 for(k=0;k<N;k++) {
  norma = norma + v[k]*v[k]; }
 norma = sqrt(norma);
 return norma;
}

void ident(int N, double A[][N]) {
 int i,j;
 for (i=0;i<N;i++) {
  for (j=0;j<N;j++) {
  if(i==j) A[i][j] = 1.0;
  else A[i][j] =  0.0; 
  }
 }
}

void householder(int N, double A[][N], double Q[][N], double R[][N]) {
 int i, j, i1, j1, k;
 double modulo, signo, norma;
 double v[N];
 double B[N][N], H[N][N];
 matrixcopy(N,A,R);   // Inicialmente R es igual a A 
 ident(N,Q);          // Inicialmente Q es la matriz identidad 
 for(j=0;j<N-1;j++) {
  modulo = 0.0;
  if(R[j][j]<0) signo=-1.0;
  else signo = 1.0;
  for(i=j;i<N;i++) {  // Calculo de ||x|| a partir de elementos R[i][j]
  modulo = modulo + R[i][j]*R[i][j]; }
  modulo = sqrt(modulo);
  for(i=0;i<N;i++) {  // Calculamos v  
  if(i<j) v[i] = 0.0;
  if(i==j) v[i] = R[j][j] - signo*modulo;
  if(i>j) v[i] = R[i][j]; }
  norma = norm(N,v);
  if(fabs(norma)>=1.0e-12) {  // Mejora para tratar matrices singulares  
  for (k=0;k<N;k++) {  // Normalizamos v
  v[k] = v[k]/norma; } 
  }
  ident(N,H);
  for(i1=0;i1<N;i1++) {   // Calculo de elementos de H  
   for(j1=0;j1<N;j1++) {
    H[i1][j1] = H[i1][j1] - 2.0*v[i1]*v[j1];
   }
  }
  matrixmult(N,H,R,B);  // Se multiplica H por R 
  matrixcopy(N,B,R);    // Se copia HR sobre R 
  matrixmult(N,Q,H,B);  // Se multiplica Q por H 
  matrixcopy(N,B,Q);    // Se copia QH sobre Q   
 } // fin de bucle en j

} // fin de funcion  

int main() {

int n,niter,s;
int i,j;

// Solucion escrita en fichero auxiliar output.dat
FILE * output;
output = fopen("output.dat","w");

printf("Introduzca la dimensión de la matriz: \n");
scanf("%d",&n); 

printf("Introduzca el número de iteraciones: \n");
scanf("%d",&niter); 

double A[n][n];
double R[n][n];
double Q[n][n];
double Qf[n][n];
double P[n][n];

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

fprintf(output,"Matriz A inicial: \n");
write(output,n,A);

ident(n,Qf);

for (s=1;s<=niter;s++) {
	householder(n,A,Q,R);

	matrixmult(n,Qf,Q,P);
	matrixcopy(n,P,Qf);

	matrixmult(n,R,Q,P);
	matrixcopy(n,P,A);
}

traspuesta(n,Qf,P);

fprintf(output,"Autovalores de A: \n");
for(i=0;i<n;i++){
	fprintf(output,"λ%d = %lf \n",i+1,A[i][i]);
}

fclose(output);

}
