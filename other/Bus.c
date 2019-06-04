#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
  int Z;
  scanf("%d", &Z);
  while(Z--){
    int k;
    scanf("%d", &k);
    long long n = 0;
    while(k--)
      n = (n + 1) * 2;
    n /= 2;
    printf("%lld\n", n);
  }
  return 0;
}
