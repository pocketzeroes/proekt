#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll*pushback(ll*array, int*size, ll value){
  ll*output = resizeArray(array, ll, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	ll* ptr;
	int sz;
}vec;
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

char buff[100000];
int main(){
  scanf("%s", &buff);
  int n = strlen(buff);
  ll val = 0;
  for(int i=0; i<n; i++)
    if(buff[i] == '0')
      val += 1LL << i;
  if(val == 0)
    return puts("0")*0;
  char seen[1LL<<n]; memset(seen, 0, sizeof(seen));
  seen[val] = 1 ;
  vec q = newVec();
  q.ptr = pushback(q.ptr, &q.sz, val);
  ll qg = 0;
  ll mask = (1LL << n) - 1;
  for(int d=1; ; d++){
    int hi = q.sz;
    for(int qg=0; qg<hi; qg++){
      val = q.ptr[qg];
      ll mod = (1LL << d) - 1;
      for(int s=0; s<=n; s++){
        ll val2 = mask & (val ^ (mod << s));
        if(seen[val2] == 0){
          seen[val2] = d + 1;
          if(val2 == 0){
            printf("%d\n", d);
            exit(0);
          }
          q.ptr = pushback(q.ptr, &q.sz, val2);
        }
      }
    }
  }
  puts("No solution");
}
