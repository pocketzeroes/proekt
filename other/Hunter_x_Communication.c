#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

void swap(ll*nums, ll i, ll j) {
   ll t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(ll*nums,ll start,ll end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
}

typedef struct{
  ll*f;
  int sz;
}vecl;

inline int __lg(int __n){
    return sizeof(int) * __CHAR_BIT__  - 1 - __builtin_clz(__n);
}
#define __lg(x) (x == 0 ? -1 : __lg(x))

enum{ MOD = 998244353,
      G   = 3,
      LG  = 23,
      MX  = 1 << 21
    };
int n;
ll rt[LG+1];

ll pw(ll u, int p){
    ll ret = 1;
    for(int i=__lg(p); i>=0; i--){
        ret *= ret;
        ret %= MOD;
        if(p >> i & 1){
            ret *= u;
            ret %= MOD;
        }
    }
    return ret;
}
int reverse_bit(int u){
    int ans = 0;
    for(int i=0; i<21; i++){
        ans <<= 1;
        ans ^= (u >> i & 1);
    }
    return ans;
}
vecl bas, ini, row;

vecl newpoly(int sz){
    vecl rez;
    rez.f  = calloc(sz, sizeof(ll));
    rez.sz = sz;
    return rez;
}
vecl ntt(vecl p, bool inv){
    if(inv)
        reverse(p.f, 1, p.sz-1);
    vecl ans = newpoly(MX);
    for(int i=0; i<p.sz; i++)
        ans.f[reverse_bit(i)] = p.f[i];
    for(int len=1; len<MX; len += len){
        for(int i=0; i<MX; i+=2*len){
            ll r = rt[__lg(len) + 1];
            ll w = 1;
            for(int j=0; j<len; j++){
                ll u = ans.f[i + j],
                   v = ans.f[i + j + len];
                ans.f[i + j] = (u + w * v) % MOD;
                ans.f[i + j + len] = (u - w * v) % MOD;
                w *= r;
                w %= MOD;
            }
        }
    }
    if(inv){
        reverse(p.f, 1, p.sz-1);
        ll iv = pw(MX, MOD - 2);
        for(int z=0; z<ans.sz; z++){
            ans.f[z]*=iv;
            ans.f[z]%=MOD;
        }
    }
    return ans;
}
vecl opmul(vecl tva, vecl oth){
    vecl ans = newpoly(MX);
    for(int i=0; i<MX; i++)
        ans.f[i] = tva.f[i]*oth.f[i]%MOD;
    return ans;
}
vecl oppow(vecl u, int p){
    vecl ans = ini;
    for(int i = __lg(p); i >= 0; i--){
        ans = opmul(ans, ans);
        if(p >> i & 1)
            ans = opmul(ans, u);
    }
    return ans;
}
void init(){
    rt[LG] = pw(G, (MOD - 1) / (1 << LG));
    for(int i = LG - 1; i >= 0; i--)
        rt[i] = rt[i + 1] * rt[i + 1] % MOD;
    ini = newpoly(1);
    ini.f[0] = 1ll;
    ini.sz=1;
    bas=newpoly(10);
    row=newpoly(10);
    for(int i=0; i<10; i++){
        bas.f[i] = 1;
        row.f[i] = i!=0;
    }
    bas = ntt(bas, 0);
    ini = ntt(ini, 0);
    row = ntt(row, 0);
}
int main(){
    scanf("%d", &n);
    if(n == 1)
        return puts("10")*0;
    init();
    vecl ans = ntt(opmul(oppow(bas,n-1), row), 1);
    ll ret = 0;
    for(int z=0;z<ans.sz;z++){ll v = ans.f[z];
        ret += v*v;
        ret %= MOD;
    }
    printf("%lld\n", (ret + MOD) % MOD);
    return 0;
}
