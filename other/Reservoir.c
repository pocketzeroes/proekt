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
int lower_bound(ll*a, int n, ll x){
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x <= a[mid]) 
            h = mid;
        else
            l = mid + 1;
    }
    return l;
}
//////////////////////////
enum{ maxn = 200005};

ll n, a[maxn], h[maxn], q, l[maxn], sum[maxn];
ll f[maxn];
vecl V;
int test;

void solve(){
    V.sz=0;
    scanf("%lld\n", &n);
    for(int i = (1); i <= (n); ++i)
        scanf("%lld\n", &a[i]);
    sum[0] = 0;
    for(int i = (1); i <= (n); ++i){
        scanf("%lld\n", &h[i]);
        sum[i] = sum[i - 1] + h[i];
    }
    a[0] = -1;
    h[0] = 1000000005;
    f[0] = 0;
    for(int i = (1); i <= (n); ++i){
        l[i] = i;
        while(h[l[i] - 1] <= h[i])
            l[i] = l[l[i] - 1];
        f[i] = f[l[i] - 1] + (h[i] * (a[i] - a[l[i] - 1])) - (sum[i] - sum[l[i] - 1]);
        V.ptr = pushbackL(V.ptr, &V.sz, f[i]);
    }
    scanf("%lld\n", &q);
    for(int iq = 0; iq < (q); ++iq){
        ll x;
        scanf("%lld\n", &x);
        int res = lower_bound(V.ptr, V.sz, x);
        printf("%d\n", res);
    }
}
int main(){
    int test;
    scanf("%d\n", &test);
    for(int itest = 0; itest < (test); ++itest)
        solve();
    return 0;
}
