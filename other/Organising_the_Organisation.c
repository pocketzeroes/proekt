#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
const ll PRIME_MOD = 1000000000000037LL;
enum{ MAXN = 64};

ll  Q [MAXN][MAXN],
    L [MAXN][MAXN];
int cg[MAXN][MAXN];

ll mul(ll a, ll b, ll mod){
    if(b < 0)
        return -mul(a, -b, mod);
    ll ret = 0;
    for(;b!=0; b>>=1, a<<=1, a%=mod){
        if(b&1){
            ret += a;
            ret %= mod;
        }
    }
    return ret;
}
void exgcd(ll x, ll y, ll*g, ll*a, ll*b){
    if(y == 0)
       *g = x, *a = 1, *b = 0;
    else
        exgcd(y, x%y, g, b, a), *b -= (x/y) * (*a);
}
ll llabs(ll x){
    return x < 0 ? -x : x;
}
ll det(ll A[][MAXN], int n){
    ll sum = 1;
    ll g, a, b;
    for(int i = 0; i < n; i++){
        exgcd(A[i][i], PRIME_MOD, &g, &a, &b);
        ll inv = a;
        if (g < 0)
            inv = -inv;
        for (int j = i+1; j < n; j++){
            for (int k = n - 1; k >= i; k--){
                A[j][k] = A[j][k] - mul(mul(A[i][k], A[j][i], PRIME_MOD), inv, PRIME_MOD);
                A[j][k] = (A[j][k]%PRIME_MOD + PRIME_MOD) %PRIME_MOD;
            }
        }
        sum = mul(sum, A[i][i], PRIME_MOD);
        if (sum == 0)
            return 0;
    }
    if (sum < 0)
        sum = (sum % PRIME_MOD + PRIME_MOD) %PRIME_MOD;
    return llabs(sum);
}
int main() {
    int N, M, K;
    int x, y;
    while (scanf("%d %d %d", &N, &M, &K) == 3){
        memset(cg, 0, sizeof(cg));
        memset(Q, 0, sizeof(Q));
        memset(L, 0, sizeof(L));
        for (int i = 0; i < M; i++) {
            scanf("%d %d", &x, &y);
            x--, y--;
            cg[x][y] = cg[y][x] = 1;
        }
        for (int i = 0; i < N; i++) {
            int deg = 0;
            for (int j = 0; j < N; j++) {
                if (i != j && cg[i][j] == 0)
                    Q[i][j] = -1, deg++;
            }
            Q[i][i] = deg;
        }
        for (int i = 1; i < N; i++)
            for (int j = 1; j < N; j++)
                L[i-1][j-1] = Q[i][j];
        printf("%lld\n", det(L, N-1));
    }
    return 0;
}
