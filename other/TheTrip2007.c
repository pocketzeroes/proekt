#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum{ N = 1200000};

int A[N];
int in[N];
int x;

int comp(const int* a, const int* b) {
   return (*a)-(*b);
}
int main(){
   int n, max, i, j;
   while (1 == scanf("%d", &n) && n) {
      if (x++) printf("\n");
      memset(A,0,sizeof(A));
      memset(in,0,sizeof(in));
      max = 0;
      for(i = 0; i < n; i++) {
          int d;
          scanf("%d", &d);
          A[d]++;
          in[i] = d;
          if(A[d]>max) max = A[d];
      }
      printf("%d\n", max);
      qsort(in, n, sizeof(in[0]), comp);
      for(i = 0; i < max; i++) {
          for(j = i; j < n; j+=max) {
              if(j>i) printf(" ");
              printf("%d", in[j]);
          }
          printf("\n");
      }
   }
   if (n) printf("missing end delimiter\n");
   return 0;
}
