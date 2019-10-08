#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ N = 105};
int n;
double pr[N];
double dp[N][N];

int cmpDbl(const void*pb, const void*pa){//rev
  double*a =(double*)pa;
  double*b =(double*)pb;
  return(*a < *b)?-1:1;
}
double solve(int p){
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for(int i = 1; i <= p; i++){
        for(int j = 0; j < N; j++){
            if(j - 1 >= 0)
                dp[i][j] += dp[i-1][j-1] * pr[i];
            dp[i][j] += dp[i-1][j] * (1 - pr[i]);
        }
    }
    double res = 0;
    for(int i = 1; i <= p; i++){
        res += dp[p][i] * pow(i, (double)i / p);
    }
    return res;
}
int main(){
    scanf("%d", &n);
    for(int i=1; i<=n; i++){
        scanf("%lf", &pr[i]);
        pr[i] /= 100;
    }
    qsort(pr+1, n, sizeof(double), cmpDbl);//rev
    double res=0.;
    for(int p=1; p<=n; p++)
        res = fmax(res, solve(p));
    printf("%.10lf\n", res);
    return 0;
}
