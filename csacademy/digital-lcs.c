#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

typedef long long ll;
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}

typedef struct pair{
    ll first;
    ll second;
}pair;
pair newPair(ll a, ll b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}

int compP( pair a, pair b){
    if(a.first !=b.first )return(a.first <b.first )?-1:1;
    if(a.second!=b.second)return(a.second<b.second)?-1:1;
    return 0;
}
pair minP(pair a,pair b){return compP(a,b)<0?a:b;}
pair maxP(pair a,pair b){return compP(a,b)>0?a:b;}


/////
int dp[20][20];
ll XX;
pair hard_an;
ll ten[18];

int LCS(int n,int m,int a[],int b[]){
    for (int i = (1); i < (n+1); ++i)
        for (int j = (1); j < (m+1); ++j){
            dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            dp[i][j]=max(dp[i][j],dp[i-1][j-1]+(a[i]==b[j]));
        }
    return dp[n][m];
}
int solve(ll X,ll Y){
    int a[20],b[20];
    int n=0,m=0;
    int now=X;
    while(now){
        a[++n]=now%10;
        now/=10;
    }
    if(!n)
        a[++n]=0;
    now=Y;
    while(now){
        b[++m]=now%10;
        now/=10;
    }
    if(!m)
        b[++m]=0;
    return LCS(n,m,a,b);
}
void dfs(ll me,ll you,int cnt_me,int cnt_you,int dif,int r,ll X){
    if(abs(cnt_me-cnt_you)>2)
        return;
    if(X<0)
        return;
    if(X==0){
        char s[20];
        sprintf(s,"%lld",me);
        if(strlen(s)!=cnt_me)
            return;
        sprintf(s,"%lld",you);
        if(strlen(s)!=cnt_you)
            return;
        ll v=(cnt_me+cnt_you-(4-r))/2;
        hard_an = minP(hard_an, newPair(-v,me));
        hard_an = minP(hard_an, newPair(-v,you));
        return;
    }
    if(dif==0){
        if(X%2==0){
            for(int half=(X%10)/2;half<10;half+=5)
                dfs(me+ten[cnt_me]*half,you+ten[cnt_you]*half,cnt_me+1,cnt_you+1,dif,r,(X-half*2)/10);
        }
        if(r){
            for (int i = 0; i < (10); ++i){
                dfs(me,you+ten[cnt_you]*i,cnt_me,cnt_you+1,dif+1,r-1,X-i);
            }
        }
    }
    else{
        int v=X%10;
        dfs(me+ten[cnt_me]*v,you+ten[cnt_you]*v,cnt_me+1,cnt_you+1,dif,r,(X-v-v*ten[dif])/10);
        if(r){
            if(dif<2){
                for (int i = 0; i < (10); ++i){
                    dfs(me,you+ten[cnt_you]*i,cnt_me,cnt_you+1,dif+1,r-1,X-i*ten[dif]);
                }
            }
            dfs(me+ten[cnt_me]*v,you,cnt_me+1,cnt_you,dif-1,r-1,X/10);
        }
    }
}
int main(){
    ten[0]=1;
    for(int i = 1; i < 18; ++i)
        ten[i] = ten[i-1]*10;
    int iTest; 
    scanf("%d ", &iTest); 
    while (iTest-- > 0){
        ll X;
        scanf("%lld", &X);
        XX = X;
        if(X<100000){
            int ma=-1;
            int an=0;
            for (int i = 0; i < (X); ++i){
                int v = solve(i,X-i);
                if(v>ma){
                    ma=v;
                    an=i;
                }
            }
            printf("%d\n", an);
            continue;
        }
        hard_an = newPair(1LL, 1LL);
        dfs(0,0,0,0,0,2,X);
        printf("%lld\n", hard_an.second);
    }
    return 0;
}





















































