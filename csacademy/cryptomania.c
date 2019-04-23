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
#define swap(a,b) do{ typeof(a) tmp; tmp = a; a = b; b = tmp; }while(0)
typedef long long ll;
typedef long double ld;
typedef unsigned int uint;
typedef unsigned long long   ull;

long double PI = 3.14159265358979323846;
long double eps = 1e-5;
ll mod = 1000 * 1000 * 1000 + 7;
ll A, B, C;


ll**newmat(int x, int y){
    ll**rv = calloc(x, sizeof(ll*));
    for(int i=0;i<x;i++)
        rv[i] = calloc(y, sizeof(ll));
    return rv;
}
ll power(ll a, ll n, ll p){
    ll res = 1;
    while (n) {
        if (n & 1) {
            res = (res * a) % p;
        }
        a = (a * a) % p;
        n /= 2;
    }
    return res;
}
ll inv(ll a, ll p){
    return power(a, p - 2, p);
}
ll*solveG(ll**m, int msz, ll p){
    int n = msz;
    for(int i=0; i<n; ++i){
        int r = i;
        while(m[r][i] == 0)
            ++r;
        for(int j = 0; j <= n; ++j)
            swap(m[i][j], m[r][j]);
        r = inv(m[i][i], p);
        for (int j = 0; j <= n; ++j)
            m[i][j] = (m[i][j] * r) % p;
        for (int l = 0; l < n; ++l){
            if (l == i)
                continue;
            r = m[l][i];
            for (int j = 0; j <= n; ++j)
                m[l][j] = (((m[l][j] - r * m[i][j]) % p) + p) % p;
        }
    }
    ll*res = calloc(n, sizeof(ll));
    for(int i=0; i<n; ++i)
        res[i] = m[i][n];
    return res;

}
void solve1(int n, ll p, ll*a, ll*b, vec*ids){
    A = B = 0;
    C = b[ids->ptr[0]];
    return;
}
void solve2(int n, ll p, ll*a, ll*b, vec*ids){
    A = 0;
    ll**m = newmat(2, 3);
    for(int i = 0; i < ids->sz; ++i){
        m[i][0] = a[ids->ptr[i]];
        m[i][1] = 1;
        m[i][2] = b[ids->ptr[i]];
    }
    ll*res = solveG(m, 2, p);
    B = res[0], 
    C = res[1];
    return;
}
void solve3(int n, ll p, ll*a, ll*b, vec*ids){
    ll**m = newmat(3, 4);
    for(int i = 0; i < ids->sz; ++i){
        m[i][0] = (a[ids->ptr[i]] * a[ids->ptr[i]]) % p;
        m[i][1] = a[ids->ptr[i]];
        m[i][2] = 1;
        m[i][3] = b[ids->ptr[i]];
    }
    ll*res = solveG(m, 3, p);
    A = res[0], 
    B = res[1], 
    C = res[2];
    return;
}
int main(){
    int n;
    ll p;
    scanf("%d %lld", &n, &p);
    ll a[n];
    ll b[n];
    for(int i=0; i<n; ++i)
        scanf("%lld", &a[i]);
    for(int i=0; i<n; ++i)
        scanf("%lld", &b[i]);
    vec ids = newVec();
    for(int i=0; i<n; ++i){
        bool ok = 1;
        for(int j=0; j<ids.sz; ++j){
            if(a[i] == a[ids.ptr[j]]){
                ok = 0;
                break;
            }
        }
        if(ok){
            ids.ptr = pushback(ids.ptr, &ids.sz, i);
            if(ids.sz == 3)
                break;
        }
    }
    if(ids.sz == 1)
        solve1(n, p, a, b, &ids);
    if(ids.sz == 2)
        solve2(n, p, a, b, &ids);
    if(ids.sz > 2)
        solve3(n, p, a, b, &ids);
    bool ok = 1;
    for (int i = 0; i < n; ++i){
        if ((a[i] * a[i] * A + a[i] * B + C) % p != b[i]){
            ok = 0;
            break;
        }
    }
    if(ok)
        printf("%lld %lld %lld\n", A, B, C);
    else
        puts("impossible");
    return 0;
}
