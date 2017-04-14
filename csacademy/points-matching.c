#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
typedef struct trip{
    int first;
    int second;
    int third;
}trip;
trip newTrip(int a, int b, int c){
    trip rez;
    rez.first =a;
    rez.second=b;
    rez.third =c;
    return rez;
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

trip*pushbackT(trip*array, int *size, trip value){
    trip*output = resizeArray(array, trip, *size + 1);
    output[(*size)++] = value;
    return output;
}

pair*pushbackP(pair*array, int *size, pair value){
    pair*output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}

int cmpT(const void*pa, const void*pb)
{
    trip*a=(trip*)pa;
    trip*b=(trip*)pb;
    int diff;
    diff = a->first  - b->first;  if(diff!=0) return diff;
    diff = a->second - b->second; if(diff!=0) return diff;
    return a->third  - b->third;
}
int cmpTrev(const void*pb, const void*pa)
{
    trip*a=(trip*)pa;
    trip*b=(trip*)pb;
    int diff;
    diff = a->first  - b->first;  if(diff!=0) return diff;
    diff = a->second - b->second; if(diff!=0) return diff;
    return a->third  - b->third;
}
int cmpP(const void*pa, const void*pb)
{
    pair*a=(pair*)pa;
    pair*b=(pair*)pb;
    int diff;
    diff = a->first  - b->first;  if(diff!=0) return diff;
    return a->second - b->second;
}

int compP( pair a, pair b)
{
    int diff;
    diff = a.first  - b.first;  if(diff!=0) return diff;
    return a.second - b.second;
}

pair minP(pair a,pair b){return compP(a,b)<0?a:b;}
pair maxP(pair a,pair b){return compP(a,b)>0?a:b;}




#define mp newPair
#define pb push_back
typedef long long ll;
typedef long double ld;

int n;
enum{ MAXN = 210000  };
enum{ INF  =(int)1e9 };
pair rmql[MAXN * 4];
pair rmqm[MAXN * 4];
int ddl[MAXN * 4];
int ddm[MAXN * 4];
int dp[MAXN];
int us[MAXN];
pair*vv   =NULL;int vvSz   =0;
pair*v1   =NULL;int v1Sz   =0;
pair*v2   =NULL;int v2Sz   =0;
trip*vvtmp=NULL;int vvtmpSz=0;
int ans[MAXN];


pair mrg(pair a, pair b) {
    return (a.first != b.first ? minP(a, b) : maxP(a, b));
}
void build(int v, int tl, int tr) {
    ddl[v] = 0;
    ddm[v] = 0;
    if (tl + 1 == tr) {
        if (vv[tl].second == 0) {
            rmql[v] = newPair(dp[tl], tl);
            rmqm[v] = newPair(INF, tl);
        }
        else {
            rmql[v] = newPair(INF, tl);
            rmqm[v] = newPair(vv[tl].first, tl);
        }
        return;
    }
    int m = (tl + tr) >> 1;
    build(v * 2 + 1, tl, m);
    build(v * 2 + 2, m, tr);
    rmqm[v] = minP(rmqm[v * 2 + 1], rmqm[v * 2 + 2]);
    rmql[v] = mrg(rmql[v * 2 + 1], rmql[v * 2 + 2]);
}
void addl(int v, int tl, int tr, int l, int r, int d) {
    if (r <= tl || tr <= l)
        return;
    if (l <= tl && tr <= r) {
        rmql[v].first += d;
        ddl[v] += d;
        return;
    }
    int m = (tl + tr) >> 1;
    addl(v * 2 + 1, tl, m, l, r, d);
    addl(v * 2 + 2, m, tr, l, r, d);
    rmql[v] = mrg(rmql[v * 2 + 1], rmql[v * 2 + 2]);
    rmql[v].first += ddl[v];
}
void addm(int v, int tl, int tr, int l, int r, int d) {
    if (r <= tl || tr <= l)
        return;
    if (l <= tl && tr <= r) {
        rmqm[v].first += d;
        ddm[v] += d;
        return;
    }
    int m = (tl + tr) >> 1;
    addm(v * 2 + 1, tl, m, l, r, d);
    addm(v * 2 + 2, m, tr, l, r, d);
    rmqm[v] = minP(rmqm[v * 2 + 1], rmqm[v * 2 + 2]);
    rmqm[v].first += ddm[v];
}
pair getl(int v, int tl, int tr, int l, int r) {
    if (r <= tl || tr <= l)
        return newPair(INF, 0);
    if (l <= tl && tr <= r) {
        return rmql[v];
    }
    int m = (tl + tr) >> 1;
    pair ans = mrg(getl(v * 2 + 1, tl, m, l, r), getl(v * 2 + 2, m, tr, l, r));
    ans.first += ddl[v];
    return ans;
}
pair getm(int v, int tl, int tr, int l, int r) {
    if (r <= tl || tr <= l)
        return newPair(INF, 0);
    if (l <= tl && tr <= r) {
        return rmqm[v];
    }
    int m = (tl + tr) >> 1;
    pair ans = minP(getm(v * 2 + 1, tl, m, l, r), getm(v * 2 + 2, m, tr, l, r));
    ans.first += ddm[v];
    return ans;
}
void solve() {
    int gn = n;
    for (int i = 0; i < gn; ++i)
        us[i] = -1;
    for (int i = 0; i < vvSz; ++i)
        if (vv[i].second == 0)
            us[vv[i].first] = i;
    int n = vvSz;
    if (n == 0)
        return;
    int now = 0;
    for (int i = 0; i < vvSz; ++i) {
        if (vv[i].second == 0)
            --now;
        else
            ++now;
        dp[i] = now;
    }
    build(0, 0, n);
    for (int i = 0; i < gn; ++i) {
        if (us[i] != -1) {
            int x = us[i];
            pair tmp = getl(0, 0, n, 0, x);
            int l = 0;
            if (tmp.first == 0)
                l = tmp.second + 1;
            tmp = getm(0, 0, n, l, x);
            ans[i] = tmp.first;
            addm(0, 0, n, tmp.second, tmp.second + 1, INF);
            addl(0, 0, n, tmp.second + 1, x, -1);
            addl(0, 0, n, x, x + 1, INF);
        }
    }
}
int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        --x;
        v1=pushbackP(v1, &v1Sz, newPair(x, i));
    }
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        --x;
        v2=pushbackP(v2, &v2Sz, newPair(x, i));
    }
    qsort(v1, v1Sz, sizeof(pair), cmpP);
    qsort(v2, v2Sz, sizeof(pair), cmpP);
    for (int i = 0; i < n; ++i) {
        if (v1[i].first < v2[i].first) {
            vvtmp=pushbackT(vvtmp, &vvtmpSz, newTrip(v1[i].first, v1[i].second, 0));
            vvtmp=pushbackT(vvtmp, &vvtmpSz, newTrip(v2[i].first, v2[i].second, 1));
        }
    }
    qsort(vvtmp, vvtmpSz, sizeof(trip), cmpTrev);//reverse
    //reverse(vvtmp, 0, vvtmpSz-1);
    for (int i = 0; i < vvtmpSz; ++i)
        vv=pushbackP(vv, &vvSz, newPair(vvtmp[i].second, vvtmp[i].third));
    solve();
    free(vv   );vv   =NULL;vvSz   =0;
    free(vvtmp);vvtmp=NULL;vvtmpSz=0;
    for(int i = 0; i < n; ++i) {
        if (v1[i].first > v2[i].first) {
            vvtmp=pushbackT(vvtmp, &vvtmpSz, newTrip(v1[i].first, v1[i].second, 0));
            vvtmp=pushbackT(vvtmp, &vvtmpSz, newTrip(v2[i].first, v2[i].second, 1));
        }
    }
    qsort(vvtmp, vvtmpSz, sizeof(trip), cmpT);
    for (int i = 0; i < vvtmpSz; ++i)
        vv=pushbackP(vv, &vvSz, newPair(vvtmp[i].second, vvtmp[i].third));
    solve();
    for (int i = 0; i < n; ++i)
        printf("%d ", ans[i] + 1);
    printf("\n");
    return 0;
}






























































