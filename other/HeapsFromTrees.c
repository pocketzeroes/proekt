#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b ); }
enum{ N=200010,M=N*20};
int n,i,x,g[N],nxt[N],size[N],son[N],a[N],b[N],q[N],cnt;
int l[M],r[M],v[M],tag[M],root[N];
int rub[M],cur;

void clear(int x){
  if(!x)return;
  clear(l[x]);
  clear(r[x]);
  rub[++cur]=x;
}
inline int newnode(){
  int x=rub[cur--];
  l[x]=r[x]=v[x]=tag[x]=0;
  return x;
}
inline void tag1(int x, int p){
  if(!x)return;
  tag[x]+=p;
  v[x]+=p;
}
inline void pb(int x){
  if(tag[x])tag1(l[x],tag[x]),tag1(r[x],tag[x]),tag[x]=0;
}
inline void up(int x){
  v[x] = fmax(v[l[x]], v[r[x]]);
}
void ins(int*x, int a, int b, int c, int d){
  if(! *x)
    *x = newnode();
  pb(*x);
  if(a==b){
    v[*x] = fmax(v[*x],d);
    return;
  }
  int mid=(a+b)>>1;
  if(c<=mid)
    ins(&l[*x],a,mid,c,d);
  else
    ins(&r[*x],mid+1,b,c,d);
  up(*x);
}
int ask(int x, int a, int b, int c, int d){
  if(!x)
    return 0;
  if(c<=a&&b<=d)
    return v[x];
  pb(x);
  int mid=(a+b)>>1,t=0;
  if(c<=mid)
    t=ask(l[x],a,mid,c,d);
  if(d>mid)
    t = fmax(t,ask(r[x],mid+1,b,c,d));
  return t;
}
void add(int x, int a, int b, int c, int d, int p){
  if(!x)return;
  if(c<=a&&b<=d){tag1(x,p);return;}
  pb(x);
  int mid=(a+b)>>1;
  if(c<=mid)add(l[x],a,mid,c,d,p);
  if(d>mid)add(r[x],mid+1,b,c,d,p);
  up(x);
}
inline int lower(int x){
  int l=1,r=n,mid,t;
  while(l<=r)if(b[mid=(l+r)>>1]<=x)l=(t=mid)+1;else r=mid-1;
  return t;
}
void dfs(int x){
  size[x]=1;
  for(int i=g[x];i;i=nxt[i]){
    dfs(i);
    size[x]+=size[i];
    if(size[i]>size[son[x]])son[x]=i;
  }
}
void go(int x){
  q[++cnt]=a[x];
  for(int i=g[x];i;i=nxt[i])go(i);
}
void merge(int x, int y){
  cnt=0;
  go(y);
  qsort(q+1, cnt, sizeof(int), cmp);
  q[cnt+1]=n+1;
  static int A[N],
             B[N];
  for(int i=1;i<=cnt;i++){
    int o=q[i];
    A[i]=ask(root[y],1,n,o,o);
    B[i]=ask(root[x],1,n,1,o);
  }
  for(int i=1,t=0;i<=cnt;i++){
    int o=q[i];
    t = fmax(t,A[i]);
    if(o!=q[i+1])
      add(root[x],1,n,o,q[i+1]-1,t);
  }
  clear(root[y]);
  for(int i=1;i<=cnt;i++){
    ins(&root[x],1,n,q[i],A[i]+B[i]);
  }
}
void dfs2(int x){
  if(son[x]){
    dfs2(son[x]);
    root[x]=root[son[x]];
  }
  for(int i=g[x];i;i=nxt[i])if(i!=son[x]){
    dfs2(i);
    merge(x,i);
  }
  int o=0;
  if(a[x]>1)o=ask(root[x],1,n,1,a[x]-1);
  ins(&root[x],1,n,a[x],o+1);
}
int main(){
  cur=M-1;
  for(i=1;i<=cur;i++)rub[i]=i;
  scanf("%d",&n);
  for(i=1;i<=n;i++){
    scanf("%d%d",&a[i],&x);
    if(x){
      nxt[i]=g[x];
      g[x]=i;
    }
    b[i]=a[i];
  }
  qsort(b+1, n, sizeof(int), cmp);
  for(i=1; i<=n; i++)
    a[i] = lower(a[i]);
  dfs (1);
  dfs2(1);
  printf("%d", ask(root[1], 1, n, 1, n));
  return 0;
}
