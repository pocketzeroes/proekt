#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
enum{ maxn = 100000 + 7};

typedef struct{
    int from,to,flag;
    ll val;
}Edge;
Edge edges[maxn*5],
     edge [maxn*5];

int cmpE(const void*pa, const void*pb){
    Edge*tva=(Edge*)pa;
    Edge*ono=(Edge*)pb;
    if(tva->val==ono->val)
        return(tva->flag>ono->flag)?-1:1;
    return(tva->val < ono->val)?-1:1;
}


int pre[maxn*2],n,m,k,w;
bool judge[maxn*2];

int finded(int x){
    int r = x;
    while(pre[r]!=r)
        r = pre[r];
    int j = x;
    while(j!=r){
        int temp = pre[j];
        pre[j] = r;
        j = temp;
    }
    return r;
}
void Union(int a,int b){
   int fx = finded(a);
   int fy = finded(b);
   if(fx!=fy)
       pre[fx] = fy;
}
int Kruskal(ll v, ll*sum){
   *sum = 0;
    for(int i = 0;i<=n;i++)
        pre[i] = i;
    for(int i = 0;i<m;i++){
        edges[i] = edge[i];
        if(edge [i].flag)
           edges[i].val+=v;
    }
    qsort(edges, m, sizeof(Edge), cmpE);
    int lens = 0,l = 0;
    for(int i = 0;i<m;i++){
        int fa = finded(edges[i].from);
        int fb = finded(edges[i].to  );
        if(fa!=fb){
            Union(edges[i].from,edges[i].to);
            lens++;
           (*sum) += edges[i].val;
            if(edges[i].flag)
                l++;
        }
        if(lens==n-1)
            break;
    }
    if(lens!=n-1)
        return -1;
    return l;
}
int main(){
    memset(judge, 0, sizeof(judge));
    scanf("%d %d %d %d", &n, &m, &k, &w);
    int len = 0;
    for(int i = 1;i<=k;i++){
        int x;
        scanf("%d",&x);
        judge[x] = 1;
    }
    for(int i = 0;i<m;i++){
        scanf("%d %d %lld", &edge[i].from, &edge[i].to, &edge[i].val);
        if((judge[edge[i].from]&&!judge[edge[i].to])||(!judge[edge[i].from]&&judge[edge[i].to])){
            edge[i].flag = 1;
            len++;
        }
        else
            edge[i].flag = 0;
    }
    if(m<n-1||len<w){
        printf("-1\n");
    }
    else{
         ll r = maxn,l = -maxn;
         ll ans = -1;
         ll res;
         while(l<=r){
            ll mid = (l + r)/2;
            int temp = Kruskal(mid, &res);
            if(temp==-1){
                printf("-1\n");
                return 0;
            }
            if(temp>=w){
               ans = res - w*mid;
               l = mid+1;
            }
            else
                r = mid-1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
