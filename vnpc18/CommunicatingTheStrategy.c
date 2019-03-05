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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
typedef long long ll;
ll inf = (ll)1 << 60;
ll mod = 1000000007;


ll modinverse(ll a, ll b){
  return 1<a ? b - modinverse(b%a,a)*b/a : 1;
}
void clean(ll*n){
  while(*n < mod)
    *n = *n + mod;
  *n = *n % mod;
}
int main(){
  ll n;
  scanf("%lld", &n);
  ll memo[n+1][n+1]; memset(memo, 0, sizeof(memo));
  puts("1 1 1"); fflush(stdout);
  ll t1, t2;
  scanf("%lld %lld", &t1, &t2);
  memo[1][1] = t2;
  vec ans=newVec();
  ans.ptr = pushback(ans.ptr, &ans.sz, t2);
  for(ll i=2; i<=n; i++){
    printf("1 1 %d\n", i);fflush(stdout);
    ll t1, t2;
    scanf("%lld %lld", &t1, &t2);
    ll val;
    if(t1 == 1) {
      val = t2 - memo[i-1][1];
      clean(&val);
    }
    else if(t1 == i) {
      val = t2 * modinverse(memo[i-1][i-1], mod);
      clean(&val);
    }
    else {
      val = (t2 - memo[i-1][t1]);
      clean(&val);
      val *= modinverse(memo[i-1][t1-1], mod);
      clean(&val);
    }
    for(int j = 1; j <= i; j++) {
      if(j == 1) {
        memo[i][j] = memo[i-1][j] + val;
        clean(&memo[i][j]);
      }
      else if(j == i) {
        memo[i][j] = memo[i-1][j-1] * val;
        clean(&memo[i][j]);
      }
      else {
        memo[i][j] = memo[i-1][j] + memo[i-1][j-1] * val;
        clean(&memo[i][j]);
      }
    }
    ans.ptr = pushback(ans.ptr, &ans.sz, val);
  }
  printf("2 ");fflush(stdout);
  for(int z=0;z<ans.sz;z++){int i = ans.ptr[z];
    printf("%d ", i);fflush(stdout);
  }
  puts("");fflush(stdout);
  return 0;
}
