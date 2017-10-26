#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#include<stdbool.h>
#ifdef _WIN32
  #define inline static
#endif
#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}
int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

#define inf 1000000000
#define mid ((l+r)>>1)
typedef struct tree_s{
  int ans,l,r;
}tree;
tree t[30000005];
int n,m,cnt,Cnt;
int rt[500005],
    Rt[500005],
    to[3000005],
    nex[3000005],
    head[500005],
    a [500005];
int ls[500005],lcnt;

inline int read(){
    int ret=0;
    char c=getchar();
    while((c>'9')||(c<'0'))
      c=getchar();
    while((c>='0')&&(c<='9'))
      ret=(ret<<1)+(ret<<3)+c-'0',c=getchar();
    return ret;
}
inline int find(int k){
  int l=0,r=lcnt+1;
  while(r-l>1){
    int midd=(l+r)>>1;
    if(ls[midd]>=k)
      r=midd;
    else 
      l=midd;
  }
  return r;
}
void ins(int u,int v){
  to[++Cnt]=v;
  nex[Cnt]=head[u];
  head[u]=Cnt;
}
inline int Abs(int k){
  return k>0?k:-k;
}
void add(int*rt, int Rt, int l, int r, int k, int x, int p){
  if(!*rt)
    *rt = ++cnt;
  if(l==r){
    if(p)
      t[*rt].ans=min(t[Rt].ans,x);
    else 
      t[*rt].ans=max(t[Rt].ans,x);
    return;
  }
  if(k<=mid){
    t[*rt].r=t[Rt].r;
    add(&t[*rt].l,t[Rt].l,l,mid,k,x,p);
  }
  else{
    t[*rt].l=t[Rt].l;
    add(&t[*rt].r,t[Rt].r,mid+1,r,k,x,p);
  }
  if(p)
    t[*rt].ans=min(t[t[*rt].l].ans,t[t[*rt].r].ans);
  else 
    t[*rt].ans=max(t[t[*rt].l].ans,t[t[*rt].r].ans);
}
//inline 
int query(int rt,int l,int r,int L,int R,int p){
  if((L<=l)&&(R>=r))
    return t[rt].ans;
  int ans;
  if(p)
    ans=inf;
  else 
    ans=0;
  if(L<=mid){
    if(p)
      ans=min(ans,query(t[rt].l,l,mid,L,R,p));
    else 
      ans=max(ans,query(t[rt].l,l,mid,L,R,p));
  }
  if(R>mid){
    if(p)
      ans=min(ans,query(t[rt].r,mid+1,r,L,R,p));
    else 
      ans=max(ans,query(t[rt].r,mid+1,r,L,R,p));    
  }
  return ans;
}
int main(){
  n=read(); 
  m=read();
  for(int i=1;i<=n;i++)
    a[i]=ls[i]=read();
  qsort(ls+1, n, sizeof(int), cmp);
  lcnt=1;
  for(int i=2;i<=n;i++)
    if(ls[i]!=ls[i-1])
      ls[++lcnt]=ls[i];
  for(int i=1;i<=n;i++)
    a[i]=find(a[i]);
  for(int i=1;i<=n;i++)
    add(&rt[i],rt[i-1],1,lcnt,a[i],i,0);
  for(int i=1;i<=n;i++){
    int p=inf,now=i-1;
    while(true){
      int L=find(ls[a[i]]-p);
      int tmp=query(rt[now],1,lcnt,L,a[i],0);
      if(tmp==0)
        break;
      ins(i,tmp);
      if(a[i]==a[tmp])
        break;
      p=(ls[a[i]]-ls[a[tmp]]-1)/2;
      now=tmp-1;
    }
  }
  for(int i=1;i<=n;i++){
    int p=inf,now=i-1;
    while(true){
      int R=find(ls[a[i]]+p+1)-1;
      int tmp=query(rt[now],1,lcnt,a[i]+1,R,0);
      if(tmp==0)
        break;
      ins(i,tmp);
      p=(ls[a[tmp]]-ls[a[i]]-1)/2;
      now=tmp-1;
    }
  }
  t[0].ans=inf;
  for(int i=1;i<=n;i++){
    int last=Rt[i-1];
    for(int j=head[i];j;j=nex[j]){
      Rt[i]=0;
      add(&Rt[i],last,1,n,to[j],Abs(ls[a[i]]-ls[a[to[j]]]),1);
      last=Rt[i];
    }
  }
  int ans = 0;
  while(m--){
    int l=read(),r=read();
    l = 1 + (l+ans)%n;
    r = 1 + (r+ans)%n;
    if(l>r)
      swap(l,r);
    printf("%d\n", ans = query(Rt[r],1,n,l,r,1));
  }
  return 0;
}

















