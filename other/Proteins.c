#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
////////////////////////////

int main(){
    static int dp[1005][1005]; dfill(dp, 1005, 1005, (int)1e9);
    int k;
    scanf("%d", &k);
    char*s=getstr();
    int n = strlen(s);
    dp[0][0]=0;
    for(int i=0; i<n; i++){
        fill(dp[i+1], n+1, (int)1e9);
        for(int v=1; v<=i+1; v++){
            int match;
            if(s[i]=='C')
                continue;
            else if(s[i]=='A')
                dp[i+1][v]=fmin(dp[i+1][v],dp[i][v-1]+2);
            else if(s[i]=='T'){
                dp[i+1][v]=fmin(dp[i+1][v],dp[i][v-1]+2);
                if(i>0&&s[i-1]=='A')
                    dp[i+1][v]=fmin(dp[i+1][v],dp[i-1][v-1]+1);
            }
            else{
                dp[i+1][v]=fmin(dp[i+1][v],dp[i][v-1]+2);
                if(i>=2&&s[i-1]=='T'&&s[i-2]=='A')
                    dp[i+1][v]=fmin(dp[i+1][v],dp[i-2][v-1]);
                if(i>=1&&s[i-1]=='T')
                    dp[i+1][v]=fmin(dp[i+1][v],dp[i-1][v-1]+1);
                if(i>=1&&s[i-1]=='A')
                    dp[i+1][v]=fmin(dp[i+1][v],dp[i-1][v-1]+1);
            }
        }
        for(int v=0;v<=i;v++)
            for(int le=1;le<=fmin(i+1,3);le++)
                dp[i+1][v]=fmin(dp[i+1][v],dp[i+1-le][v]+3-le);
    }
    int ans=(int)1e9;
    for(int le=0;le<=n;le++)
        for(int v=0;v<=fmin(k,n);v++){
            ans=fmin(ans,dp[le][v]+3*(k-v));
        }
    printf("%d\n", ans);
    return 0;
}
