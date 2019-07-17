#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
void swap(int*nums, int i, int j) {
  int t   = nums[i];
  nums[i] = nums[j];
  nums[j] = t;
}



typedef long long ll;

enum{ MOD = 1000000007};
enum{ MAX_N = 200     };


int n, k;
pair edge[MAX_N];
int start[MAX_N];
int size [MAX_N];
ll fact[MAX_N+1];
ll factinv[MAX_N+1];

ll gcd(ll a, ll b, ll*s, ll*t){
  if(b==0){
   *t = 0;
   *s = (a < 0) ? -1 : 1;
    return (a < 0) ? -a : a;
  }
  else{
    ll g = gcd(b, a%b, t, s);
   (*t) -= a/b * (*s);
    return g;
  }
}
void init(){
  fact[0] = fact[1] = 1;
  factinv[0] = factinv[1] = 1;
  for (int i = 2; i <= MAX_N; i++) {
    fact[i] = (fact[i-1] * i) % MOD;
    ll t;
    gcd(fact[i], MOD, &factinv[i], &t);
    if (factinv[i] < 0)
      factinv[i] += MOD;
    factinv[i] %= MOD;
  }
}
void compute_size(int r){
  size[r] = 1;
  int s = start[r];
  if (s == -1)
    return;
  while (edge[s].first == r){
    int c = edge[s].second;
    compute_size(c);
    size[r] += size[c];
    s++;
  }
}
void read_tree(){
  for (int i = 2; i <= n; i++){
    int p;
    scanf("%d", &p);
    edge[i-2] = newPair(p-1, i-1);
  }
  qsort(edge, n-1, sizeof(pair), cmpP);
  edge[n-1] = newPair(MAX_N+1, MAX_N+1);
  fill(start, n, -1);
  for (int i = 0; i < n-1; i++){
    if (i == 0 || edge[i].first != edge[i-1].first)
      start[edge[i].first] = i;
  }
}
ll table[MAX_N][MAX_N+1][2];
void distribute(int r, int child[], int num_child, bool cheat);

void f(int r, int inv){
  if (table[r][0][inv] >= 0)
    return;
  int s = start[r];
  if (s == -1) {
    for (int t = 0; t <= k; t++)
      table[r][t][inv] = 0;
    table[r][0][0] = 1;
    return;
  }
  int child[MAX_N];
  int num_child = 0;
  for (int t = s; edge[t].first == r; t++) {
    child[num_child++] = edge[t].second;
    f(child[num_child-1], 0);
    f(child[num_child-1], 1);
  }
  for (int t = 0; t <= k; t++)
    table[r][t][inv] = 0;
  if (inv) {
    if (k == 0)
      return;
    for (int c = 0; c < num_child; c++) {
      swap(child, c, 0);
      distribute(r, child, num_child, inv);
      swap(child, c, 0);
    }
  }
  else
    distribute(r, child, num_child, inv);
}
ll mult(ll a, ll b){
  return (a * b) % MOD;
}
ll choose(int n, int k){
  return mult(mult(fact[n], factinv[k]), factinv[n-k]);
}
void distribute(int r, int child[], int num_child, bool cheat){
  int inv = cheat ? 1 : 0;
  int s = size[r]-1;
  int fs = cheat ? size[child[0]]-1 : size[child[0]];
  ll row[MAX_N+1] = {0};
  for (int j = 0; j <= k-inv; j++) {
    row[j] = mult(table[child[0]][j][0], choose(s, fs));
    if (!cheat) {
      row[j] += mult(table[child[0]][j][1], choose(s, fs));
      row[j] %= MOD;
    }
  }
  s -= size[child[0]];
  for (int i = 1; i < num_child; i++) {
    ll temp[MAX_N+1] = {0};
    for (int j1 = 0; j1 <= k-inv; j1++) {
      for (int j2 = 0; j1+j2 <= k-inv; j2++){
        int j = j1+j2;
        temp[j] += mult(row[j1], mult(table[child[i]][j2][0], choose(s, size[child[i]])));
        temp[j] %= MOD;
        temp[j] += mult(row[j1], mult(table[child[i]][j2][1], choose(s, size[child[i]])));
        temp[j] %= MOD;
      }
    }
    s -= size[child[i]];
    for (int j = 0; j <= k-inv; j++)
      row[j] = temp[j];
  }
  for (int j = 0; j <= k-inv; j++) {
    table[r][j+inv][inv] += row[j];
    table[r][j+inv][inv] %= MOD;
  }
}
bool solve(){
  scanf("%d %d", &n, &k);
  if (!n && !k)
    return false;
  read_tree();
  fill(size, n, 0);
  compute_size(0);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= k; j++)
      table[i][j][0] = table[i][j][1] = -1;
  }
  ll ans = 0;
  f(0,0);
  f(0,1);
  for (int i = 0; i <= k; i++) {
    ans += (table[0][i][1] + table[0][i][0]) % MOD;
    ans %= MOD;
  }
  printf("%lld\n", ans);
  return true;
}
int main(){
  init();
  while(solve());
  return 0;
}
