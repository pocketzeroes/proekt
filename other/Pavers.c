#define DO_LONG
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#ifdef DO_LONG
typedef unsigned long CNT_TYPE;
#define MAX_SIZE  13
#else
#ifdef DO_QUAD
#ifdef LINUX
typedef unsigned long long CNT_TYPE;
#else
typedef unsigned __int64 CNT_TYPE;
#endif
#define MAX_SIZE  25
#else
typedef double CNT_TYPE;
#define MAX_SIZE  400
#endif
#endif
CNT_TYPE F[MAX_SIZE+1], F1[MAX_SIZE+1], F2[MAX_SIZE+1], F3[MAX_SIZE+1];
CNT_TYPE G[MAX_SIZE+1], G1[MAX_SIZE+1], G2[MAX_SIZE+1], G3[MAX_SIZE+1];

int maxindex = 0;

int comp_tiles()
{
  int n;
  CNT_TYPE test, test1;
  F[0] = 1; F[1] = 2; F[2] = 11;
  F1[0] = 0; F1[1] = 2; F1[2] = 16;
  F2[0] = 0; F2[1] = 1; F2[2] = 8;
  F3[0] = 0; F3[1] = 0; F3[2] = 4;
  G[0] = 0; G[1] = 0; G[2] = 2;
  G1[0] = G1[1] = 0; G1[2] = 1;
  G2[0] = G2[1] = 0; G2[2] = 1;
  G3[0] = G3[1] = 0; G3[2] = 1;
  for(n = 2; n <= MAX_SIZE-1 ; n++) {
    F[n+1] = 2*F[n] + 7*F[n-1] + 4*G[n];
    F1[n+1] = 2*F1[n] + 2*F[n] + 7*F1[n-1] + 8*F[n-1] + 4*G1[n]+2*G[n];
    F2[n+1] = 2*F2[n] + F[n] + 7*F2[n-1] + 4*F[n-1] + 4*G2[n]+2*G[n];
    F3[n+1] = 2*F3[n] + 7*F3[n-1] + 4*F[n-1] + 4*G3[n]+2*G[n];
    test = 2.0*((double)(n+1))*F[n+1];
    test1 = F1[n+1] + 2.0*F2[n+1] + 3.0*F3[n+1];
    if(fabs(test - test1) > .0000001*test) {
      fprintf(stderr, "mismatch %d: %g != %g\n", n+1, test, test1);
    }
    G[n+1] = 2*F[n-1] + G[n];
    G1[n+1] = 2*F1[n-1] + F[n-1] + G1[n];
    G2[n+1] = 2*F2[n-1] + F[n-1] + G2[n] + G[n];
    G3[n+1] = 2*F3[n-1] + F[n-1] + G3[n];
  }
  return 0;
}

char inbuf[256];
int main()
{
  int nprob=1, curprob=1, index, n;
  comp_tiles();
  for(curprob = 1; curprob <= nprob ; curprob++)
  {
    scanf("%d", &n);
    if(n == 1){
      printf("2 2 1 0\n");
    }
    else if((n < 2) || (n > MAX_SIZE)) {
      fprintf(stderr, "array width %d not in range 2 .. %d problem %d\n", n, MAX_SIZE, curprob);
      return -6;
    }
    else{
#ifdef DO_LONG
      printf("%lu %lu %lu %lu\n", F[n], F1[n], F2[n], F3[n]);
#else
#ifdef DO_QUAD
      printf("%llu %llu %llu %llu\n", F[n], F1[n], F2[n], F3[n]);
#else
      printf("%g %g %g %g %.6lf\n", F[n], F1[n], F2[n], F3[n], F1[n]/(F1[n]+F2[n]+F3[n]));
#endif
#endif
    }
  }
  return 0;
}
