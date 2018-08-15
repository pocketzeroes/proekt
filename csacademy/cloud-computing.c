#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#define max(a,b) (((a)>(b))?(a):(b))
typedef long long ll;

int n, m;

typedef struct{
    int c;
    int f;
    int v;
}Order;
Order order[4000];
Order avail[2000];
ll dp[100001];

int lambda(const void*pa, const void*pb){
    Order*a=(Order*)pa;
    Order*b=(Order*)pb;
    return(a->f > b->f)?-1:1;
}
int main(){
    scanf("%d", &n);
    ll initial_cost = 0;
    for(int i=0; i<n; i++){
        scanf("%d %d %d", &order[i].c, &order[i].f, &order[i].v);
        avail[i] = order[i];
        initial_cost += order[i].v;
    }
    scanf("%d", &m);
    for(int i=n; i<n+m; i++){
        scanf("%d %d %d", &order[i].c, &order[i].f, &order[i].v);
    }
    qsort(order, n+m, sizeof(Order), lambda);
    qsort(avail, n  , sizeof(Order), lambda);
    int C = 0;
    int next_avail = 0;
    for(int i=0; i<n+m; i++){
        while(next_avail < n && avail[next_avail].f >= order[i].f){
            C += avail[next_avail].c;
            next_avail++;
        }
        for(int w=C-order[i].c; w>=0; w--)
            dp[w+order[i].c] = max(dp[w+order[i].c], dp[w] + order[i].v);
    }
    ll ans = 0;
    for(int i=0; i<=C; i++) 
        ans = max(ans, dp[i]);
    printf("%lld\n", ans - initial_cost);
    return 0;
}
