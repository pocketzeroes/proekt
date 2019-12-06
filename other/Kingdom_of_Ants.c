#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
typedef long long ll;
typedef struct{
  int first;
  ll  second;
}pil;
pil newpil(int a, ll b){
  return(pil){a,b};
}
int cmpP(pil a, pil b){
  if(a.first !=b.first )return(a.first <b.first )?-1:1;
  if(a.second!=b.second)return(a.second<b.second)?-1:1;
  return 0;
}
pil minp(pil a,pil b){return cmpP(a,b)<0?a:b;}

#define pbl(zpv, zvv) zpv.ptr = pushbackL(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll*pushbackL(ll*array, int*size, ll value){
  ll*output = resizeArray(array, ll, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  ll*ptr;
  int sz;
}vecl;
vecl newVecL(){
  vecl rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
int cmpLL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}

ll unique(ll*a, ll len){
  ll i, j;
  for(i = j = 0; i < len; i++)
    if(a[i] != a[j])
      a[++j] = a[i];
  return j + 1;
}
ll lower_bound(ll*a, ll n, ll x){
  ll l = 0;
  ll h = n;
  while (l < h) {
    ll mid = (l + h) / 2;
    if (x <= a[mid]) 
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}

#define fi first
#define se second
enum{N =(int)2E5 + 5};
int n;
ll x, y, u, v, ans;
vecl ve;

typedef struct{
    ll u, l, r, val;
}event;
event newevent(ll u, ll l, ll r, ll v){
    return(event){u,l,r,v};
}
#define pbe(zpv, zvv) zpv.ptr = pushbackE(zpv.ptr, &zpv.sz, zvv)
event*pushbackE(event*array, int *size, event value){
  event*output = resizeArray(array, event, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	event*ptr;
	int sz;
}vece;
vece newVecE(){
	vece rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int cmpE(const void*pa, const void*pb){
    event*u = (event*)pa;
    event*v = (event*)pb;
    return(u->u < v->u)?-1:1;
}
vece sw;

//typedef struct segment_tree{
#define m (l + r) / 2
#define lc i * 2
#define rc i * 2 + 1
ll eve[4 * N],
   odd[4 * N];
pil mi[4 * N];//pil{int,ll}
int lz[4 * N];

void apply(int i, int v){
    lz[i]    += v;
    mi[i].fi += v;
    if(abs(v) % 2 == 1)
        swap(eve[i], odd[i]);
}
void down(int i){
    apply(lc, lz[i]);
    apply(rc, lz[i]);
    lz[i] = 0;
}
void build(int l, int r, int i){
    if(l == r){
        eve[i] = mi[i].se = ve.ptr[l + 1] - ve.ptr[l];
        odd[i] = 0;
    }
    else{
        build(l, m, lc);
        build(m + 1, r, rc);
        eve[i] = eve[lc] + eve[rc];
        odd[i] = 0;
        mi[i].se = eve[i];
    }
}
void update(int l, int r, int i, int L, int R, int v){
    if(l > R || r < L || L > R)
        return;
    else if(L <= l && r <= R)
        apply(i, v);
    else{
        down(i);
        update(l, m, lc, L, R, v);
        update(m + 1, r, rc, L, R, v);
        eve[i] = eve[lc] + eve[rc];
        odd[i] = odd[lc] + odd[rc];
        mi [i] = minp(mi[lc], mi[rc]);
        if(mi[lc].fi == mi[rc].fi)
           mi[i].se = mi[lc].se + mi[rc].se;
    }
}
#undef m
#undef lc
#undef rc

int main(){
    scanf("%d", &n);
    for(int i=1; i<=n; i++){
        scanf("%lld %lld %lld %lld", &x, &y, &u, &v);
        if(x > u)
            swap(x, u);
        if(y > v)
            swap(y, v);
        if(x == u || y == v)
            continue;
        pbe(sw, newevent(x, y, v, 1));
        pbe(sw, newevent(u, y, v,-1));
        pbl(ve, y);
        pbl(ve, v);
    }
    if(sw.sz==0)
        return puts("0")*0;
    qsort(ve.ptr, ve.sz, sizeof(ll), cmpLL);
    qsort(sw.ptr, sw.sz, sizeof(event), cmpE);
    ve.sz = unique(ve.ptr, ve.sz);
    int n = ve.sz - 1;
    build(0, n - 1, 1);
    for(int i=0; i<sw.sz-1; i++){
        int l = lower_bound(ve.ptr, ve.sz, sw.ptr[i].l);
        int r = lower_bound(ve.ptr, ve.sz, sw.ptr[i].r)-1;
        update(0, n - 1, 1, l, r, sw.ptr[i].val);
        ans += 1LL*(sw.ptr[i + 1].u - sw.ptr[i].u) * (eve[1] - (mi[1].fi == 0) * mi[1].se);
    }
    printf("%lld\n", ans);
    return 0;
}
