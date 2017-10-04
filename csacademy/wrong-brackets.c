#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
enum{ MOD  =(int) 1e9+7};
enum{ SIZE =      62   };
ll C[SIZE][SIZE];
char an[SIZE];
ll dp[SIZE][SIZE];

ll cal(int N){
    memset((dp), 0, sizeof((dp)));
    dp[0][0]=1;
    int L=0,R=0;
    for (int i = 0; i < (2*N); ++i){
        if(an[i]=='(')L++;
        else if(an[i]==')')R++;
        for (int j = 0; j < (N+1); ++j){
            if(an[i]=='('){
                dp[i+1][j+1]+=dp[i][j];
            }
            else if(an[i]==')'){
                if(j)dp[i+1][j-1]+=dp[i][j];
            }
            else{
                dp[i+1][j+1]+=dp[i][j];
                if(j)dp[i+1][j-1]+=dp[i][j];
            }
        }
    }
    return C[2*N-L-R][N-L]-dp[2*N][0];
}
int main(){
    for (int i = 0; i < (SIZE); ++i){
        C[i][0]=1;
        for (int j = (1); j < (i+1); ++j)C[i][j]=C[i-1][j-1]+C[i-1][j];
    }
    int N;
    ll K;
    scanf("%d %lld", &N, &K);
    int L=0,R=0;
    for (int i = 0; i < (2*N); ++i){
        if(L==N){
            R++;
            an[i]=')';
            continue;
        }
        an[i]='(';
        L++;
        ll v=cal(N);
        if(K>v){
            K-=v;
            an[i]=')';
            L--;
            R++;
        }
    }
    puts(an);
    return 0;
}
























