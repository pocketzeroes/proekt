#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int N;
int S;
int  A[100000];
long P[100003];

void initPrefixSums(){
  int iPrefixSum = 0;
  for(int i=0; i<N; i++){
    P[i] = iPrefixSum;
    iPrefixSum += A[i];
  }
  P[N] = iPrefixSum;
  P[N+1] = LONG_MAX;
  P[N+2] = LONG_MAX;
}
void dvoniz(){
  initPrefixSums();
  int j = -1;
  for(int i=0; i<N; i++){
    while(P[j+1] - P[i] < 2*S)
      j += 2;
    int k = (i + j) / 2;
    while(P[k+1] - P[i] > S || P[j+1] - P[k+1] > S){
      j -= 2;
      k = (i + j) / 2;
    }
    printf("%d\n", j-i+1);
    j = fmax(j-1, i);
  }
}
int main(){
  scanf("%d %d", &N, &S);
  for(int i=0; i<N; i++)
    scanf("%d", &A[i]);
  dvoniz();
  return 0;
}
