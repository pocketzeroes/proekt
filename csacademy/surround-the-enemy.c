#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;


enum{ maxn = 50000  };
enum{ maxm = 2222222};
const ll  inf=(ll)1e18;
int g[maxn],to[maxm],np[maxm],cp;
int n,u,v,now,source,sink;
ll sum, cap[maxm], a[maxn];
int d[maxn],p[maxn],cur[maxn],cnt[maxn];

void add_edge(int x, int y, ll z){
  cap[cp] = z;
  to [cp] = y;
  np [cp] = g[x];
  g  [x ] = cp++;
  cap[cp] = 0;
  to [cp] = x;
  np [cp] = g[y];
  g  [y ] = cp++;
}
void init(){
  cp=2; 
  memset(g, 0, sizeof(g));
}
ll maxflow(){
    sum=0;
    for(u=1;u<=n;u++)
        cur[u]=g[u]; 
    a[u=source]=inf; 
    memset(d,0,sizeof(int)*(n+1)); 
    memset(cnt,0,sizeof(int)*(n+1)); 
    cnt[0]=n;
    while(d[source]<n){
        for(now=cur[u];now;now=np[now])
            if(cap[now]&&d[v=to[now]]+1==d[u])
                break; 
        cur[u]=now;
        if(now){
            p[v]=now;
            a[v]=cap[now]; 
            if (a[v]>a[u])
                a[v]=a[u];
            if((u=v)==sink){
                do{
                    cap[p[u]]  -=a[sink]; 
                    cap[p[u]^1]+=a[sink]; 
                    u=to[p[u]^1];
                }
                while(u!=source);
                sum+=a[sink]; 
                a[source]=inf;
            }
        }
        else{
            if(--cnt[d[u]]==0)
                break; 
            d[u]=n; 
            cur[u]=g[u];
            for(now=g[u];now;now=np[now]) 
                if(cap[now] && d[u]>d[to[now]]+1) 
                    d[u]=d[to[now]]+1;
            cnt[d[u]]++;
            if(u!=source)
                u=to[p[u]^1];
        }
    }
    return sum;
}

int row,col,xx,yy, ga[155][155];
int main(){
    scanf("%d %d %d %d", &row, &col, &xx, &yy);
    --xx, --yy;
    for(int i=0; i<row; i++)
      for(int j=0; j<col; j++)
        scanf("%d", &ga[i][j]);
    init();
    n = row * col * 2 + 1;
    source = (xx*col+yy) * 2 + 1;
    sink = row*col*2;
    for(int i=0; i<row; i++)
      for(int j=0; j<col; j++){
        ll tmp = ga[i][j] == -1 ? inf : ga[i][j];
        add_edge((i*col+j)*2, (i*col+j)*2+1, tmp);
        if(i==0 || i==row-1 || j==0 || j==col-1)
          add_edge((i*col+j)*2+1, sink, inf);
        for(int dx=-1; dx<=1; dx++)
          for(int dy=-1; dy<=1; dy++)
            if(dx!=0 || dy!=0){
              int ii = i + dx, jj = j + dy;
              if(ii>=0 && ii<row && jj>=0 && jj<col)
                add_edge((i*col+j)*2+1, (ii*col+jj)*2, inf);
            }
      }
    printf("%d\n", maxflow());
    return 0;
}
