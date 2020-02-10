#pragma GCC optimize "-O3"
#include<stdio.h>
enum{N=100010};
int k,tot,i,f[N],c[N],g[N];

int solve(int k, int o){
  int x=++tot;
  f[x]=o;
  if(k<=2){
    int y=++tot;
    f[y]=x;
    c[y]=1;
    g[x]=1;
    c[x]=3-k;
    return g[x]=1;
  }
  g[x]=solve(k/2,x)+solve(2,x);
  c[x]=g[x]+(k%2==0);
  return g[x];
}
int main(){
  scanf("%d", &k);
  solve(k, 0);
  printf("%d\n", tot);
  for(i=2;i<=tot;i++)
    printf("%d%c",f[i],i<tot?' ':'\n');
  for(i=1;i<=tot;i++)
    printf("%d%c",c[i],i<tot?' ':'\n');
  return 0;
}
