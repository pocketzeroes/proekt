#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{INF = 0x3f3f3f3f};

typedef struct{
    int cnt;
    int w[103],v[103];
}P;
P p[55];

int dp[55][550];

int main(){
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF){
        m++;
        memset(dp,0,sizeof(dp));
        for(int i=m;i>=1;i--){
            scanf("%d",&p[i].cnt);
            for(int j=0;j<p[i].cnt;j++)
                scanf("%d",&p[i].w[j]);
            for(int j=0;j<p[i].cnt;j++)
                scanf("%d",&p[i].v[j]);
        }
        memset(dp,-1,sizeof(dp));
        dp[0][0]=0;
        for(int i=1;i<=m;i++){
            for(int j=n;j>=0;j--){
                for(int k=0;k<p[i].cnt;k++){
                    if(j-p[i].v[k]>=0&&dp[i-1][j-p[i].v[k]]!=-1){
                        dp[i][j]=fmax(dp[i][j],dp[i-1][j-p[i].v[k]]+p[i].w[k]*p[i].v[k]);
                    }
                    if(j==p[i].v[k])
                        for(int d=p[i].v[k]-1;d>=0;d--)
                            if(dp[i-1][0]!=-1)
                                dp[i][d]=fmax(dp[i][d],dp[i-1][0]+d*p[i].w[k]);
                }
            }
        }
        int sum=0;
        for(int i=0;i<=n;i++)
            sum=fmax(dp[m][i],sum);
        if(m==1){
            printf("%d\n",sum);
            for(int i=0;i<p[m].cnt;i++)
                if(p[m].w[i]*p[m].v[i]==sum){
                    printf("%d\n",p[m].w[i]);
                    break;
                }
            continue;
        }
        printf("%d\n",dp[m][n]);
        for(int i=0;i<p[m].cnt;i++)
            if(dp[m][n]==dp[m-1][n-p[m].v[i]]+p[m].v[i]*p[m].w[i]){
                printf("%d\n",p[m].w[i]);
                break;
            }
    }
    return 0;
}
