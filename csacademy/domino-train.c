#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define swap(x, y) do { int tSWAP = x; x = y; y = tSWAP; } while (0)
int min(int a,int b){return a<b?a:b;}

void swaparr(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swaparr(nums, start, end);
        start++;
        end  --;
    }
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
    int*ptr;
    int sz;
}vec;
vec newVec(){
    vec rez;
    rez.ptr = NULL;
    rez.sz  = 0;
    return rez;
}
/////////////////
typedef long long ll;

enum{ MAXN=100000};
enum{ MAXM=2*MAXN};
int n,m;
int a    [MAXM],
    b    [MAXM];
int q    [MAXN-1];
vec  adj [MAXN];
int idx  [MAXN];
int deg  [MAXN];
bool done[MAXM];
bool flip[MAXM];
int odd  [MAXN],nodd;
int o    [MAXN],no;
int ro   [MAXN];
int par  [MAXN];
int sz   [MAXN],
    mnpos[MAXN];

void dfs(int at){
    while(idx[at] < adj[at].sz){
        int x = adj[at].ptr[idx[at]++];
        if(done[x])
            continue;
        int to = a[x]+b[x]-at;
        done[x] = true, --deg[at], --deg[to], flip[x]=at!=a[x];
        dfs(to);
        if(x<n)
            o[no++]=x;
    }
}
int uffind(int a) {
    if(par[a]==a)
        return a;
    return par[a]=uffind(par[a]);
}
void ufmerge(int a,int b) {
    a=uffind(a),b=uffind(b); assert(a!=b);
    assert(mnpos[a]+sz[a]==mnpos[b]);
    if(sz[a]<sz[b])
        swap(a, b);
    par[b]=a,sz[a]+=sz[b],mnpos[a]=min(mnpos[a],mnpos[b]);
}
int main() {
    scanf("%d",&n); m=n;
    for(int i=(0);i<(m);++i) scanf("%d%d",&a[i],&b[i]),--a[i],--b[i];
    for(int i=(0);i<(n-1);++i) scanf("%d",&q[i]),--q[i];
    for(int i=(0);i<(n);++i) deg[i]=0; for(int i=(0);i<(m);++i) ++deg[a[i]],++deg[b[i]];
    nodd=0; for(int i=(0);i<(n);++i) if(deg[i]%2==1) odd[nodd++]=i;
    for(int i=2;i<nodd;i+=2) a[m]=odd[i],b[m]=odd[i+1],++m;
    for(int i=(0);i<(m);++i){
        int ai = a[i];
        int bi = b[i];
        adj[ai].ptr = pushback(adj[ai].ptr, &adj[ai].sz, i);
        adj[bi].ptr = pushback(adj[bi].ptr, &adj[bi].sz, i);
        done[i] = false;
    }
    for(int i=(0);i<(n);++i) idx[i]=0,deg[i]=((int)(adj[i]).sz);
    no=0;
    for(int i=(0);i<(n);++i) if(deg[i]%2==1) dfs(i);
    for(int i=(n);i<(m);++i) if(!done[i]) { done[i]=true; dfs(b[i]); }
    for(int i=(0);i<(n);++i) if(deg[i]>0) dfs(i);
    reverse(o, 0, n-1);
    assert(no==n);
    for(int i=(0);i<(n);++i) ro[o[i]]=i;
    for(int i=(0);i<(n);++i) par[i]=i,sz[i]=1,mnpos[i]=ro[i];
    for(int i=(0);i<(n-1);++i) {
        int x=uffind(q[i]);
        if(mnpos[x]!=0) {
            int y=uffind(o[mnpos[x]-1]);
            printf("%d %d\n",o[mnpos[y]]+1,o[mnpos[x]]+1);
            ufmerge(y,x);
        }
        else {
            int y=uffind(o[sz[x]]);
            printf("%d %d\n",o[mnpos[x]]+1,o[mnpos[y]]+1);
            ufmerge(x,y);
        }
    }
    for(int i=(0);i<(n);++i) { if(i!=0) printf(" "); printf("%d",flip[i]?1:0); } puts("");
}
