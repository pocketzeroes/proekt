#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
typedef long long ll;
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}

void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swap(nums, start, end);
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
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
////////////////////////


typedef long long llong;
typedef long double ld;
typedef unsigned long long ull;


enum{ MAXN = 120000};
enum{ MX = 110     };

vec eds[MAXN];
int par[MAXN];
ll sm[MAXN];
int n;
ll dp1[MAXN][MX];
ll dp2[MAXN][MX];
int VV;
ll p[MAXN];
ll mx[MX];


void dfs1(int v, int pp) {
    par[v] = pp;
    for(int i=0;i<eds[v].sz;i++){ int u = eds[v].ptr[i];
        sm[v] += p[u];
        if (u == pp)
            continue;
        dfs1(u, v);
    }
}
void dfs2(int v) {
    dp1[v][1] = sm[v];
    for(int _=0;_<eds[v].sz;_++){ int u = eds[v].ptr[_];
        if (u == par[v])
            continue;
        dfs2(u);
        ll prof = sm[v] - p[u];
        for (int i = 0; i <= VV; ++i)
            dp1[v][i] = max(dp1[v][i], dp1[u][i]);
        for (int i = 0; i < VV; ++i)
            dp1[v][i + 1] = max(dp1[v][i + 1], dp1[u][i] + prof);
    }
    dp2[v][1] = max(dp2[v][1], sm[v]);
    for (int i = 0; i <= VV; ++i)
        mx[i] = 0;
    for(int _=0;_<eds[v].sz;_++){ int u = eds[v].ptr[_];
        if (u == par[v])
            continue;
        ll prof1 = sm[u] - p[v];
        for (int i = 0; i <= VV; ++i) {
            dp2[u][i] = max(dp2[u][i], mx[i]);
            if (i > 0)
                dp2[u][i] = max(dp2[u][i], mx[i - 1] + prof1);
        }
        ll prof = sm[v] - p[u];
        for (int i = 0; i <= VV; ++i)
            mx[i] = max(mx[i], dp1[u][i]);
        for (int i = 0; i < VV; ++i)
            mx[i + 1] = max(mx[i + 1], dp1[u][i] + prof);
    }
    reverse(eds[v].ptr, 0, eds[v].sz-1);
    for (int i = 0; i <= VV; ++i)
        mx[i] = 0;
    for(int _=0;_<eds[v].sz;_++){ int u = eds[v].ptr[_];
        if (u == par[v])
            continue;
        ll prof1 = sm[u] - p[v];
        for (int i = 0; i <= VV; ++i) {
            dp2[u][i] = max(dp2[u][i], mx[i]);
            if (i > 0)
                dp2[u][i] = max(dp2[u][i], mx[i - 1] + prof1);
        }
        ll prof = sm[v] - p[u];
        for (int i = 0; i <= VV; ++i)
            mx[i] = max(mx[i], dp1[u][i]);
        for (int i = 0; i < VV; ++i)
            mx[i + 1] = max(mx[i + 1], dp1[u][i] + prof);
    }
    reverse(eds[v].ptr,0, eds[v].sz-1);
}
void dfs3(int v) {
    for(int _=0;_<eds[v].sz;_++){ int u = eds[v].ptr[_];
        if (u == par[v])
            continue;
        for (int i = 0; i <= VV; ++i) {
            dp2[u][i] = max(dp2[u][i], dp2[v][i]);
        }
        ll prof = sm[u] - p[v];
        for (int i = 0; i < VV; ++i) {
            dp2[u][i + 1] = max(dp2[u][i + 1], dp2[v][i] + prof);
        }
        dfs3(u);
    }
}
ll ans = 0;
int main() {
    scanf("%d%d", &n, &VV);
    if (VV == 0) {
        puts("0");
        return 0;
    }
    for (int i = 0; i < n; ++i)
        scanf("%lld", p + i);
    for (int i = 0; i < n - 1; ++i){
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        eds[a].ptr = pushback(eds[a].ptr, &eds[a].sz ,b);
        eds[b].ptr = pushback(eds[b].ptr, &eds[b].sz ,a);
    }
    dfs1(0, -1);
    for (int i = 0; i < n; ++i)
        ans = max(ans, sm[i]);
    dfs2(0);
    dfs3(0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= VV; ++j)
            ans = max(ans, dp1[i][j]), ans = max(ans, dp2[i][j]);
    printf("%lld\n", ans);
    return 0;
}





















































