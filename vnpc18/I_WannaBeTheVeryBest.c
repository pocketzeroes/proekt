#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXN = 1005};
int N, K, ord[MAXN];
unsigned int A[MAXN], D[MAXN], H[MAXN];
bool in[MAXN];


int lambda(const void *pa, const void*pb){
  int*i=(int*)pa;
  int*j=(int*)pb;
  return(A[*i] > A[*j])?-1:1;
}
int lambda2(const void *pa, const void*pb){
  int*i=(int*)pa;
  int*j=(int*)pb;
  return(D[*i] > D[*j])?-1:1;
}
int lambda3(const void *pa, const void*pb){
  int*i=(int*)pa;
  int*j=(int*)pb;
  return(H[*i] > H[*j])?-1:1;
}

int main(){
  scanf("%d %d", &N, &K);
  for(int i=0; i<N; i++)
    scanf("%u %u %u", &A[i], &D[i], &H[i]);
  for(int i=0; i<N; i++)
    ord[i] = i;
  qsort(ord, N, sizeof(int), lambda);
  for(int i=0; i<K; i++)
    in[ord[i]] = 1;
  qsort(ord, N, sizeof(int),lambda2);
  for(int i=0; i<K; i++)
    in[ord[i]] = 1;
  qsort(ord, N, sizeof(int), lambda3);
  for(int i=0; i<K;i++)
    in[ord[i]] = 1;
  int ans = 0;
  for(int i=0; i<N; i++)
    ans += in[i];
  printf("%d\n", ans);
  return 0;
}
