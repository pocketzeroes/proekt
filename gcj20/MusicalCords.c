#pragma GCC optimize "-O3"
#define __USE_MINGW_ANSI_STDIO 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define back(_v) _v.ptr[_v.sz-1]
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
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
////////////
typedef long long   ll;
typedef long double ld;

int main(){
  const ll MAX = (ll)360*(ll)1e9;
  const ld q = M_PI / MAX;
  int tt;
  scanf("%d", &tt);
  for(int qq=1; qq<=tt; qq++){
    printf("Case #%d: ", qq);
    int n, r, k;
    scanf("%d %d %d", &n, &r, &k);
    ll d[2*n];
    ll l[2*n];
    for(int i=0; i<n; i++){
      scanf("%lld %lld", &d[i], &l[i]);
      d[i + n] = d[i] + MAX;
      l[i + n] = l[i];
    }
    ld ans = 0;
    void Test(int i, int j){
      ll diff = llabs(d[i] - d[j]);
      if(diff >= MAX)
         diff -= MAX;
      ld dd = (ld)diff*q;
      ans = fmaxl(ans, sinl(dd)*2*r+l[i]+l[j]);
    };
    vec st=newVec();
    int beg = 0;
    int i = 0;
    int j = 0;
    while(j < n){
      if(i < 2 * n && d[i] <= d[j] + MAX / 2){
        while(beg < (int) st.sz && l[back(st)] <= l[i]){
          st.sz--;
        }
        pb(st, i);
        ++i;
      }
      else{
        while(beg < (int) st.sz && st.ptr[beg] <= j)
          ++beg;
        for(int t = beg; t < (int) st.sz; t++)
          Test(j, st.ptr[t]);
        ++j;
      }
    }
    printf("%.17Lf\n", ans);
  }
  return 0;
}
