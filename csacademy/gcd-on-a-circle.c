#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

typedef signed long long ll;
int N;
int A[201010];
int G[201010][21];
int Gp[201010],Gv[201010];
ll dp[202020];
ll S[202020];
ll mo=1000000007;

int gcd(int u, int v ){
  return v != 0?gcd(v, u%v):u;
}
void solve() {
    int i,j,k,l,r,x,y; 
    scanf("%d", &N);
    for(i=0;i<(N);i++) 
        scanf("%d", &A[i]), A[N+i]=G[i][0]=G[i+N][0]=A[i];
    for(i=0;i<(20);i++) {
        for(x=0;x<(2*N);x++) {
            if(x-(1<<i)<0) 
                G[x][i+1]=1;
            else 
                G[x][i+1]=gcd(G[x][i],G[x-(1<<i)][i]);
        }
    }
    for(i=0;i<(N);i++) {
        Gp[i]=i+1;
        for(j=19;j>=0;j--) 
            if(Gp[i]&&gcd(Gv[i],G[Gp[i]-1][j])>1) 
                Gv[i] = gcd(Gv[i],G[Gp[i]-1][j]), Gp[i]-=1<<j;
    }
    ll ret=0;
    if(Gp[N-1]==0) {
        ret=1;
        for(i=0;i<(N);i++) 
            ret=ret*2%mo;
        ret = (ret+(mo-N))%mo;
    }
    else {
        int cur=0;
        for(i=0;i<(N);i++) {
            x = gcd(cur,A[(N-i)%N]);
            if(x==1) 
                break;
            if(cur!=x) {
                cur = x;
                dp[0]=S[0]=1;
                dp[1]=1,S[1]=2;
                for(j=1;j<N-i;j++) {
                    if(Gp[j]==0 && gcd(Gv[j],cur)==1) 
                        Gp[j]=1;
                    dp[j+1]=S[j];
                    if(Gp[j]>=1) 
                        dp[j+1]+=mo-S[Gp[j]-1];
                    dp[j+1]%=mo;
                    S[j+1]=(S[j]+dp[j+1])%mo;
                }
            }
            ret += dp[N-i];
            ret%=mo;
        }
    }
    printf("%lld\n", ret);
}
int main(){
    solve();
    return 0;
}


























































