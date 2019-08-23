#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef long long ll;
int n, k;
ll  a[1000005];
int num[105];

void solve(){
  scanf("%d %d", &n, &k);
  memset(num, 0, sizeof(num));
  ll sum = 0, half = 0;
  for(int i = (1); i <= (n); ++i){
    scanf("%lld", &a[i]);
    num[a[i] % k]++;
    sum += a[i];
  }
  vec V=newVec();
  for(int i = 0; i < (k); ++i){
    if(num[i] & 1)
      V.ptr=pushback(V.ptr, &V.sz, i);
    half += (num[i] / 2) * 1ll * i;
  }
  sum %= k;
  half %= k;
  if(sum == 0 || V.sz == 0 || V.sz > 2)
    puts( "DRAW" );
  else if(V.sz == 1){
    if(half == 0)
      puts( "SECOND" );
    else if((half + V.ptr[0]) % k == 0)
      puts( "FIRST" );
    else 
      puts( "DRAW" );
  }
  else{
    if((half + V.ptr[0]) % k == 0 || (half + V.ptr[1]) % k == 0)
      puts( "FIRST" );
    else
      puts( "DRAW" );
  }
}
int main(){
  int ntest;
  scanf("%d", &ntest);
  while(ntest--)
    solve();
  return 0;
}
