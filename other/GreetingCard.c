#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ maxn =(int)1e5+3};
typedef unsigned long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

typedef struct Node{
    ll x, y;
    double len;
}Node;
Node node[maxn];

int cmpN(const void*pa, const void*pb){
    Node*a=(Node*)pa;
    Node*b=(Node*)pb;
    return(a->len < b->len)?-1:1;
}
ll dis(Node a, Node b){
    int x1 = max(a.x,b.x);
    int x2 = min(a.x,b.x);
    int y1 = max(a.y,b.y);
    int y2 = min(a.y,b.y);
    return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
int main(){
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%lld %lld", &node[i].x, &node[i].y);
        node[i].len = sqrt(node[i].x*node[i].x+node[i].y*node[i].y);
    }
    qsort(node, n, sizeof(Node), cmpN);
    int ans  = 0;
    ll  base = 2018 * 2018;
    for(int i = 0 ; i < n; i++){
        for(int j = i+1 ;j < n; j++){
            if(node[j].len-node[i].len > 2018)
               break;
            if(dis(node[i],node[j]) == base )
                ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}
