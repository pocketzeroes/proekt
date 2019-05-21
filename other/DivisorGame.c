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
  ll*ptr;
  int sz;
}vecl;
vecl newVecL(){
  vecl rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

enum{ maxn = 100005};
enum{ MAXP = maxn*10};

int p[(MAXP>>6)+1];

void bitinit(){
    for (int i = 3; i * i <= MAXP; i += 2){
        if (!( p[i >> 6] & ( 1 << ( (i & 63) >> 1) ) )){
            int ii = i * i, i2 = i << 1;
            for (int j = ii; j <= MAXP; j += i2)
                p[j >> 6] |= ( 1 << ( (j & 63) >> 1 ) );
        }
    }
}
bool bitget(const int x){
    return x > 1 && (x == 2 || ( (x & 1) && !( p[x >> 6] & ( 1 << ( (x & 63) >> 1) ) ) ) );
}

int test;
vecl primes;
vecl V[maxn];
int mask = 64;

void add(ll*x, ll y){
   (*x) += y;
    if(*x >= 1000000007)
       *x -= 1000000007;
}
void sol(){
    ll A, B, n;
    scanf("%lld %lld", &A, &B);
    n = B - A;
    ll f[mask][2], 
       g[mask][2];
    for(int i = (0); i <= (n); ++i)
        V[i].sz=0;
    for(int i = 0; primes.ptr[i] * primes.ptr[i] <= B; i++){
        ll u = ((A - 1) / primes.ptr[i] + 1) * primes.ptr[i];
        for(ll j = u; j <= B; j += primes.ptr[i]){
            V[j-A].ptr=pushback(V[j-A].ptr, &V[j-A].sz, primes.ptr[i]);
        }
    }
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    f[0][0] = 1;
    for(int t = (0); t <= (n); ++t){
        for(int i = 0; i < (mask); ++i){
            for(int j = 0; j < (2); ++j){
                g[i][j] = f[i][j];
                f[i][j] = 0;
            }
        }
        ll x = A + t;
        int num = 0;
        for(int j = 0; j < (ll)V[t].sz; ++j){
            ll u = V[t].ptr[j];
            while(x % u == 0){
                x /= u;
                num++;
            }
        }
        if(x > 1)
            num++;
        for(int i = 0; i < (mask); ++i){
            for(int j = 0; j < (2); ++j){
                add(&f[i][j], g[i][j]);
                if(num != 1)
                    add(&f[i ^ num][1], g[i][j]);
                else
                    add(&f[i ^ num][j], g[i][j]);
            }
        }
    }
    ll res = f[1][0];
    add(&res, f[0][1]);
    printf("%lld\n", res);
}
int main(){
    bitinit();
    scanf("%d", &test);
    for(int i = (2); i <= (maxn * 10 - 1); ++i)
        if(bitget(i))
            primes.ptr = pushback(primes.ptr, &primes.sz, i);
    for(int itest = 0; itest < (test); ++itest)
        sol();
    return 0;
}
