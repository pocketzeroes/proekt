#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;


enum{ maxn = 21};
int num;
int test;
int n, a[maxn];
ll f[maxn][maxn][10][2];

ll go(int id, int so, int du, int behon){
    if(id < 0){
        if(du == 0) return so;
        else return 0;
    }
#define ret f[id][so][du][behon]
    if(ret != -1)
        return ret;
    ret = 0;
    int l = 0,
        r = 9;
    if(!behon)
        r = a[id];
    for(int i=l; i<=r; i++){
        int dnew = (du * 10 + i) % 8;
        int sonew = so;
        if(i == 8 || i == 6)
            sonew++;
        ret += go(id - 1, sonew, dnew, behon | (i < a[id]));
    }
    return ret;
    #undef ret
}
ll dem(ll X){
    ll res = 0;
    while(X){
        ll d = X % 10;
        res += (d == 6 || d == 8);
        X /= 10;
    }
    return res;
}
void sol(){
    memset(f, -1, sizeof(f));
    memset(a, 0, sizeof(a));
    ll X, temp;
    scanf("%lld", &X);
    temp = X - 1;
    n = 0;
    while(temp){
        a[n++] = temp % 10;
        temp /= 10;
    }
    printf("%lld\n", go(19, 0, 0, 0) + dem(X));
}
int main(){
    scanf("%d", &test);
    for(int itest = 0; itest < test; ++itest)
        sol();
    return 0;
}
