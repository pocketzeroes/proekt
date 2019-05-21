#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[100];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
typedef long long ll;


ll n, MOD;
const ll INF = 1000111000111000111LL;

typedef struct{
    ll x[55][55];
}Matrix;
Matrix a, p[66];

ll mul(ll a, ll b){
    if (b == 0)
        return 0;
    ll b1 = b / 1000000;
    ll b2 = b % 1000000;
    return (((a * b1) % MOD * 1000000) + (b2 * a)) % MOD;
}
Matrix matmul(Matrix*a, Matrix*b){
    Matrix res;
    memset(res.x, 0, sizeof res.x);
    for (ll i = (0), _b = (n); i <= _b; ++i){
        for (ll j = (0), _b = (n); j <= _b; ++j){
            for (ll k = (0), _b = (n); k <= _b; ++k){
                res.x[i][j] = (res.x[i][j] + mul(a->x[i][k], b->x[k][j])) % MOD;
            }
        }
    }
    return res;
}
char*s;
bool equals(ll a, ll b){
    while (a && b){
        if (s[a] != s[b])
            return 0;
        --a, --b;
    }
    return 1;
}
signed main(){
    ll ntest;
    scanf("%lld", &ntest);
    for(ll test=(1), _b = (ntest); test <= _b; ++test){
        ll k;
        scanf("%lld %lld", &k, &MOD);
        s = getstr();
        n = strlen(s);
        char ss[100]=" ";
        strcat(ss, s);
        strcat(ss, " ");
        free(s);
        s=strdup(ss);
        memset(a.x, 0, sizeof a.x);
        for (ll i = (0), _b = (n); i <= _b; ++i){
            for (ll c = ('a'), _b = ('z'); c <= _b; ++c){
                if (i == n)
                    a.x[n][i]++;
                else {
                    ll ok = 0;
                    for (ll j = (i+1), _b = (1); j >= _b; --j){
                        if(s[j] == c) {
                            if (equals(j-1, i)) {
                                a.x[j][i]++;
                                ok = 1;
                                break;
                            }
                        }
                    }
                    if (!ok)
                        a.x[0][i]++;
                }
            }
        }
        p[0] = a;
        for (ll i = (1), _b = (60); i <= _b; ++i)
            p[i] = matmul(&p[i-1], &p[i-1]);
        Matrix res;
        memset(res.x, 0, sizeof res.x);
        for (ll i = (0), _b = (n); i <= _b; ++i)
            res.x[i][i] = 1;
        for (ll bit = (0), _b = (60); bit <= _b; ++bit){
            if ((k >> bit) & 1)
                res = matmul(&res, &p[bit]);
        }
        printf("%lld\n", res.x[n][0]);
    }
    return 0;
}
