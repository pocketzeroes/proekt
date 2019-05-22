#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
typedef long long ll;

typedef struct{
  ll  first;
  int second;
}pair;
pair newPair(ll a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}

enum{ INF      =(int)1e9};
enum{ MAXNODES = 262144 };
enum{ offset   = 131072 };
int n, k, q;


typedef struct{
  int len;
  pair pref[50];
  pair suff[50];
  int ans;
}node;
node tree[MAXNODES];

node newnode(int t, int v){
  node rez;
  rez.len = 1;
  rez.pref[0] = rez.suff[0] = (pair){1LL<<v, t};
  rez.ans = INF;
  return rez;
}
inline bool subset(ll mask1, ll mask2){
  return (mask1 & mask2) == mask1;
}
void merge(node*t, node*l, node*r){
  int pref_len, 
      suff_len;
  pref_len = 0;
  for (int i = 0; i < l->len; ++i)
    t->pref[pref_len++] = l->pref[i];
  for (int i = 0; i < r->len; ++i)
    if (pref_len == 0 || !subset(r->pref[i].first, t->pref[pref_len-1].first)) {
      t->pref[pref_len] = r->pref[i];
      if (pref_len > 0)
        t->pref[pref_len].first |= t->pref[pref_len-1].first;
      ++pref_len;
    }
  suff_len = 0;
  for (int i = 0; i < r->len; ++i)
    t->suff[suff_len++] = r->suff[i];
  for (int i = 0; i < l->len; ++i)
    if (suff_len == 0 || !subset(l->suff[i].first, t->suff[suff_len-1].first)) {
      t->suff[suff_len] = l->suff[i];
      if (suff_len > 0)
        t->suff[suff_len].first |= t->suff[suff_len-1].first;
      ++suff_len;
    }
  assert(pref_len == suff_len);
  t->len = pref_len;
  t->ans = INF;
  int pref_pos = 0;
  for (int suff_pos = l->len-1; suff_pos >= 0; --suff_pos){
    while (pref_pos < r->len && (l->suff[suff_pos].first | r->pref[pref_pos].first) != (1LL<<k)-1)
      ++pref_pos;
    if (pref_pos < r->len){
      ll curr_mask = l->suff[suff_pos].first | r->pref[pref_pos].first;
      if(curr_mask == (1LL<<k)-1)
        t->ans = min(t->ans, r->pref[pref_pos].second-l->suff[suff_pos].second+1);
    }
  }
  t->ans = min(t->ans, min(l->ans, r->ans));
}
void update(int t, int v){
  t += offset;
  tree[t] = newnode(t-offset, v);
  for (t /= 2; t > 0; t /= 2)
    merge(&tree[t], &tree[2*t], &tree[2*t+1]);
}
int query(){
  return tree[1].ans;
}
int main(){
  for(int i=0;i<MAXNODES;i++)
    tree[i].ans=INF;
  scanf("%d %d %d", &n, &k, &q);
  for (int i=0; i<n; ++i){
    int v;
    scanf("%d", &v);
    --v;
    update(i, v);
  }
  for(int i=0; i<q; ++i){
    int t;
    scanf("%d", &t);
    if (t == 1){
      int x, v;
      scanf("%d %d", &x, &v);
      --x, --v;
      update(x, v);
    }
    else{
      int ans = query();
      printf("%d\n", ans == INF ? -1 : ans);
    }
  }
  return 0;
}
