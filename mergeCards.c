#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

double rate[5005][5005];

int main(){
    rate[2][1]=1;
    rate[2][2]=1;
    for(int i=3;i<=5000;i++){
        for(int j=2;j<i;j++){
            rate[i][j]=(j-1)*rate[i-1][j-1]+(i-j)*rate[i-1][j];
            rate[i][j]+=2;
            rate[i][j]/=i-1;
        }
        rate[i][1]=rate[i][i]=rate[i-1][1]+1.0f/(i-1);
    }
    int T;
    scanf("%d", &T);
    int cas=1;
    while(T--){
        int n;
        scanf("%d", &n);
        double ans=0;
        for(int i=0; i<n; i++){
            int tem;
            scanf("%d", &tem);
            ans += rate[n][i+1]*tem;
        }
        printf("Case #%d: %lf\n", cas++, ans);
    }
    return 0;
}
