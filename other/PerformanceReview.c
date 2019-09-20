#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
enum{ N=100010};
int n,i,x,a[N],b[N],q[N],g[N],nxt[N],root,j,st[N],en[N],dfn;
int flag[N];
ll bit[N],ans[N];

int cmp(const void*pa, const void*pb){
  int*x=(int*)pa;
  int*y=(int*)pb;
  return(a[*x] < a[*y])?-1:1;
}
inline void add(int x,int y){
  flag[y]=1;
  nxt[y]=g[x];
  g[x]=y;
}
void dfs(int x){
  st[x]=++dfn;
  for(int i=g[x];i;i=nxt[i])
    dfs(i);
  en[x]=dfn;
}
inline void modify(int x,int p){
  for(;x<=n;x+=x&-x)
    bit[x]+=p;
}
inline ll ask(int x){
  ll t=0;
  for(;x;x-=x&-x)
    t+=bit[x];
  return t;
}
int main(){
  scanf("%d",&n);
  for(i=1;i<=n;i++){
    scanf("%d%d%d",&x,&a[i],&b[i]);
    if(x>0)
      add(x,i);
    else
      root=i;
  }
  for(i=1;i<=n;i++)
    if(!flag[i])
      dfs(i);
  for(i=1;i<=n;i++)
    q[i]=i;
  qsort(q+1, n, sizeof(int), cmp);
  for(i=1;i<=n;i=j){
    for(j=i;j<=n&&a[q[i]]==a[q[j]];j++)
      ans[q[j]] = ask(en[q[j]])-ask(st[q[j]]-1);
    for(j=i;j<=n&&a[q[i]]==a[q[j]];j++)
      modify(st[q[j]],b[q[j]]);
  }
  for(i=1;i<=n;i++)
    printf("%lld\n",ans[i]);
  return 0;
}
