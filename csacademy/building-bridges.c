#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
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


const ll INF = 1e18;
int n,i,j,p,deq[100005];
ll dp[100005],h[100005],w[100005];




int cmp(const void*pa, const void*pb){
    int*a=(int*)pa;
    int*b=(int*)pb;
    int u = *a;
    int v = *b;
    return (h[u] < h[v])?-1:1;
}
ll x(int a){
    return h[a];
}
ll y(int a){
    return dp[a] + h[a] * h[a] - w[a];
}
ll cost(int a, int b){
    return dp[b] + (h[b] - h[a]) * (h[b] - h[a]) + w[a - 1] - w[b];
}
bool slope1(int a, int b, int c){
    double v1 = (y(b) - y(a));
    double v2 = (y(c) - y(b));
    if(x(c) - x(b) == 0)
      v1 *= 0.000001;
    else
      v1 *= (x(c) - x(b));
    if(x(b) - x(a) == 0)
      v2 *= 0.000001;
    else
      v2 *= (x(b) - x(a));
    return v1 <= v2;
}
bool slope2(int a, int b, int c){
    double v1 = (y(b) - y(a));
    double v2 = (y(c) - y(b));
    if(x(c) - x(b) == 0)
      v1 *= -0.000001;
    else
      v1 *= (x(c) - x(b));
    if(x(b) - x(a) == 0)
      v2 *= -0.000001;
    else
      v2 *= (x(b) - x(a));
    return v1 >= v2;
}
double m(int a, int b){
    ll v1;
    if(x(a) - x(b) == 0)
      return 1e18;
    else
      return (y(a) - y(b)) / (x(a) - x(b));
}
void solve(int l, int r){
    if(l == r) 
        return;
    int mid = (l + r) / 2;
    solve(l, mid);
    vec pt  = newVec();
    vec pt1 = newVec();
    for(int ii = l; ii <= mid; ii++)
      pt.ptr = pushback(pt.ptr, &pt.sz ,ii);
    for(int ii = mid + 1; ii <= r; ii++)
      pt1.ptr = pushback(pt1.ptr, &pt1.sz ,ii);
    qsort(pt.ptr , pt.sz , sizeof(int), cmp);
    qsort(pt1.ptr, pt1.sz, sizeof(int), cmp);
    int st = 0;
    int ed = -1;
    for(int ii = 0; ii < pt.sz; ii++){
        while(st + 1 <= ed && !slope1(deq[ed - 1], deq[ed], pt.ptr[ii]))
          ed--;
        deq[++ed] = pt.ptr[ii];
    }
    for(int ii = 0; ii < pt1.sz; ii++){
        while(st + 1 <= ed && cost(pt1.ptr[ii], deq[st]) > cost(pt1.ptr[ii], deq[st + 1]))
            st++;
        int now = pt1.ptr[ii];
        int opt = deq[st];
        dp[now] = min(dp[now], cost(now, opt));
    }
    reverse(pt.ptr ,0, pt.sz -1);
    reverse(pt1.ptr,0, pt1.sz-1);
    st = 0;
    ed = -1;
    for(int ii = 0; ii < pt.sz; ii++){
        while(st + 1 <= ed && !slope2(deq[ed - 1], deq[ed], pt.ptr[ii]))
          ed--;
        deq[++ed] = pt.ptr[ii];
    }
    for(int ii = 0; ii < pt1.sz; ii++){
        while(st + 1 <= ed && cost(pt1.ptr[ii], deq[st]) > cost(pt1.ptr[ii], deq[st + 1]))
          st++;
        int now = pt1.ptr[ii];
        int opt = deq[st];
        dp[now] = min(dp[now], cost(now, opt));
    }
    solve(mid + 1, r);
}
int main(){
    scanf("%d", &n);
    for(i = 0; i < n; i++)
      scanf("%lld", &h[i]);
    for(i = 0; i < n; i++){
        scanf("%lld", &w[i]);
        if(i)
          w[i] += w[i - 1];
    }
    for(i = 1; i < n; i++)
      dp[i] = INF;
    dp[0] = 0;
    solve(0, n - 1);
    printf("%lld\n", dp[n - 1]);
}






























































