#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
typedef long long ll;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
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
int compP( pair a, pair b){
    int diff;
    diff = a.first  - b.first;  if(diff!=0) return diff;
    return a.second - b.second;
}
pair*pushbackP(pair *array, int *size, pair value) {
    pair *output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP() {
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
typedef struct{
   ll first;
   ll second;
}pll;
pll newPll(ll a, ll b){
   pll rez;
   rez.first =a;
   rez.second=b;
   return rez;
}
pll*pushbackPl(pll *array, int *size, pll value) {
    pll *output = resizeArray(array, pll, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	pll*ptr;
	int sz;
}vecpl;
vecpl newVecPl() {
	vecpl rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
enum{ N    =(int) 4e4 + 5};
enum{ M    =(int) 6e4 + 5};
enum{ L    =(int) 8e4 + 5};
enum{ V    =(int) 1e6    };
enum{ LG   =(int) 16     };
enum{ SQRT =(int) 256    };
enum{ MOD  =(ll ) 1e9 + 9};
typedef struct{
    int l, r, index;
}Query;
Query newQuery(int a, int b, int c){
    Query rez;
    rez.l     = a;
    rez.r     = b;
    rez.index = c;
    return rez;
}
vecpl psum[V];
vecp defact[N];
vec g[N];
pll ant[M];
ll  fact[V],
    inv[V];
int far[LG][N],
    lvl[N],
    val[N],
    exponent[V],
    euler[L],
    l_euler[N],
    r_euler[N];
bool in[N];
Query*qs;//vector<Query> qs;
ll q1, q2;
int n, q;
int cmpQ(const void*pa, const void*pb){
    Query*a=(Query*)pa;
    Query*b=(Query*)pb;
    return(compP(newPair(a->l / SQRT, a->r),
                 newPair(b->l / SQRT, b->r))< 0)?-1:1;
}
static ll expow(ll b, ll e){
    ll ant = 1;
    for (b%= MOD; e > 0; e/= 2) {
        if (e % 2)
            ant = ant * b % MOD;
        b = b * b % MOD;
    }
    return ant;
}
static void factor(int u){
    int e, tv = val[u];
    for (int p = 2; p * p <= tv; ++p) {
        e = 0;
        while (tv % p == 0) {
            tv/= p;
            e+= 1;
        }
        exponent[p]+= e;
        if (e > 0)
            defact[u].ptr = pushbackP(defact[u].ptr, &defact[u].sz, newPair(p, e));
    }
    if (tv > 1) {
        exponent[tv]+= 1;
        defact[u].ptr = pushbackP(defact[u].ptr, &defact[u].sz, newPair(tv, 1));
    }
}
static void dfs(int u, int pap){
    static int pb = 0;
    far[0][u] = pap;
    lvl[u] = lvl[pap] + 1;
    euler[++pb] = u;
    l_euler[u] = pb;
    for(int i=0;i<g[u].sz;i++){int v = g[u].ptr[i];
        if (v != pap)
            dfs(v, u);
    }
    euler[++pb] = u;
    r_euler[u] = pb;
}
static void make_str(){
    for (int lg = 1; lg < LG; ++lg)
        for (int i = 1; i <= n; ++i)
            far[lg][i] = far[lg - 1][far[lg - 1][i]];
}
static void number_theory(){
    fact[0] = 1;
    for (int i = 1; i < V; ++i)
        fact[i] = fact[i - 1] * i % MOD;
    inv[V - 1] = expow(fact[V - 1], MOD - 2);
    for (int i = V - 2; i >= 0; --i)
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    for (int i = 2; i < V; ++i)
        inv[i] = inv[i] * fact[i - 1] % MOD;
    for (int i = 1; i <= n; ++i)
        factor(i);
    for (int i = 1; i < V; ++i)
        if (exponent[i]) {
            ll t = i, ti = inv[i - 1];
//          psum[i].reserve(exponent[i]);
            psum[i].ptr = pushbackPl(psum[i].ptr, &psum[i].sz, newPll(1LL, 1LL));
            for (int j = 1; j <= exponent[i]; ++j) {
                t = t * i % MOD;
                psum[i].ptr = pushbackPl(psum[i].ptr, &psum[i].sz, newPll((t + MOD - 1) * ti % MOD, expow((t + MOD - 1) * ti % MOD, MOD - 2)));
            }
        }
    memset(exponent, 0, sizeof(exponent));
}
static int lca(int a, int b){
    if (lvl[a] < lvl[b])
        swap(a, b);
    for (int lg = LG - 1; lg >= 0; --lg)
        if (lvl[a] - (1 << lg) >= lvl[b])
            a = far[lg][a];
    if (a == b)
        return a;
    for (int lg = LG - 1; lg >= 0; --lg)
        if (far[lg][a] != far[lg][b]) {
            a = far[lg][a];
            b = far[lg][b];
        }
    return far[0][a];
}
static void mod(int pos){
    if (!in[euler[pos]]) {
        in[euler[pos]]^= true;
        int idx = euler[pos];
        for(int z=0;z<defact[idx].sz;z++){pair x = defact[idx].ptr[z];
            q1 = q1 * inv[exponent[x.first] + 1] % MOD;
            q2 = q2 * psum[x.first].ptr[exponent[x.first]].second % MOD;
            exponent[x.first]+= x.second;
            q1 = q1 * (exponent[x.first] + 1) % MOD;
            q2 = q2 * psum[x.first].ptr[exponent[x.first]].first % MOD;
        }
    }
    else {
        in[euler[pos]]^= true;
        int idx = euler[pos];
        for(int z=0;z<defact[idx].sz;z++){pair x = defact[idx].ptr[z];
            q1 = q1 * inv[exponent[x.first] + 1] % MOD;
            q2 = q2 * psum[x.first].ptr[exponent[x.first]].second % MOD;
            exponent[x.first]-= x.second;
            if (exponent[x.first] > 0) {
                q1 = q1 * (exponent[x.first] + 1) % MOD;
                q2 = q2 * psum[x.first].ptr[exponent[x.first]].first % MOD;
            }
        }
    }
}
void mo(){
    int tlca, gl = 1, gr = 1;
    q1 = q2 = 1LL;
    mod(1);
    for(int i=0;i<q;i++){Query myq = qs[i];
        while (gl < myq.l) mod(gl++);
        while (gl > myq.l) mod(--gl);
        while (gr < myq.r) mod(++gr);
        while (gr > myq.r) mod(gr--);
        ant[myq.index] = newPll(q1, q2);
        tlca = lca(euler[myq.l], euler[myq.r]);
        if (tlca != euler[myq.l] && tlca != euler[myq.r]) {
            mod(l_euler[tlca]);
            ant[myq.index] = newPll(q1, q2);
            mod(l_euler[tlca]);
        }
    }
}
int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &val[i]);
    for (int a, b, i = 1; i < n; ++i) {
        scanf("%d %d", &a, &b);
        g[a].ptr = pushback(g[a].ptr, &g[a].sz, b);
        g[b].ptr = pushback(g[b].ptr, &g[b].sz, a);
    }
    dfs(1, 0);
    make_str();
    number_theory();
    scanf("%d", &q);
    qs = calloc(q, sizeof(Query));
    for (int x, y, i = 0; i < q; ++i) {
        scanf("%d %d", &x, &y);
        if (l_euler[x] > l_euler[y])
            swap(x, y);
        if (lca(x, y) == x)
             qs[i] = newQuery(l_euler[x], l_euler[y], i);
        else qs[i] = newQuery(r_euler[x], l_euler[y], i);
    }
    qsort(qs, q, sizeof(Query), cmpQ);
    mo();
    for (int i = 0; i < q; ++i)
        printf("%lld %lld\n", ant[i].first, ant[i].second);
    return 0;
}




