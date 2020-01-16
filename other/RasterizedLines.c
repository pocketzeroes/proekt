#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
#define pbl(zpv, zvv) zpv.ptr = pushbackL(zpv.ptr, &zpv.sz, zvv)
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
typedef struct{
  ll first;
  int second;
}pli;
pli newpli(ll a, int b){
  return(pli){a,b};
}
#define pbp(zpv, zvv) zpv->ptr = pushbackP(zpv->ptr, &zpv->sz, zvv)
pli*pushbackP(pli*array, int *size, pli value){
  pli*output = resizeArray(array, pli, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pli*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
//////////////////////////
enum{ SIZE = 10000010};
int bs[SIZE+1];
vecl primes;

void sieve(){
    memset(bs, 0x11, sizeof(bs));
    bs[0] = bs[1] = 0;
    for(ll i=2; i<=SIZE; i++){
        if(bs[i]){
            for(ll j=i*i; j<=SIZE; j+=i)
                bs[j] = 0;
            pbl(primes, i);
        }
    }
}
ll phi(ll n){
    ll ans = n, pn = n;
    unsigned s = primes.sz;
    for(unsigned i=0; i < s && primes.ptr[i]*primes.ptr[i]<=pn; ++i){
        if(pn % primes.ptr[i] == 0){
            ans -= ans / primes.ptr[i];
            while(pn % primes.ptr[i] == 0)
                pn /= primes.ptr[i];
        }
    }
    if(pn > 1)
        ans -= ans / pn;
    return ans;
}
void factorize(ll n, vecp*f){
    for(unsigned i = 0; i<primes.sz && primes.ptr[i]*primes.ptr[i] <= n; ++i){
        if(n % primes.ptr[i] == 0){
            int p = 0;
            while(n%primes.ptr[i] == 0){
                n /= primes.ptr[i];
                ++p;
            }
            pbp(f, newpli(primes.ptr[i], p));
        }
    }
    if(n > 1)
        pbp(f, newpli(n, 1));
}
vecl divisors(vecp*f){
    vecl res=newVecL();
    pbl(res,1);
    for(unsigned i = 0; i<f->sz; ++i){
        int o = res.sz;
        for(int j=0; j<f->ptr[i].second*o; ++j){
            pbl(res, res.ptr[res.sz-o]*f->ptr[i].first);
        }
    }
    return res;
}
int main(){
    sieve();
    int T;
    scanf("%d", &T);
    while (T--){
        ll N;
        scanf("%lld", &N);
        ll sq = (ll)(sqrt(N)) + 10, ans = 0LL;
        vecp f = newVecP();//of pli
        factorize(N, &f);
        vecl div = divisors(&f);
        for(int i=0; i<div.sz; ++i)
            ans += phi(div.ptr[i] + 1);
        printf("%lld\n", ans);
    }
    return 0;
}
