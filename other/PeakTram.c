#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>


typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll*pushbackL(ll*array, int*size, ll value){
  ll*output = resizeArray(array, ll, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  ll*ptr;
  int sz;
}vecl;
vecl newVecL(){
  vecl rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
int cmpL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}
int lower_bound(ll*a, int n, ll x){
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x <= a[mid]) 
            h = mid;
        else
            l = mid + 1;
    }
    return l;
}
int unique(ll*a, int len){
	int i, j;
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j])
            a[++j] = a[i];
	return j + 1;
}
//////////////////////////
enum{ mod =(int)1e9+7};
enum{Maxn=71};
const ll Inf=1LL<<60;
vecl V;
ll p[Maxn],c[Maxn];
ll dp [2][142*71][71];
ll pre[2][142*71][71];
int n,K;
int tot;

int getid(ll x){
    return lower_bound(V.ptr, V.sz, x);
}
void init(int cs){
    for(int i=0;i<tot;i++){
        for(int j=0;j<=K;j++)
            dp[cs][i][j]=Inf;
    }
}
void calpre(int cs){
    for(int i=0;i<tot;i++){
        for(int j=0;j<=K;j++){
            pre[cs][i][j]=dp[cs][i][j];
            if(i)
                pre[cs][i][j]=min(pre[cs][i-1][j],pre[cs][i][j]);
        }
    }
}
inline void up(ll*x, ll y){
    if(*x > y)
       *x = y;
}
void solve (){
    V.sz=0;
    ll tp=0;
    V.ptr = pushbackL(V.ptr, &V.sz, tp);
    for(int i=1; i<=n; i++){
        scanf("%lld %lld", p+i, c+i);
        for(int j=-n; j<=n; j++)
            if(p[i]+j>0)
                V.ptr = pushbackL(V.ptr, &V.sz, p[i]+j);
    }
    qsort(V.ptr, V.sz, sizeof(ll), cmpL);
    V.sz = unique(V.ptr, V.sz);
    tot = V.sz;
    int cs=0;
    init(cs);
    dp[cs][0][0]=0;
    calpre(cs);
    for(int i=1; i<=n; i++){
        init(cs^1);
        int tid = getid(p[i]);
        for(int j=1; j<tot; j++){
            ll cost = 0;
            if(j<tid){
                cost = abs(V.ptr[j]-p[i])*c[i];
            }
            for(int k=0;k<=K;k++){
                up(&dp[cs^1][j][k], dp[cs][j][k]+cost);
            }
        }
        for(int j=1;j<tot;j++){
            ll cost = abs(V.ptr[j]-p[i])*c[i];
            for(int k=1; k<=K; k++){
                up(&dp[cs^1][j][k], pre[cs][j-1][k-1]+cost);
                up(&dp[cs^1][j][k], pre[cs][j-1][k  ]+cost);
            }
        }
        calpre(cs^1);
        cs^=1;
    }
    ll ans = pre[cs][tot-1][K];
    printf("%lld\n", ans);
}
int main (){
    while(~scanf ( "%d%d" , &n,&K ))
        solve();
    return 0;
}
