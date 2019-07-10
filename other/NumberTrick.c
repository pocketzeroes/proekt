#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll*pushbackL(ll*array, int*size, ll value){
  ll*output = resizeArray(array, ll, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  ll*ptr;
  int sz;
}vecl;
vecl newVecL(){
  vecl rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

ll X;

vecl sols;

ll solve(ll y, ll A){
  ll nom=(A*X-10000LL)*y;
  ll denom=(100000LL - X);
  if (nom%denom!=0) 
    return -1;
  return nom/denom;
}
void gensols(){
  ll A=1;
  for(int _n=(8),i=0; i<_n; ++i){
    for(int _b=(9),y=(1); y<=_b; ++y){
      ll x=solve(y,A);
      if (x<A/10LL || x>=A) 
        continue;
      sols.ptr = pushbackL(sols.ptr, &sols.sz, A*y+x);
    }
    A*=10LL;
  }
}
void input(){
  char buf[100];
  gets(buf);
  ll r1=0;
  int j;
  for(j=0;((buf[j]!=0)&&(buf[j]!='.'));j++)
    r1=r1*10LL+(buf[j]-'0');
  if (buf[j]=='.'){
    j++;
    int u=0;
    for(;buf[j]!=0;j++){
      r1=r1*10LL+(buf[j]-'0'); 
      u++;
    }
    for(int _n=(4-u),m=0; m<_n; ++m) 
      r1=r1*10LL;
    X=r1;
  }
  else
    X=r1*10000LL;
}
int main(){
  input();
  if (X>=100000LL) {
    printf("No solution\n"); 
    return 0;
  }
  gensols();
  if(sols.sz==0)
    printf("No solution\n");
  else
    for(int _n=(sols.sz),i=0; i<_n; ++i)
      printf("%lld\n", sols.ptr[i]);
  return 0;
}
