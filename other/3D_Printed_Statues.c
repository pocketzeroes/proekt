#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef unsigned long long ull;

int main(){
  ull N;
  scanf("%llu", &N);
  ull cur = 1, t = 0;
  while(cur < N){
    cur *= 2;
    ++t;
  }
  printf("%llu\n", t + 1);
  return 0;
}
