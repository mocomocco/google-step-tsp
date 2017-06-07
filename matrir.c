#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double get_time()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec * 1e-6;
}


double time_memo(int n){
double* a = (double*)malloc(n * n * sizeof(double)); // Matrix A
  double* b = (double*)malloc(n * n * sizeof(double)); // Matrix B
  double* c = (double*)malloc(n * n * sizeof(double)); // Matrix C

  // Initialize the matrices to some values.
  int i, h,j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      a[i * n + j] = i * n + j; // A[i][j]
      b[i * n + j] = j * n + i; // B[i][j]
      c[i * n + j] = 0; // C[i][j]
    }
  }
  /* for(i=1;i<=n;i++){
  printf("a%d行め\n",i);
  for(h=1;h<=n;h++)
    scanf("%lf",&a[(i-1)*n+h-1]);
  }
 
 for(i=1;i<=n;i++){
  printf("b%d行め\n",i);
  for(h=1;h<=n;h++)
    scanf("%lf",&b[(i-1)*n+h-1]);
    }*/

  double begin = get_time();

  /**************************************/
   for(i=0;i<n;i++){
   for(h=0;h<n;h++){
     for(j=0;j<n;j++){
       c[i*n+h]+=a[i*n+j]*b[j*n+h];
     }
   }
   }
  /**************************************/

  double end = get_time();
  //  printf("time: %.6lf sec\n", end - begin);

  // Print C for debugging. Comment out the print before measuring the execution time.
  /*|||||||||||||||||*/ 
  /*   for(i=0;i<n;i++){
 for(h=0;h<n;h++){
   printf(" ");
   printf("%d",(int)a[i*n+h]) ;
 }
 if(i==n/2)printf(" * ");
else  printf("   ");
 for(h=0;h<n;h++){
   printf(" ");
   printf("%d",(int)b[i*n+h]) ;
     }
 if(i==n/2)printf(" = ");
else  printf("   ");
for(h=0;h<n;h++){
   printf(" ");
   printf("%d",(int)c[i*n+h]) ;
 }

 printf("\n");
 }*/
 /*||||||||||||||||||||||*/
  double sum = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      sum += c[i * n + j];
      // printf("c[%d][%d]=%lf\n", i, j, c[i * n + j]);
    }
  }
  // Print out the sum of all values in C.
  // This should be 450 for N=3, 3680 for N=4, and 18250 for N=5.
  //printf("sum: %.6lf\n", sum);

  free(a);
  free(b);
  free(c);
 return (end-begin);
}

int main(int argc, char** argv)
{ int i;
  double time;
  FILE* fp;
  fp=fopen("time.txt","w");
  if (argc != 2) {
    printf("usage: %s N\n", argv[0]);
    return -1;
  }

  int n = atoi(argv[1]);
  for(i=0;i<n;i++){
  time= time_memo(i);
  fprintf(fp," %.6lf\n", time);
  }
  fclose(fp);
  return 0;

}
