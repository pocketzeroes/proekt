#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define X first
#define Y second
#define mkp make_pair
#define lson (o<<1)
#define rson ((o<<1)|1)
#define mid (l+(r-l)/2)
#define sz() size()
#define pb(v) push_back(v)
#define all(o) (o).begin(),(o).end()
#define clr(a,v) memset(a,v,sizeof(a))
#define bug(a) cout<<#a<<" = "<<a<<endl
#define rep(i,a,b) for(int i=a;i<(b);i++)
enum{maxn=111};
int vis[maxn];
int arr[maxn][maxn];
int n,m,k;

int main(){
    while(scanf("%d%d%d",&n,&m,&k)==3){
        rep(i,1,n+1){
            rep(j,1,m+1){
                scanf("%d",&arr[i][j]);
            }
        }
        clr(vis,0);
        int cnt=0,su=1;
        rep(j,1,m+1){
            if(vis[j]) 
                continue;
            rep(i,1,n+1){
                if(arr[i][j]==0){
                    vis[j]=1;
                    cnt++;
                    rep(k,1,m+1){
                        if(arr[i][k]==0)
                            vis[k]=1;
                    }
                    break;
                }
            }
            if(!vis[j]){
                su=0;
                break;
            }
        }
        if(!su||cnt>k)
            puts("no");
        else
            puts("yes");
    }
    return 0;
}
