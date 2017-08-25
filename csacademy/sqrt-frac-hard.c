#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#ifdef _WIN32
  #define inline static
#endif


inline double asmSqrt(double x) {
  __asm__ ("fsqrt" : "+t" (x));
  return x;
}

typedef long long   ll;
typedef long double ld;

ll inf  = (ll)1e18;
enum{ SQRT =(ll) 32000LL};
ll EPS  = (ll) 1e11;

typedef struct __ttt{
  ll cur;
  ll overs;
  ll k;
}thing;
thing newThing(ll a, ll b, ll c){
  thing rez;
  rez.cur  =a;
  rez.overs=b;
  rez.k    =c;  
  return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
thing*pushback(thing *array, int *size, thing value) {
  thing *output = resizeArray(array, thing, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct vec_T{
	thing*ptr;
	int sz;
}vect;
vect newVecT() {
	vect rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int cmpT(const void*pa, const void*pb){
  thing*ta=(thing*)pa;
  thing*tb=(thing*)pb;
  return (ta->cur < tb->cur)?-1:1;
}
int compT(thing ta, thing tb){
  return (ta.cur < tb.cur)?-1:1;
}

int lower_bound(thing*a, int n, thing x){
  int l = 0;
  int h = n;
  while(l < h){
    int mid = (l + h) / 2;
    if(compT(x, a[mid])<=0)
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}

///////////////////////////////////////////
long mult(long x, long k){
  __int128 a[2] = {x, k};
  __int128 b[4] = {0};
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      b[i + j] += a[i] * a[j];
    }
  }
  for (int i = 0; i < 2; i++) {
    b[i + 1] += b[i] / inf;
    b[i] %= inf;
  }
  return b[2];
}
inline bool test(ll y, ll x) {
  if (y < 1 || y > inf) {
    return false;
  }
  ll k = asmSqrt((ld) y);
  while (k * k > y) {
    k--;
  }
  while ((k + 1) * (k + 1) <= y) {
    k++;
  }
  long v1 = mult(x, k);
  long v2 = mult(x + 1, k);
  return (v1 < y && y <= v2);
}
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    ll x;
    scanf("%lld", &x);
    if (x == 0) {
      puts("1");
      continue;
    }
    ld z = x * 1e-18;
    ld aux = 1 - z * z;
    ll need = (ll) (aux * 1e18);
    need %= inf;
    vect e = newVecT();
    ll cur = 0;
    ll overs = 0;
    for(ll k = 1; k <= SQRT; k++) {
      cur += 2 * x;
      while (cur >= inf) {
        cur -= inf;
        overs++;
      }
      e.ptr = pushback(e.ptr, &e.sz ,newThing(cur, overs, k));
    }
    qsort(e.ptr, e.sz, sizeof(thing), cmpT);
    ll big_cur = cur;
    ll big_overs = overs;
    cur = overs = 0;
    ll ans = 0;
    for(ll big = 0; big <= SQRT && ans == 0; big++){
      ll get = need - cur;
      if (get < 0){
        get += inf;
      }
      int pos = lower_bound(e.ptr, e.sz, newThing(get, -1, -1));
      for (int j = pos - 4; j <= pos + 4; j++) {
        if (0 <= j && j < e.sz){
          ll value = e.ptr[j].cur;
          if (abs(value - get) < EPS) {
            ll k = big * SQRT + e.ptr[j].k;
            ll around = k * k + overs + e.ptr[j].overs + 1;
            for (ll y = around - 5; y <= around + 5; y++) {
              if (test(y, x)) {
                ans = y;
                break;
              }
            }
          }
        }
      }
      cur   += big_cur;
      overs += big_overs;
      while (cur >= inf) {
        cur -= inf;
        overs++;
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}




























