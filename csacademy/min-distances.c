#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll a[105][105],
   b[105][105];
int main(){
    ll i,j,k;
    ll l,m,n,c,d,p,q,r,c2;
    ll cs=0,tc,t=1,flg,f,sm;
    while(scanf("%lld %lld", &n, &m)==2){
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                a[i][j]=b[i][j]=1000000007LL;
        for(i=0;i<m;i++){
            scanf("%lld %lld %lld", &p, &q, &d);
            a[p][q]=b[p][q]=d;
            a[q][p]=b[q][p]=d;
        }
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                for(int k=1; k<=n; k++){
                    if(a[j][i]+a[i][k]<a[j][k]){
                        a[j][k]=a[j][i]+a[i][k];
                    }
                }
            }
        }
        f=0;
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                if(b[i][j]!=1000000007LL){
                    if(a[i][j]<b[i][j]){
                        f=1;
                        break;
                    }
                }
            }
            if(f)
                break;
        }
        if(f){
            printf("-1\n");
            return 0;
        }
        p=n*(n-1)/2;
        printf("%lld\n",p);
        for(i=1;i<=n;i++){
            for(j=i+1;j<=n;j++){
                if(b[i][j]==1000000007LL)
                    p=10000000;
                else
                    p=b[i][j];
                printf("%lld %lld %lld\n", i, j, p);
            }
        }
    }
    return 0;
}
