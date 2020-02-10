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
enum{maxn=17};
enum{mod =(int)1e9+7};

ll power(ll base, ll p){
  ll ret=1;
  while(p){
    if(p&1)
      ret = ret*base%mod;
    base = base*base%mod;
    p>>=1;
  }
  return ret;
}
ll inv(ll base){
  return power(base, mod-2);
}
int n,m;
int adj[maxn][maxn];

//namespace DSU{
int p[maxn];
int tot;
void init(int n){
  tot=n;
  for(int i=0;i<n;++i)p[i]=i;
}
int pa(int x){
  if(x==p[x])
    return x;
  else
    p[x]=pa(p[x]);
  return p[x];
}
void merge(int x, int y){
  if(pa(x)!=pa(y)){
    --tot;
    p[pa(x)]=pa(y);
  }
}
bool connected(){
  return tot==1;
}
//}
enum{ maxb=1<<maxn};
int d[maxb][maxn];
inline void Add(int*x, int y){
  if(((*x)+=y)>=mod)
    (*x)-=mod;
}
inline void Addl(ll*x, ll y){
  if(((*x)+=y)>=mod)
    (*x)-=mod;
}
int rev_lb[maxb];
int id[maxn],ptr;

//namespace Matrix_tree{
ll a[maxn][maxn];
void mt_init(){
  memset(a,0,sizeof(a));
}
void add(int u, int v){
  a[u][v]-=1;
  a[v][u]-=1;
  a[u][u]+=1;
  a[v][v]+=1;
}
ll mt_solve(int n){
  //---
  //---
  //---
  ll ans = 1;
  for(int i = 0; i < n-1; ++i){
    int pick=-1;
    for(int j=i;j<n-1;++j){
      if(a[j][i]!=0){
        pick=j;
        break;
      }
    }
    if(pick==-1)
      fprintf(stderr, "assert false\n");
    for(int j=0;j<n;j++){
      swap(a[i][j], a[pick][j]);
    }
    for(int j=i+1;j<n-1;++j)
      if(a[j][i]!=0){
        ll ratio=a[j][i]*inv(a[pick][i])%mod;
        for(int k=i;k<n;++k)
          Addl(&a[j][k], mod-ratio*a[pick][k]%mod);
      }
    ans*=a[pick][i];
    ans%=mod;
  }
  return ans;
}
//}
ll solve(int bit){
  init(n);
  int start=rev_lb[bit&-bit];
  for(int i=0;i<n;++i)
    if((bit>>i)&1)
      merge(i,start);
  ptr=0;
  for(int i=0;i<n;++i)
    if(pa(i)==i)
      id[i]=ptr++;
  mt_init();
  for(int i=0;i<n;++i){
    int x=pa(i);
    for(int j=i+1; j<n; ++j)
      if(adj[i][j]){
        int y=pa(j);
        if(x!=y){
          add(id[x],id[y]);
        }
      }
  }
  ll ans = mt_solve(ptr);
  return ans;
}
int main(){
  scanf("%d%d",&n,&m);
  init(n);
  memset(adj,0,sizeof(adj));
  for(int i=0;i<m;++i){
    int u,v;
    scanf("%d%d",&u,&v);
    --u, --v;
    adj[u][v]=adj[v][u]=1;
    merge(u,v);
  }
  if(!connected()||m==n-1){
    puts("0");
    return 0;
  }
  for(int i=0;i<n;++i){
    rev_lb[1<<i]=i;
    d[1<<i][i]=1;
  }
  for(int bit=1;bit<(1<<n);++bit){
    int start=rev_lb[bit&-bit];
    for(int i=start;i<n;++i)
      if((bit>>i)&1)
        for(int j=start+1;j<n;++j)
          if(adj[i][j]&&((bit>>j)&1)==0)
            Add(&d[bit|(1<<j)][j],d[bit][i]);
  }
  int ans=0;
  const int inv2=(int)inv(2);
  for(int bit=1;bit<(1<<n);++bit){
    int cnt=0;
    int start=rev_lb[bit&-bit];
    for(int i=start+1;i<n;++i)
      if(adj[i][start]&&((bit>>i)&1)&&(bit!=((1<<start)|(1<<i))))
        Add(&cnt, d[bit][i]);
    if(cnt==0)continue;
    cnt=1ll*inv2*cnt%mod;
    //
    Add(&ans,1ll*cnt*solve(bit)%mod);
  }
  printf("%d\n", ans);
  return 0;
}






















