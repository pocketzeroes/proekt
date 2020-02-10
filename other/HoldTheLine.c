#pragma GCC optimize "-O3" // https://codeforces.com/gym/102452/problem/H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int lower_bound(int*a, int n, int x){
  int l = 0;
  int h = n;
  while (l < h) {
    int mid = (l + h) / 2;
    if (x <= a[mid]) 
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}
int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}

enum{N=500010,M=1000010,K=2100005,inf=~0U>>1};
int Case,n,m,i,j,op,x,y,z,pool[M],cp,e[M][4],val[N],ap[N];
int pos[M],st[K],en[K],q[11000005],cq,cnt[M];
int g[N],nxt[M],ans[M],L,H,T,ANS,TMP;

void build(int x, int a, int b){
  st[x]=cq+1;
  en[x]=cq;
  cq+=cnt[b]-cnt[a-1];
  if(a==b){
    pos[a]=x;
    return;
  }
  int mid=(a+b)>>1;
  build(x<<1, a, mid),
  build(x<<1|1,mid+1,b);
}
void ins  (int x){
  int y=ap[x];
  if(y>m)
    return;
  for(int o=pos[val[x]];o;o>>=1){
    int S=st[o],T=en[o];
    while(S<=T&&ap[q[T]]>=y)
      T--;
    q[++T]=x;
    en[o]=T;
  }
}
bool check(int x){
  int l=st[x],r=en[x],mid;
  while(l<=r){
    mid=(l+r)>>1;
    if(q[mid]>=L&&ap[q[mid]]<=T)
      return 1;
    if(q[mid]<L)
      l=mid+1;
    else
      r=mid-1;
  }
  return 0;
}
void askl (int x, int a, int b){
  if(TMP||st[x]>en[x])
    return;
  if(b<=H){
    if(!check(x))
      return;
    if(a==b){
      TMP=a;
      return;
    }
  }
  int mid=(a+b)>>1;
  if(H>mid)
    askl(x<<1|1,mid+1,b);
  askl(x<<1,a,mid);
}
void askr (int x, int a, int b){
  if(TMP||st[x]>en[x])
    return;
  if(H<=a){
    if(!check(x))
      return;
    if(a==b){
      TMP=a;
      return;
    }
  }
  int mid=(a+b)>>1;
  if(H<=mid)
    askr(x<<1,a,mid);
  askr(x<<1|1,mid+1,b);
}
void query(int x){
  L=e[x][1];
  H=e[x][3];
  T=x;
  ANS=inf;
  TMP=0;
  askl(1,1,cp);
  if(TMP)
    ANS=pool[H]-pool[TMP];
  TMP=0;
  askr(1,1,cp);
  if(TMP)
    ANS = fmin(ANS, pool[TMP]-pool[H]);
  ans[x] = ANS<inf?ANS:-1;
}
int main(){
  scanf("%d", &Case);
  while(Case--){
    scanf("%d %d", &n, &m);
    for(i=1;i<=n;i++)
      ap[i]=m+1,g[i]=0;
    for(i=1;i<=m;i++){
      scanf("%d %d", &op, &x);
      if(op==0)
        scanf("%d", &z);
      else 
        scanf("%d %d", &y, &z);
      e[i][0]=op;
      e[i][1]=x;
      e[i][2]=y;
      e[i][3]=z;
      pool[i]=z;
    }
    qsort(pool+1, m, sizeof(int), cmp);
    for(cp=0,i=1;i<=m;i++)
      if(pool[i]>pool[i-1])
        pool[++cp]=pool[i];
    for(i=1;i<=cp;i++)
      cnt[i]=0;
    for(i=1;i<=m;i++){
      e[i][3] = lower_bound(pool+1, cp, e[i][3])+1;
      x=e[i][1];
      y=e[i][2];
      z=e[i][3];
      if(e[i][0]==0){
        val[x]=z;
        ap [x]=i;
        cnt[z]++;
      }
      else{
        nxt[i]=g[y];
        g  [y]=i;
      }
    }
    for(i=1;i<=cp;i++)
      cnt[i]+=cnt[i-1];
    cq=0;
    build(1, 1, cp);
    for(i=1; i<=n; i++){
      ins(i);
      for(j=g[i];j;j=nxt[j])
        query(j);
    }
    for(i=1; i<=m; i++)
      if(e[i][0]==1)
        printf("%d\n", ans[i]);
  }
  return 0;
}
