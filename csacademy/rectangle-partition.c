#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
typedef long long ll;
int cmp (const void *pa, const void *pb){
  ll*a=(ll*)pa;
  ll*b=(ll*)pb;
  return *a < *b ? -1:1;
}

ll m, n, kei;
ll width, height;
ll xx[100010];
ll yy[100010];
ll ww[100010];
ll hh[100010];

int main(){
    scanf("%lld %lld %lld %lld", &height, &width, &n, &m);
    for(int i=1; i<=n; i++)
        scanf("%lld", &yy[i]);
    for(int i=1; i<=m; i++)
        scanf("%lld", &xx[i]);
    yy[n+1] = height;
    xx[m+1] = width;
    ++n; ++m;
    qsort(yy, 1 + n, sizeof(ll),cmp);
    qsort(xx, 1 + m, sizeof(ll),cmp);
    for(ll i=0ll;i<(n);++i) {
        hh[i] = yy[i + 1] - yy[i];
    }
    for(ll i=0ll;i<(m);++i) {
        ww[i] = xx[i + 1] - xx[i];
    }
    qsort(hh, n,sizeof(ll),cmp);
    qsort(ww, m,sizeof(ll),cmp);
    ll xi = 0;
    ll yi = 0;
    ll result = 0;
    while (xi < m && yi < n) {
        ll w = ww[xi];
        ll h = hh[yi];
        if (w < 0 || h < 0) 
            break;
        if (w < h) {
            ++xi;
        }
        else if (w > h) {
            ++yi;
        }
        else {
            ll wr = 1; 
            ll hr = 1;
            while (ww[++xi] == w) ++wr;
            while (hh[++yi] == h) ++hr;
            result += wr*hr;
        }
    }
    printf("%lld\n", result);
    return 0;
}








