#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
inline ll max(ll a, ll b){return a>b?a:b;}
 
int N;
int A[3003], D[3003][3003], E[3003][3003];
ll S[3003];
 
int main(){
    scanf("%d", &N);
    for (int i=1;i<=N;i++)
        scanf("%d", A+i), S[i] = S[i-1] + A[i];
    for (int i=1;i<=N;i++){
        D[1][i] = 1;
        for (int j=i,k=i-1;j>1;j--){
            if (k >= j) k = j-1;
            while (k > 0 && S[j-1] - S[k-1] <= S[i] - S[j-1]) k--;
            if (E[k+1][j-1]) D[j][i] = E[k+1][j-1] + 1;
        }
        for (int j=i;j;j--) E[j][i] = max(D[j][i], E[j+1][i]);
    }
    int ans = 0;
    for (int i=1;i<=N;i++) ans = max(ans, D[i][N]);
    printf("%d\n", ans);
}
