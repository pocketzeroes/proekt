#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

inline int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
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
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
enum{ mod = (int)1e9+7};
enum{ oo  = (int)1e9+1};
ll*inv;
int*bs;
vec*cs;

typedef struct{
  ll*cs;
  int n;
}Poly;
Poly newPoly(ll*cs, int n){
  return(Poly){cs, n};
}
Poly mkPoly(ll x){
  Poly rez;
  rez.cs=calloc(1, sizeof(ll));
  rez.cs[0]=x;
  rez.n=1;
  return rez;
}
void add(Poly*p, ll x){
  p->cs[0] = (p->cs[0]+x)%mod;
}
Poly multiply(Poly p, Poly q){
  ll*cc = calloc(p.n+q.n-1, sizeof(ll));
  for(int i = 0; i < p.n; i++)
    for(int j = 0; j < q.n; j++)
      cc[i + j] = (cc[i + j] + p.cs[i] * q.cs[j]) % mod;
  return newPoly(cc, p.n+q.n-1);
}
Poly integrate(Poly p){
  ll*cc = calloc(p.n+1, sizeof(ll));
  for(int i = 1; i <= p.n; i++)
    cc[i] = (p.cs[i - 1] * inv[i]) % mod;
  return newPoly(cc, p.n+1);
}
ll eval(Poly p, ll x){
  ll xpow = 1;
  ll y = 0;
  for(int i=0; i<p.n; i++){
    y = (y + xpow * p.cs[i]) % mod;
    xpow = xpow * x % mod;
  }
  return y;
}
//poly
typedef struct{
  Poly*ps;
  int* rs;
  int  m;
}Piece;
Piece newPiece(Poly*ps, int*rs, int sz){
  return(Piece){ps, rs, sz};
}
Piece mult(Piece p, Piece q){
  Poly*ps = calloc(p.m+q.m, sizeof(Poly));
  int* rs = calloc(p.m+q.m, sizeof(int) );
  int left= -oo,
      n   = 0;
  for(int a=0, b=0; a<p.m&&b<q.m; n++){
    ps[n] = multiply(p.ps[a], q.ps[b]);
    rs[n] = fmin(p.rs[a], q.rs[b]);
    left = rs[n];
    while(a < p.m && p.rs[a] == left)
      a++;
    while(b < q.m && q.rs[b] == left)
      b++;
  }
  return newPiece(ps, rs, n);
}
Piece integr(Piece p){
  Poly*nps = calloc(p.m, sizeof(Poly));
  int* nrs = calloc(p.m, sizeof(int) );
  ll C = 0;
  int left = -oo;
  for(int i=0; i<p.m; i++){
    nps[i] = integrate(p.ps[i]);
    nrs[i] = p.rs[i];
    add(&nps[i], C - eval(nps[i], left));
    C = eval(nps[i], nrs[i]);
    left = nrs[i];
  }
  return newPiece(nps, nrs, p.m);
}
//piece
ll Pow(ll x, ll e){
  ll y = 1;
  while(e > 0){
    if((e & 1) != 0)
      y = y*x%mod;
    x = x*x%mod;
    e >>= 1;
  }
  return y;
}
ll Inv(ll x){
  return Pow(x, mod-2);
}
Piece solve(int node){
  Poly*pa = calloc(3, sizeof(Poly));
  pa[0] = mkPoly(0);
  pa[1] = mkPoly(Inv(bs[node]));
  pa[2] = mkPoly(0);
  int* pb = calloc(3, sizeof(int));
  pb[0]=-bs[node];
  pb[1]=0;
  pb[2]=oo;
  Piece pdf = newPiece(pa, pb, 3);
  for(int z=0;z<cs[node].sz;z++){int c = cs[node].ptr[z];
    pdf = mult(pdf, solve(c));
  }
  return integr(pdf);
}
int main(){
  int n = in_nextInt();
  inv = calloc(n+1, sizeof(ll));
  for(int i=1; i<=n; i++)
    inv[i] = Inv(i);
  bs = calloc(n, sizeof(int));
  cs = calloc(n, sizeof(vec));
  int root = -1;
  for(int i=0; i<n; i++){
    bs[i] = in_nextInt();
    int p = in_nextInt() - 1;
    if(p >= 0)
      cs[p].ptr = pushback(cs[p].ptr, &cs[p].sz, i);
    else
      root = i;
  }
  Piece res = solve(root);
  ll ans = res.ps[res.m-1].cs[0];
  if(ans < 0)
    ans += mod;
  printf("%lld\n", ans);
  return 0;
}
