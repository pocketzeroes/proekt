#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
int cmpLL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}
int unique(ll*a, int len){
  int i, j;
  for(i = j = 0; i < len; i++)
    if(a[i] != a[j])
      a[++j] = a[i];
  return j + 1;
}
ll lower_bound(ll*a, ll n, ll x){
  ll l = 0;
  ll h = n;
  while(l < h){
    ll mid = (l + h) / 2;
    if(x <= a[mid]) 
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}
enum{MAXN = 10010};
#define GET (ch>='0'&&ch<='9')

int n, cnt, top, ans, tp;
ll sta[MAXN * 3];
int mat[MAXN], 
    vis[MAXN];

struct data{
  int a, b;
  ll c[3];
}s[MAXN];
typedef struct data data;
struct edge{
  int to;
  struct edge*next;
}e[MAXN << 1], *Prev[MAXN];
typedef struct edge edge;
struct Ans{
  int a, b, opt, id;
  ll c;
}q[MAXN];
typedef struct Ans Ans;

inline void insert(int u, int v){
  e[++top].to = v;
  e[top].next = Prev[u];
  Prev[u] = &e[top];
}
#define in(x) do{                                 \
  char ch = getchar ();                           \
  x = 0;                                          \
  int flag = 1;                                   \
  while (!GET)                                    \
    flag = ch == '-' ? -1 : 1, ch = getchar ();   \
  while (GET)                                     \
    x = x * 10 + ch - '0', ch = getchar ();       \
  x *= flag;                                      \
}while(0)

bool find(int x){
  for (edge * i = Prev[x]; i; i = i->next){
    if (!vis[i->to]){
      vis[i->to] = 1;
      if (!mat[i->to] || find (mat[i->to])){
        mat[i->to] = x;
        return 1;
      }
    }
  }
  return 0;
}
int cmp(const void*pa, const void*pb){
  Ans*a=(Ans*)pa;
  Ans*b=(Ans*)pb;
  return(a->id < b->id)?-1:1;
}
int main(){
  in(n);
  for(int i = 1; i <= n; i++){
    in(s[i].a);
    in(s[i].b);
    s[i].c[0] = s[i].a + s[i].b, s[i].c[1] = s[i].a - s[i].b,
    s[i].c[2] = 1ll * s[i].a * s[i].b,
    sta[(i - 1) * 3 + 1] = s[i].c[0],
    sta[(i - 1) * 3 + 2] = s[i].c[1], sta[(i - 1) * 3 + 3] = s[i].c[2];
  }
  qsort(sta+1, (n*3), sizeof(ll), cmpLL);
  cnt = unique(sta+1, n*3);
  for(int i = 1; i <= n; i++)
    for(int j = 0; j < 3; j++){
        int t = lower_bound(sta+1, cnt, s[i].c[j])+1;
        insert(i, t + n);
        insert(t + n, i);
      }
    for(int i = 1; i <= n; i++){
      memset(vis, 0, sizeof (int) * (cnt + n + 2));
      if(find (i))
        ans++;
      else
        break;
    }
  if (ans == n){
    for (int i = 1; i <= cnt; i++)
      if (mat[i + n]){
        for (int j = 0; j < 3; j++)
          if (s[mat[i + n]].c[j] == sta[i]){
            q[++tp].a = s[mat[i + n]].a;
            q[tp].b   = s[mat[i + n]].b;
            q[tp].c   = sta[i];
            q[tp].opt = j;
            q[tp].id  = mat[i + n];
            break;
          }
      }
    qsort(q+1, tp, sizeof(Ans), cmp);
    for(int i = 1; i <= tp; i++){
      if(q[i].opt == 0)
        printf ("%d + %d = %lld\n", q[i].a, q[i].b, q[i].c);
      if(q[i].opt == 1)
        printf ("%d - %d = %lld\n", q[i].a, q[i].b, q[i].c);
      if(q[i].opt == 2)
        printf ("%d * %d = %lld\n", q[i].a, q[i].b, q[i].c);
    }
  }
  else
    puts("impossible");
  return 0;
}
