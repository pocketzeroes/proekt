#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef unsigned int u32;
typedef long long   ll;
typedef long double ld;


void swap(ll*nums, int i, int j){
   ll t    = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}


enum{ MAXN = (1048576<<1) };
const ll P = (479 << 21) + 1LL;
const ll G = 3;
ll wn[22];
ll s[MAXN], d1[MAXN], d2[MAXN], y[MAXN];


ll mod_mul(ll a, ll b, ll mod){
    return (a*b - (ll)(a/(ld)mod*b+1e-3)*mod+mod)%mod;
}
ll mod_pow(ll n, ll e, ll m) {
    ll x = 1;
    for (n = n >= m ? n%m : n; e; e >>= 1){
        if (e&1)
            x = mod_mul(x, n, m);
        n = mod_mul(n, n, m);
    }
    return x;
}
void TOOL_NTT(){
    for (int i = 0; i < 22; i++)
        wn[i] = mod_pow(G, (P-1) / (1<<i), P);
}
int NumberOfBitsNeeded(int PowerOfTwo){
    for (int i = 0;; ++i) {
        if (PowerOfTwo & (1 << i)) {
            return i;
        }
    }
}
inline u32 FastReverseBits(u32 a, int NumBits){
    a = ( ( a & 0x55555555U ) << 1 ) | ( ( a & 0xAAAAAAAAU ) >> 1 ) ;
    a = ( ( a & 0x33333333U ) << 2 ) | ( ( a & 0xCCCCCCCCU ) >> 2 ) ;
    a = ( ( a & 0x0F0F0F0FU ) << 4 ) | ( ( a & 0xF0F0F0F0U ) >> 4 ) ;
    a = ( ( a & 0x00FF00FFU ) << 8 ) | ( ( a & 0xFF00FF00U ) >> 8 ) ;
    a = ( ( a & 0x0000FFFFU ) << 16 ) | ( ( a & 0xFFFF0000U ) >> 16 ) ;
    return a >> (32 - NumBits);
}
void NTT(int on, ll *In, ll *Out, int n){
    int NumBits = NumberOfBitsNeeded(n);
    for (int i = 0; i < n; ++i)
        Out[FastReverseBits(i, NumBits)] = In[i];
    for(int h = 2, id = 1; h <= n; h <<= 1, id++) {
        for(int j = 0; j < n; j += h) {
            ll w = 1, u, t;
            int block = h/2, blockEnd = j + h/2;
            for(int k = j; k < blockEnd; k++) {
                u = Out[k], t = mod_mul(w, Out[k+block], P);
                Out[k] = u + t;
                Out[k + block] = u - t + P;
                if (Out[k] >= P)        Out[k] -= P;
                if (Out[k+block] >= P)  Out[k+block] -= P;
                w = mod_mul(w, wn[id], P);
            }
        }
    }
    if (on == 1) {
        for (int i = 1; i < n/2; i++)
            swap(Out, i, n-i);
        ll invn = mod_pow(n, P-2, P);
        for (int i = 0; i < n; i++)
            Out[i] = mod_mul(Out[i], invn, P);
    }
}
void convolution(ll *a, ll *b, int n, ll *c){
    NTT(0, a, d1, n);
    s[0] = b[0];
    for (int i = 1; i < n; ++i)
        s[i] = b[n-i];
    NTT(0, s, d2, n);
    for (int i = 0; i < n; i++)
        s[i] = mod_mul(d1[i], d2[i], P);
    NTT(1, s, c, n);
}


ll a[MAXN], b[MAXN], c[MAXN];
ll ret[1048576];
ll pr[1048576] = {};
int main() {
    TOOL_NTT();
    int m;
    const int N = 500000;
    for (m = 1; m < (N<<1); m <<= 1);
    for (int i = 1; i <= N; i++) {
    	for (int j = i; j <= N; j += i)
    		pr[j]++;
    }	
    memset(a, 0, sizeof(a[0]) * m);
    memset(b, 0, sizeof(b[0]) * m);
    for (int i = 1; i <= N; i++) {
        a[i] = pr[i];
        b[m-i] = pr[i];
    }	
    convolution(a, b, m, c);
    for (int i = 1; i <= N; i++)
        ret[i] = c[i];
    int testcase, L, R;
    while (scanf("%d", &testcase) == 1) {
        while (testcase--)	 {
            scanf("%d %d", &L, &R);
            assert(L <= R);
            assert(L >= 1 && R <= 500000);
            int mxA = L;
            for (int i = L; i <= R; i++) {
                if (ret[i] > ret[mxA])
                    mxA = i;
            }
            printf("%d %lld\n", mxA, ret[mxA]);
        }
    }
    return 0;
}
