#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

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

typedef struct{
  int  first;
  pair second;
}trip;
trip newTrip(int a, pair b){
  trip rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpT(const void*pa, const void*pb){
  trip*a=(trip*)pa;
  trip*b=(trip*)pb;
  int diff;
  int a2nd = a->second.first ; int a3rd = a->second.second;
  int b2nd = b->second.first ; int b3rd = b->second.second;
  diff = a->first  - b->first;  if(diff!=0) return diff;
  diff = a2nd - b2nd; if(diff!=0) return diff;
  return a3rd - b3rd;
}

enum{ MAGIC = 1000};

int sub(int a, int b, int q){
  a -= b;
  if (a < 0)
    a += q;
  return a;
}
int add(int a, int b, int q){
  a += b;
  if (a >= q)
    return a - q;
  return a;
}
enum{ N =(int) 3e5};
int p    [N];
int depth[N];
int shift[N];

int getp(int v){
  if (p[v] == v)
    return v;
  return getp(p[v]);
}
int getcolor(int v){
  int color = 0;
  while (true){
    color ^= shift[v];
    if (v == p[v])
      return color;
    v = p[v];
  }
  return color;
}
pair getpr(int v){
  if (v == p[v])
    return newPair(v, shift[v]);
  pair lr = getpr(p[v]);
  return newPair(lr.first, lr.second ^ shift[v]);
}
bool unite(pair xa, pair xb){
  int x = xa.second;
  int y = xb.second;
  int a = xa.first;
  int b = xb.first;
  if (a == b)
    return false;
  if (depth[a] > depth[b])
    swap(a, b);
  p[a] = b;
  depth[b] = max(depth[b], depth[a] + 1);
  if (x == y)
    shift[a] ^= 1;
  return true;
}
enum{ INF =(int) 1e6 + 1};
int conn[N];

int main(){
  int n, m;
  scanf("%d %d", &n, &m);
  trip v[m];
  for(int i = 0; i < n; ++i){
    p   [i] = i;
    conn[i] = INF;
  }
  for(int i = 0; i < m; ++i){
    int a, b, w;
    scanf("%d %d %d", &a, &b, &w);
    --a, --b;
    v[i] = newTrip(w, newPair(a, b));
  }
  qsort(v, m, sizeof(trip), cmpT);
  int answer = 2 * INF;
  for(int z=0;z<m;z++){trip x = v[z];
    int a = x.second.first;
    int b = x.second.second;
    int w = x.first;
    pair xa = getpr(a);
    pair xb = getpr(b);
    if(!unite(xa, xb)){
      if(xa.second == xb.second){
        answer = min(answer, w);
        break;
      }
      else{
        answer  = min(answer, conn[a] + w);
        answer  = min(answer, conn[b] + w);
        conn[a] = min(conn[a], w);
        conn[b] = min(conn[b], w);
      }
    }
    else{
      answer  = min(answer, conn[a] + w);
      answer  = min(answer, conn[b] + w);
      conn[a] = min(conn[a], w);
      conn[b] = min(conn[b], w);
    }
  }
  if(answer <= INF)
    printf("%d\n", answer);
  else
    puts("-1");
  return 0;
}
