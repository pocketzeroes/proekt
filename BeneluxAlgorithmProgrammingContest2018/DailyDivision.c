#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}

enum{ maxn     =(int) 1e5 + 350};
enum{ sqrtmaxn = 350};
int N, nbins, binsize;
ll A[maxn];
ll BS[sqrtmaxn];
ll CS[sqrtmaxn][sqrtmaxn];

ll F(int idx){
    int q = idx / binsize, r = idx % binsize;
    return BS[nbins] - A[idx] - 2LL * (BS[q] + CS[q][r]);
}
ll SF(int idx){
    ll ret = abs(F(idx));
    if (A[idx] % 2LL == 0LL)
        return ret;
    if (ret == 0LL)
        return 1LL;
    return ret - 1LL;
}
int hut_pos(){
    int lo = -1,
        hi = N - 1;
    while (hi - lo > 1){
        int mi = (lo + hi) / 2;
        if (F(mi) >= 0LL)
            lo=mi;
        else
            hi=mi;
    }
    if (lo < 0)
        return 0;
    if (hi >= N)
        hi = lo--;
    ll flo = SF(lo),
       fhi = SF(hi);
    ll bestVal = min(flo, fhi);
    int best = flo <= fhi ? lo : hi;
    if (lo > 0){
        ll alt = SF(lo - 1);
        if(alt <= bestVal)
            bestVal = alt, best = lo - 1;
    }
    return best;
}
int main(){
    int Q;
    scanf("%d %d", &N, &Q);
    for(int i = (0); i != (N); ++i)
        scanf("%lld", &A[i]);
    binsize = sqrt(N);
    nbins = N / binsize;
    if (N % binsize != 0){
        N += binsize - (N % binsize);
        nbins++;
    }
    for(int i = (0); i != (nbins); ++i)
        CS[i][0] = 0LL;
    for(int i = (0); i != (nbins); ++i)
        for(int j = (0); j != (binsize); ++j)
            CS[i][j + 1] = CS[i][j] + A[i * binsize + j];
    for(int i = (0); i != (nbins); ++i)
        BS[i + 1] = BS[i] + CS[i][binsize];
    int ret[Q];
    for(int i=0; i != Q; ++i){
        int p, q, v;
        scanf("%d%d", &p, &v);
        q = p / binsize;
        ll inc = v - A[p];
        for (int r = p % binsize; ++r < binsize; )
            CS[q][r] += inc;
        for (int r = q; ++r <= nbins; )
            BS[r] += inc;
        A[p] = v;
        ret[i] = hut_pos();
    }
    for(int i=0; i!=Q; ++i)
        printf("%d\n", ret[i]);
    return 0;
}
