#include<stdio.h>
int main(){
  long long N, b;
  scanf("%lld %lld", &N, &b);
  printf("%s\n", ((2LL<<b)-1 >= N) ? "yes" : "no");
  return 0;
}
