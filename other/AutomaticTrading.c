#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
enum{ N=100010,A=1000000007,B=1000000009};
int n,m,i,x,y;char a[N];ll pa[N],pb[N],f[N],g[N];

inline ll hasha(int l,int r){return((f[r]-1LL*f[l-1]*pa[r-l+1]%A)%A+A)%A;}
inline ll hashb(int l,int r){return((g[r]-1LL*g[l-1]*pb[r-l+1]%B)%B+B)%B;}

inline int ask(int x,int y){
  int l=1,r=n-y+1,mid,t=0;
  while(l<=r){
    mid=(l+r)>>1;
    if(hasha(x,x+mid-1)==hasha(y,y+mid-1)&&hashb(x,x+mid-1)==hashb(y,y+mid-1))l=(t=mid)+1;else r=mid-1;
  }
  return t;
}
int main(){
  for(pa[0]=i=1;i<N;i++)pa[i]=233LL*pa[i-1]%A;
  for(pb[0]=i=1;i<N;i++)pb[i]=233LL*pb[i-1]%B;
  while(~scanf("%s",a+1)){
    if(a[1]=='*')
      return 0;
    n=strlen(a+1);
    for(i=1;i<=n;i++)f[i]=(233LL*f[i-1]+a[i])%A;
    for(i=1;i<=n;i++)g[i]=(233LL*g[i-1]+a[i])%B;
    scanf("%d",&m);
    while(m--)
      scanf("%d%d",&x,&y),printf("%d\n",ask(x+1,y+1));
  }
  return 0;
}
