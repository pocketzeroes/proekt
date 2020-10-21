#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int ma[1005][1005];

int main(){
    int T;
    scanf("%d", &T);
    int cas=1;
    while(T--){
        int n;
        scanf("%d", &n);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf("%d", &ma[i][j]);
            }
        }
        long long ans=0;
        for(int i=1;i<=n;i++){
            long long cnt=0;
            for(int j=0;i+j<=n;j++){
                cnt+=ma[j+1][j+i];
            }
            ans = fmaxl(ans, cnt);
            cnt=0;
            for(int j=0; i+j<=n; j++){
                cnt+=ma[i+j][1+j];
            }
            ans = fmaxl(ans, cnt);
        }       
        printf("Case #%d: %lld\n", cas++, ans);
    }
    return 0;
}
