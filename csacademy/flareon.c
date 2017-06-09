#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

typedef struct pairS{
  ll first;
  ll second;
}Pair;
Pair newPair(ll a, ll b){
  Pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll *pushback(ll *array, int *size, ll value) {
  ll *output = resizeArray(array, ll, *size + 1);
  output[(*size)++] = value;
  return output;
}
Pair *pushbackP(Pair *array, int *size, Pair value) {
  Pair *output = resizeArray(array, Pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct vecpS {
	Pair*ptr;
	int sz;
}vecp;
vecp newVecP() {
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef struct vecS {
	ll*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
//////

typedef Pair ii;
typedef vec vi;

vi   adj    [200001];
bool used   [200001];
ll   ans    [200001];
int  subsize[200001];
vec  queries[200001];
ll   ma     [200001];
ll   matotal;
int  maxh;
ll   masiz;
vi   tt     [200001];
ii   dph    [200001];


void calcsiz(int u, int p)
{
  subsize[u]=1;
  for(int i=0;i<adj[u].sz; i++)
  {
    int v=adj[u].ptr[i];
    if(v==p||used[v]) continue;
    calcsiz(v,u);
    subsize[u]+=subsize[v];
  }
}
int centroid(int u, int p, int c)
{
  for(int i=0;i<adj[u].sz; i++)
  {
    int v=adj[u].ptr[i];
    if(v==p||used[v]) continue;
    if(subsize[v]*2>subsize[c]) return centroid(v,u,c);
  }
  return u;
}
void collectqueries(int u, int p, int cent, int rt, int h)
{
  for(int i = 0; i < queries[u].sz; i++)
  {
    int v = max(queries[u].ptr[i]-h,0);
    if(v>0)
    {
      if(rt!=-1||p==cent)
      {
        if(rt!=-1) 
          tt[rt].ptr = pushback(tt[rt].ptr, &tt[rt].sz , v);
        else 
          tt[u ].ptr = pushback(tt[u ].ptr, &tt[u ].sz , v);
      }
      if(v<=maxh) 
        ma[v]++;
      masiz++;
      matotal+=v;
    }
  }
  for(int i=0;i<adj[u].sz; i++)
  {
    int v=adj[u].ptr[i];
    if(v==p||used[v]) 
      continue;
    if(p==cent) 
      collectqueries(v,u,cent,u,h+1);
    else 
      collectqueries(v,u,cent,rt,h+1);
  }
}
void push(int u, int p, int h)
{
  if(dph[h].first<0)
  {
    dph[h] = dph[h-1];
    if(h==1) 
      dph[h]=newPair(0,0);
    if(ma[h]>0)
    {
      ll tmp=ma[h];
      dph[h].first +=tmp*h;
      dph[h].second+=tmp;
    }
  }
  maxh=max(maxh,h);
  ans[u] += matotal - dph[h].first - (ll)h * (masiz - dph[h].second);
  for(int i = 0; i < adj[u].sz; i++)
  {
    int v=adj[u].ptr[i];
    if(v==p||used[v]) 
      continue;
    push(v,u,h+1);
  }
}
void cmaxh(int u, int p, int h)
{
  maxh = max(maxh, h);
  for(int i=0;i<adj[u].sz; i++)
  {
    int v = adj[u].ptr[i];
    if(v==p || used[v]) 
      continue;
    cmaxh(v, u, h+1);
  }
}
void solve(int u)
{
  maxh=0;
  cmaxh(u,-1, 0);
  collectqueries(u,-1,u, -1, 0);
  ans[u]+=matotal;
  int ori=maxh;
  for(int i = 0; i < adj[u].sz; i++)
  {
    int v = adj[u].ptr[i];
    if(used[v]) continue;
    for(int j=0;j<tt[v].sz; j++)
    {
      int V = tt[v].ptr[j];
      if(V>0)
      {
        if(V<=ori)
          ma[V]--;
        matotal-=V;
        masiz--;
      }
    }
    maxh=0;
    push(v,u , 1);
    for(int i=0;i<=maxh;i++)
      dph[i] = newPair(-1,-1);
    for(int j=0;j<tt[v].sz; j++)
    {
      int V = tt[v].ptr[j];
      if(V>0)
      {
        if(V<=ori)
          ma[V]++;
        matotal+=V;
        masiz++;
      }
    }
  }
  for(int i=0;i<=ori;i++)
    ma[i]=0;
  matotal=0;
  masiz=0;
  for(int i = 0; i < adj[u].sz; i++)
  {
    int v = adj[u].ptr[i];
    if(used[v]) continue;
    tt[v].sz=0;
  }
}
void solveall(int u)
{
  calcsiz(u,-1);
  int cent=centroid(u,-1,u);
  solve(cent);
  used[cent]=1;
  for(int i=0;i<adj[cent].sz; i++)
  {
    int v=adj[cent].ptr[i];
    if(used[v])
      continue;
    solveall(v);
  }
}
int main()
{
  int n,m;
  scanf("%d %d", &n, &m);
  for(int i=0;i<=n;i++)
    dph[i] = newPair(-1,-1);
  for(int i=1;i<n;i++)
  {
    int p;
    scanf("%d", &p);
    p--;
    adj[p].ptr = pushback(adj[p].ptr, &adj[p].sz ,i);
    adj[i].ptr = pushback(adj[i].ptr, &adj[i].sz ,p);
  }
  for(int i=0;i<m;i++)
  {
    int u,v;
    scanf("%d %d", &u, &v);
    u--;
    queries[u].ptr = pushback(queries[u].ptr, &queries[u].sz ,v);
  }
  solveall(0);
  for(int i=0;i<n;i++)
    printf("%lld\n", ans[i]);
}
























































