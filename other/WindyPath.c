#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ typeof(a) tp; tp = a; a = b; b = tp; }while(0)
enum{ maxn = 105};
#define INF 0x3f3f3f3f
#define eps 1e-8
typedef long long ll;

int n,ans[maxn];
char s[maxn];
typedef struct node
{
    int x,y;
}node;
node e[maxn];
node newnode(int x, int y){
    return(node){x,y};
}
int cmpN(node a,node b){
  if(a.x != b.x) return(a.x < b.x)?-1:1;
  if(a.y != b.y) return(a.y < b.y)?-1:1;
  return 0;
}
node opSub(node a, node b){
    return newnode(a.x-b.x,a.y-b.y);
}
int  opMul(node a, node b){
    return a.x*b.y-a.y*b.x;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&e[i].x,&e[i].y);
        ans[i]=i;
    }
    int tmp=1;
    for(int i=2;i<=n;i++){
        if(cmpN(e[i], e[tmp])<0)
            tmp=i;
    }
    swap(e[1], e[tmp]);
    swap(ans[1],ans[tmp]);
    scanf("%s",s+2);
    for(int i=2;i<n;i++){
        int k=i,cnt=(s[i]=='L'?1:-1);
        for(int j=i+1;j<=n;j++){
            if(opMul(opSub(e[k],e[i-1]),opSub(e[j],e[i-1])) * cnt < 0)
                k=j;
        }
        swap(e[i],e[k]);
        swap(ans[i],ans[k]);
    }
    for(int i=1;i<=n;i++)
        printf(i==n?"%d\n":"%d ",ans[i]);
    return 0;
}
