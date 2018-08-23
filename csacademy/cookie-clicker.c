#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}

#define mem(a,b) memset(a,b,sizeof(a))
typedef long long ll;

int a  [10], b  [10];
int v  [10], vis[10];
int ord[10];
int ans = 1e9;
int c,s;
int n;

int upper(int a, int b){
    if(a%b == 0)
        return a/b;
    return a/b+1;
}
int getAns(){
    int ts  = s;
    int ret = 0;
    int cur = 0;
    for(int i=0; i<n; i++){
        int k = ord[i];
        if(v[k] == 0) 
            continue;
        int d = min(upper(c-cur,ts), upper(a[k]-cur,ts));
        if(d < 0) 
            d = 0;
        ret += d;
        cur += ts*d;
        if(cur >= c) 
            break;
        cur -= a[k];
        ts += b[k];
    }
    if(cur < c) 
        ret += upper(c-cur,ts);
    return ret;
}
void dfs(int x){
    if(x == n){
        ans = min(ans,getAns());
        return;
    }
    for(int i = 0;i < n;i++){
        if(vis[i])
            continue;
        ord[i] = x;
        vis[i] = 1;
        dfs(x+1);
        vis[i] = 0;
    }
}
void work(int x){
    mem(v,0);
    int cnt = 0;
    while(x)
        v[cnt++] = x%2,x >>= 1;
    dfs(0);
}
int main(){
    scanf("%d", &n);
    scanf("%d %d", &c, &s);
    for(int i=0; i<n; i++) 
        scanf("%d%d",&a[i],&b[i]);
    for(int i = 1;i < (1<<n);i++){
        work(i);
    }
    printf("%d\n", ans);
    return 0;
}
