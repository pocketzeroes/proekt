#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
ll d, t, v1, v2;

int main(){
  scanf("%lld %lld %lld %lld", &d, &t, &v1, &v2);
  ll vv = v1-v2;
  if(vv*t>=d){
    printf("%lld\n", (d+vv-1)/vv);
  }
  else{
    d-=vv*t;
    printf("%lld\n", ((d+v1-1)/v1)+t);
  }
  return 0;
}
