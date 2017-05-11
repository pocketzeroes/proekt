#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<limits.h>
#ifdef _WIN32
  #define inline static
#endif
inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}
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
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, int *size, pair value){
    pair*output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
int cmpP(const void*pb, const void*pa)
{
  pair*a=(pair*)pa;
  pair*b=(pair*)pb;
  int diff;
  diff = a->first  - b->first;  if(diff!=0) return diff;
  return a->second - b->second;
}


typedef struct vecS {
	pair*ptr;
	int  sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


enum{ N =(int)3e5 + 6};
enum{ M = 32         };
vec have[N];
int du[N], n, all[N], dv[N], dc[N], dr[N], ql[N], qr[N], qu[N], qv[N], qres[M][N], dp[M], res[N], queries[N];
int mark[M];
int cnt, g[N], head[N], prev[N];
int sum[N];


inline int do_query(int x, int y, int posid) {
    int res = 1e9;
    res = min(res, (x == y) ? 0 : (int) 1e9);
    res = min(res, (du[posid] == x && dv[posid] == y) ? dc[posid] : (int) 1e9);
    res = min(res, (dv[posid] == x && du[posid] == y) ? dc[posid] : (int) 1e9);
    return res;
}
void add(int x, int val) {
    g[cnt] = val;
    prev[cnt] = head[x];
    head[x] = cnt++;
}
void solve(int b, int e){
    if (b + 1 == e) return;
    int m = b + e >> 1;
    int t = 0, sz = 0;
    cnt = 0;
    int mask = 0;
    for (int j = b; j <= e; ++j) head[j] = -1;
    for (int pl = m + 1; pl <= e; ++pl) {
        while(have[pl].sz){
            pair cur = have[pl].ptr[have[pl].sz-1];
            if (cur.first >= m){
                break;
            }
            if (cur.first < b) assert(0);
            have[pl].sz--;
            int j = cur.second;
            queries[t++] = j;
            mask |= 1 << qv[j];
            mask |= 1 << qu[j];
            add(ql[j], j);
            add(qr[j], j);
        }
    }
    if (t > 0) {
        if (e - b + sz <= 400 || 1) {
            for (int j = b; j < e; ++j) { 
                mask |= 1 << du[j];
                mask |= 1 << dv[j];
            }
            sz = 0;
            for (int j = 0; j < n; ++j) if (mask >> j & 1) all[sz++] = j;
        }
        else {
            sz = 0;
            for (int j = 0; j < n; ++j) all[sz++] = j;
        }
        for (int sti = 0; sti < sz; ++sti) { int st = all[sti];
            for (int x = 0; x < sz; ++x) dp[all[x]] = 1e9;
            dp[st] = 0;
            for (int j = m; j < e; ++j) {
                int uval = 1e9, vval = 1e9;
                if (dp[dv[j]] < 5e8) uval = min(uval, dp[dv[j]] + do_query(dv[j], du[j], j));
                if (dp[du[j]] < 5e8) uval = min(uval, dp[du[j]] + do_query(du[j], du[j], j));
                if (dp[dv[j]] < 5e8) vval = min(vval, dp[dv[j]] + do_query(dv[j], dv[j], j));
                if (dp[du[j]] < 5e8) vval = min(vval, dp[du[j]] + do_query(du[j], dv[j], j));
                dp[du[j]] = uval;
                dp[dv[j]] = vval;
                for (int x = head[j + 1]; ~x; x = prev[x]) {
                    int pos = g[x];
                    qres[st][pos] += dp[qv[pos]];
                }
            }
            for (int x = 0; x < sz; ++x) dp[all[x]] = 1e9;
            dp[st] = 0;
            for (int j = m - 1; j >= b; --j) {
                int uval = 1e9, vval = 1e9;
                if (dp[dv[j]] < 5e8) uval = min(uval, dp[dv[j]] + do_query(dv[j], du[j], j));
                if (dp[du[j]] < 5e8) uval = min(uval, dp[du[j]] + do_query(du[j], du[j], j));
                if (dp[dv[j]] < 5e8) vval = min(vval, dp[dv[j]] + do_query(dv[j], dv[j], j));
                if (dp[du[j]] < 5e8) vval = min(vval, dp[du[j]] + do_query(du[j], dv[j], j));
                dp[du[j]] = uval;
                dp[dv[j]] = vval;
                for (int x = head[j]; ~x; x = prev[x]) {
                    int pos = g[x];
                    qres[st][pos] += dp[qu[pos]];
                }
            }
            for (int j = 0; j < t; ++j) { int x = queries[j];
                res[x] = min(res[x], qres[st][x]);
            }
        }
    }
    solve(b, m);
    solve(m, e);
}
int main(){
    memset(res, 63, sizeof(res));
    int m, q;
    scanf("%d %d %d", &n, &m, &q);
    for (int j = 0; j < m; ++j) {
        int u,v,c,r;

        scanf("%d %d %d %d", &u, &v, &c, &r);
        --u, --v;

        du[j]=u; 
        dv[j]=v; 
        dc[j]=c; 
        dr[j]=r;

        sum[j + 1] = sum[j] + dr[j];
        dc[j] -= dr[j];
    }
    for (int j = 0; j < q; ++j) {
        scanf("%d %d %d %d", qu + j, qv + j, ql + j, qr + j);
        --qu[j], --qv[j];
        --ql[j];
        if (qr[j] - ql[j] <= 1) res[j] = do_query(qu[j], qv[j], ql[j]);
        int idx=qr[j];
        have[idx].ptr=pushbackP(have[idx].ptr, &have[idx].sz, newPair(ql[j], j));
    }
    for (int j = 0; j <= m; ++j) { 
        qsort(have[j].ptr, have[j].sz, sizeof(pair), cmpP);
    }
    solve(0, m);
    for (int j = 0; j < q; ++j) {
        printf("%d\n", (res[j] >= 5e8 ? -1 : res[j] + sum[qr[j]] - sum[ql[j]]));
    }
}




































































