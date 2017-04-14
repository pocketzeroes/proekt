#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<stdint.h>
#include<limits.h>

enum{ kMod  =(int) 1e9+7};
enum{ kMaxN =(int) 125  };
int d[kMaxN][kMaxN+1];

int main() {
    int n,k;
    scanf("%d%d", &n, &k);
    assert(n <= kMaxN);
    assert(k <= n - 2);
    assert(3 <= n);
    assert(1 <= k);
    d[3][0]=1;
    for(int i=4;i<=n;i++)
    {
        d[i][0]=1;
        for(int j=1;j<=i-3;j++)
        {
            d[i][j]=d[i-1][j]+d[i-1][j-1];
            d[i][j] %= kMod;
            for(int k=3;k<i;k++)
                for(int j2=0;j2<j;j2++) {
                    d[i][j]+=1LL*(j2?(d[k-1][j2]+d[k-1][j2-1]):d[k][0])*d[i-k+2][j-j2-1]%kMod;
                    d[i][j] %= kMod;
                }
        }
    }
    printf("%d\n",d[n][k-1]);
    return 0;
}
