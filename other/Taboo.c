#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

enum{ N=200010};
enum{ inf=100000000};
int n,i,j,x;
char s[N];
int tot,son[N][2],ban[N],fail[N],q[N];
int f[N],vis[N],in[N];

void ins(){
  scanf("%s",s);
  int l=strlen(s);
  int i,x=0,w;
  for(i=0;i<l;i++){
    w=s[i]-'0';
    if(!son[x][w])
      son[x][w]=++tot;
    x=son[x][w];
  }
  ban[x]=1;
}
void make(){
  int h=1,t=0,i,j,x;
  fail[0]=-1;
  for(i=0;i<2;i++)
    if(son[0][i])
      q[++t]=son[0][i];
  while(h<=t){
    for(x=q[h++],i=0;i<2;i++){
      if(son[x][i]){
        fail[son[x][i]]=son[fail[x]][i];
        q[++t]=son[x][i];
        ban[son[x][i]]|=ban[fail[son[x][i]]];
      }
      else{
        son[x][i]=son[fail[x]][i];
      }
    }
  }
}
int dp(int x){
  if(in[x]){
    puts("-1");
    exit(0);
  }
  if(vis[x])
    return f[x];
  in [x]=1;
  vis[x]=1;
  f  [x]=-inf;
  if(!ban[x]){
    f[x]=0;
    for(int i=0;i<2;i++){
      f[x]=max(f[x],dp(son[x][i])+1);
    }
  }
  in[x]=0;
  return f[x];
}
int main(){
  scanf("%d",&n);
  while(n--)
    ins();
  make();
  dp(0);
  for(x=0,i=1;i<=f[0];i++){
    for(int j=0;j<2;j++){
      if(f[son[x][j]]+1==f[x]){
        x=son[x][j];
        printf("%d",j);
        break;
      }
    }
  }
  puts("");
  return 0;
}
