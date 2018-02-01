#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define swap(x, y) do { int tSWAP = x; x = y; y = tSWAP; } while (0)

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
//////////////////////////////
typedef long long ll;
ll MOD;
enum{ N = 111};
ll  a    [N][N], 
    coeff[N][N];
int in   [N][N];

bool isPrime(int n){
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0)
            return false;
    return n > 1;
}
ll Pow(ll a, ll b){
    ll x = 1, 
       y = a;
    while (b) {
        if(b % 2){
            x *= y;
            x %= MOD;
        }
        y *= y;
        y %= MOD;
        b /= 2;
    }
    return x;
}
ll Inv(ll a){
    return Pow(a, MOD - 2);
}
vec factor(int n){
    vec ans = newVec();
    for(int i = 2; i * i <= n; ++i)
        if(n % i == 0){
            ans.ptr = pushback(ans.ptr, &ans.sz, i);
            while (n % i == 0)
                n /= i;
        }
    return ans;
}
bool isGenerator(int g, vec*ps){
    for(int z=0;z<ps->sz;z++){int p = ps->ptr[z];
        if(Pow(g, (MOD - 1) / p) == 1)
            return false;
    }
    return true;
}
ll det(int n){
    ll ans = 1;
    for (int i = 0; i < n; ++i) {
        int pos = i;
        for (int j = i; j < n; ++j)
            if (a[j][i]) {
                pos = j;
                break;
            }
        if (pos != i) {
            ans = MOD - ans;
            for (int j = 0; j < n; ++j)
                swap(a[pos][j], a[i][j]);
        }
        ll inv = Inv(a[i][i]);
        ans *= a[i][i];
        ans %= MOD;
        for (int j = i; j < n; ++j) {
            a[i][j] *= inv;
            a[i][j] %= MOD;
            a[i][j] = MOD - a[i][j];
        }
        for (int j = i + 1; j < n; ++j)
            for (int k = i + 1; k < n; ++k){
                a[j][k] += a[i][k] * a[j][i];
                a[j][k] %= MOD;
            }
    }
    return ans;
}
int myRand(){
#if RAND_MAX < 100000
    return (rand() << 15) | rand();
#else
    return rand();
#endif
}
int main(){
    srand(57);
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%d", &in[i][j]);
    MOD = (int)(1e9) / k * k + 1;
    while (!isPrime(MOD))
        MOD -= k;
    int g = 1;
    vec ps = factor(MOD - 1);
    while (!isGenerator(g, &ps))
        ++g;
    ll root = Pow(g, (MOD - 1) / k);
    int ITS = 3;
    while (ITS--) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                coeff[i][j] = myRand() % MOD;
        ll sum = 0;
        for (int d = 0; d < k; ++d) {
            ll rootPow = Pow(root, d);
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j) {
                    if (in[i][j] == -1) {
                        a[i][j] = 0;
                        continue;
                    }
                    a[i][j] = Pow(rootPow, in[i][j]) * coeff[i][j] % MOD;
                }
            sum += det(n);
        }
        if (sum % MOD) {
            puts("Yes");
            return 0;
        }
    }
    puts("No");
}

