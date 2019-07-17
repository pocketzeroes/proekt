#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
int upper_bound(ll*a, int n, ll x){
    int l = 0;
    int h = n;
    while (l < h){
        int md = (l + h) / 2;
        if (x >= a[md])
            l = md + 1;
        else
            h = md;
    }
    return l;
}
int lower_bound(ll*a, int n, ll x){
    int l = 0;
    int h = n;
    while (l < h){
        int md = (l + h) / 2;
        if (x <= a[md]) 
            h = md;
        else
            l = md + 1;
    }
    return l;
}

#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
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
int cmpL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}
void erase(vec*v, int pos){
    for(int i=pos; i < v->sz-1; i++)
        v->ptr[i] = v->ptr[i+1];
    (v->sz)--;
}
//////////////////////////////
#define mid ((l+r)>>1)


enum{ MAXN = 1000   + 10};
enum{ MAXM = 100000 + 10};
enum{ SIZE = MAXM << 6  };
vec G[MAXN];
int ls[SIZE], rs[SIZE], cnt[SIZE], rt[MAXM];
int wt[MAXN][MAXN], dsu[MAXN], vis[MAXN];
int sz, n, m, cas;
ll E[MAXM];

void ins(int*now, int pre, int p, int v, int l, int r){
   *now = sz++;
    cnt[*now] = cnt[pre] + v;
    ls [*now] = ls[pre], rs[*now] = rs[pre];
    if (l + 1 == r)
        return;
    if (p < mid)
        ins(&ls[*now], ls[pre], p, v, l, mid);
    else
        ins(&rs[*now], rs[pre], p, v, mid, r);
}
int ask(int rt, int l, int r, int L, int R){
    if (L <= l && R >= r) 
        return cnt[rt];
    int ret = 0;
    if (L < mid) 
        ret += ask(ls[rt], l, mid, L, R);
    if (R > mid) 
        ret += ask(rs[rt], mid, r, L, R);
    return ret;
}
int get1(int x){
    if(x == dsu[x])
        return x;
    else{
        dsu[x] = get1(dsu[x]);
        return dsu[x];
    }
}
bool get(int b, int e, int*x, int*y, int*z){
    static int Q[MAXN], 
               P[MAXN];
    if(get1(b) != get1(e))
        return dsu[get1(b)] = get1(e), false;
    ++ cas;
    Q[0] = b;
    vis[b] = cas;
    for (int h = 0, t = 1; h < t; ++ h){
        int u = Q[h];
        if (u == e){
            *x = -1;
            *y = -1;
            *z = -1;
            for (; h; h = P[h]){
                int v = Q[P[h]];
                if (wt[u][v] > *z)
                    *z = wt[u][v], *x = u, *y = v;
                u = v;
            }
            return true;
        }
        for(int q=0;q<G[u].sz;q++){int v = G[u].ptr[q];
            if (vis[v] != cas){
                vis[v] = cas;
                P[t] = h;
                Q[t ++] = v;
            }
        }
    }
    return true;
}
int main(){
    int T;
    scanf("%d", &T);
    while (T --) {
        scanf("%d%d", &n, &m); cas = 0;
        for (int i = 0; i < n; ++ i){
            G[i].sz=0;
            dsu[i] = i;
        }
        for (int i = 0; i < m; ++ i){
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            if (u > v)
                swap(u, v);
            --u, --v;
            E[i] = ((ll)w << 20) | (u << 10) | v;
        }
        qsort(E, m, sizeof(ll), cmpL);
        rt[m] = ls[0] = rs[0] = cnt[0] = 0;
        sz = 1;
        for (int i = m - 1; i >= 0; -- i) {
            int u = (E[i] >> 10) & 1023, v = E[i] & 1023, w = E[i] >> 20;
            int x, y, z; rt[i] = rt[i + 1];
            if(get(u, v, &x, &y, &z)){
                if (x > y)
                    swap(x, y);
                int now = lower_bound(E, m, ((ll)z << 20) | (x << 10) | y);
                ins(&rt[i], rt[i], now, -z, 0, m);
                for(int z=0;z<G[x].sz;z++){int it = G[x].ptr[z];
                    if(it == y){
                        erase(&G[x], z);
                        break;
                    }
                }
                for(int z=0;z<G[y].sz;z++){int it = G[y].ptr[z];
                    if(it == x){
                        erase(&G[y], z);
                        break;
                    }
                }
            }
            ins(&rt[i], rt[i], i, w, 0, m);
            G[u].ptr = pushback(G[u].ptr, &G[u].sz, v);
            G[v].ptr = pushback(G[v].ptr, &G[v].sz, u);
            wt[u][v] = wt[v][u] = w;
        }
        int q;
        scanf("%d", &q);
        for (int i = 0, last = 0; i < q; ++ i) {
            int l, r;
            scanf("%d%d", &l, &r);
            l -= last;
            r -= last;
            int x = lower_bound(E, m, (ll)l << 20);
            int y = upper_bound(E, m, ((ll)r << 20) | (n << 10) | n);
            last = ask(rt[x], 0, m, x, y);
            printf("%d\n", last);
        }
    }
    return 0;
}
