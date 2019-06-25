#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long gcd(long a, long b){
  if (b == 0)
    return a;
  else
    return gcd(b, a%b);
}
long lcm(long a, long b){
  return (a*b)/gcd(a,b);
}
int main(){
  int num, a, b, i;
  scanf("%d", &num);
  for(i=0;i<num;i++){
    scanf("%d %d", &a, &b);
    long ref=lcm(a-1, b-1);
    long n1=ref/(a-1);
    long n2=ref/(b-1);
    long c=1+ref-((n1-1)*(n2-1))/2;
    printf("%ld\n", c);
  }
  return 0;
}
