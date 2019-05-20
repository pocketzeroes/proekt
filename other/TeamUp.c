#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
//////////////////
enum{ N  = 1500010  };
enum{ inf= 100000000};
int n,m,p,i,j,x,size[N],g[N],G[N],v[N],nxt[N],ed,a[N],son[N];
int from[N],father[N];
int st[N],en[N],dfn;
int ans;
int cnt;
int f[N];
bool vis[N];
vec fin[300010];

int cmp(const void*pa, const void*pb){
  int*x=(int*)pa;
  int*y=(int*)pb;
  return(size[*x]>size[*y])?-1:1;
}
inline void add(int*x, int y){
  v[++ed] = y;
  nxt[ed] = *x;
 *x = ed;
}
void dfs(int x){
  for(int i=son[x];i;i=nxt[i])
    dfs(v[i]);
  for(int i=g[x];i;i=nxt[i]){
    if(!vis[v[i]]){
      from[++dfn]=x;
      vis[v[i]]=1;
    }
  }
  en[x]=dfn;
}
int ask(int x){
  if(!x)
    return 0;
  if(f[x]==x){
    if(G[x])
      return x;
    f[x]=father[x];
  }
  return f[x]=ask(f[x]);
}
void solve(){
  while(1){
    int now=1;
    while(1){
      x=ask(from[now]);
      if(!x)
        return;
      int y=v[G[x]];
      G[x]=nxt[G[x]];
      fin[ans+1].ptr = pushback(fin[ans+1].ptr, &fin[ans+1].sz, y);
      now=en[x]+1;
      if(now>n)
        break;
    }
    ans++;
  }
}
int main(){
  scanf("%d%d%d",&n,&m,&p);
  for(i=1;i<=m;i++){
    scanf("%d",&size[i]);
    for(j=0;j<size[i];j++){
      scanf("%d",&x);
      add(&g[i],x);
    }
  }
  for(i=1;i<=p;i++){
    scanf("%d",&x);
    add(&G[x],i);
  }
  for(i=1;i<=m;i++)
    a[i]=i;
  qsort(a+1, m, sizeof(int), cmp);
  for(i=1;i<=m;i++){
    x=a[i];
    father[x]=from[v[g[x]]];
    for(j=g[x];j;j=nxt[j]){
      from[v[j]]=x;
    }
  }
  for(i=1;i<=n;i++)
    if(!from[i])
      return puts("0"),0;
  for(i=1;i<=m;i++)
    if(father[i])
      add(&son[father[i]],i);
  for(i=1;i<=m;i++)
    if(!father[i])
      dfs(i);
  for(i=1;i<=m;i++)
    f[i]=i;
  solve();
  printf("%d\n",ans);
  for(i=1;i<=ans;i++){
    int t=fin[i].sz;
    printf("%d",t);
    for(int j=0;j<t;j++)
      printf(" %d", fin[i].ptr[j]);
    puts("");
  }
  return 0;
}
