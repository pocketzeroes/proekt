#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}
typedef struct{
  ll first;
  ll second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}

#define inf   100010LL
#define Worst 1000000000000000001LL
#define N 10100
typedef struct{
  ll a;
  ll b;
}Line;
ll get(Line*l, ll x){
  if(l->a > inf)
    return Worst;
  return l->a * x + l->b;
}
Line newLine(ll u, ll v){
  Line ret;
  ret.a = u;
  ret.b = v;
  return ret;
}

typedef struct{
  ll  low, high;
  int root, cnt;
  int*L;
  int*R;
  Line*it;
  ll lef, rig;
}LineIT;

LineIT newLineIT(ll from, ll to){
  LineIT rez;
  rez.low  = from;
  rez.high = to;
  rez.L    = calloc(N*16+10, sizeof(int));
  rez.R    = calloc(N*16+10, sizeof(int));
  rez.it   = calloc(N*16+10, sizeof(Line));
  for(int i=0;i<N*16+10;i++)
    rez.it[i] = newLine(inf+1, inf+1);
  rez.root = rez.cnt = 1;
  return rez;
}
void upd   (LineIT*this, int*x, ll l, ll r, Line val){
  if(l > this->rig || r < this->lef) 
    return;
  if(*x == 0)
    (*x) = ++this->cnt;
  ll mid  = ((l + r) >> 1);
  if(l >= this->lef && r <= this->rig){
    if(get(&this->it[*x], l) <= get(&val, l) && get(&this->it[*x], r)   <= get(&val, r))
      return;
    if(get(&this->it[*x], l) >= get(&val, l) && get(&this->it[*x], r)   >= get(&val, r)){
      this->it[*x] = val;
      return;
    }
    if(get(&this->it[*x], l) >= get(&val, l) && get(&this->it[*x], mid) >= get(&val, mid)){
      upd(this, &this->R[*x], mid + 1, r, this->it[*x]);
      this->it[*x] = val;
      return;
    }
    if(get(&this->it[*x], l) <= get(&val, l) && get(&this->it[*x], mid) <= get(&val, mid)){
      upd(this, &this->R[*x], mid + 1, r, val);
      return;
    }
    if(get(&this->it[*x], mid + 1) >= get(&val, mid + 1) && get(&this->it[*x], r) >= get(&val, r)){
      upd(this, &this->L[*x], l, mid, this->it[*x]);
      this->it[*x] = val;
      return;
    }
    if(get(&this->it[*x], mid + 1) <= get(&val, mid + 1) && get(&this->it[*x], r) <= get(&val, r)){
      upd(this, &this->L[*x], l, mid, val);
      return;
    }
  }
  upd(this, &this->L[*x], l, mid, val);
  upd(this, &this->R[*x], mid + 1, r, val);
}
ll   query (LineIT*this, int x, int l, int r, ll val){
  if(l > val || r < val || x == 0)
      return Worst;
  if(l == r) 
    return get(&this->it[x], val);
  ll mid  = ((l + r) >> 1);
  ll ans = get(&this->it[x], val);
  ans = min(ans, query(this, this->L[x], l, mid, val));
  ans = min(ans, query(this, this->R[x], mid + 1, r, val));
  return ans;
}
void update(LineIT*this, ll a, ll b, pair seg){
  if(seg.first != -inf - 1){
    this->lef = seg.first;
    this->rig = seg.second;
  }
  else{
    this->lef = this->low;
    this->rig = this->high;
  }
  upd(this, &this->root, this->low, this->high, newLine(a, b));
}
ll   ask   (LineIT*this, ll x){
  return query(this, this->root, this->low, this->high, x);
}
////////////////////


enum{ K =   110};
#undef  N
#define N 10010
int n, k;
int a[N];
ll f[N][K];

int main(){
  scanf("%d %d", &n, &k);
  for(int i = 1; i <= n; ++i) 
    scanf("%d", a + i);
  memset(f, 60, sizeof f);
  f[0][0] = 0;
  for(int j = 1; j <= k; ++j){
    LineIT smt = newLineIT(1, 1000000);
    for(int i = 1; i <= n; ++i){
      if(i - 1 >= j - 1)
        update(&smt, -2*a[i], 1LL*a[i]*a[i]+f[i-1][j-1], newPair(-inf-1, -inf-1));
      f[i][j] = 1LL * a[i] * a[i] + ask(&smt, a[i]);
    }
    free(smt.L);
    free(smt.R);
    free(smt.it);
  }
  printf("%lld\n", f[n][k]);
  return 0;
}


