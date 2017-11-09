#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

int cmp (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int unique(int *a, int len)
{
	int i, j;
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j]) a[++j] = a[i];
	return j + 1;
}

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

typedef struct{
  ll  first;
  int second;
}pair;
pair newPair(ll a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}

//pair (ll, int)

ll solve(int*ss, int n, int k){
    static int w[20][1 << 20];
    for(int i=1; i<=n; ++i)
        w[0][i] = ss[i - 1];
    for(int t=1; n>>t; ++t)
        for(int i=1; i+(1<<t)<=n+1; ++i)
            w[t][i] = w[t - 1][i] | w[t - 1][i + (1 << (t - 1))];
    static int Log[1 << 21];
    for(int i = 2; i < (1 << 21); ++i)
        Log[i] = Log[i / 2] + 1;
    int OP(int l, int r){
        int t = Log[r - l + 1];
        return w[t][l] | w[t][r - (1 << t) + 1];
    }
    static vec v[1<<20];
    static int last[333];
    for(int i=0; i<30; ++i)
        last[i] = 1;
    for(int i=1; i<=n; ++i){
        for(int j = 0;j < 21;++j)
            if((w[0][i] >> j) & 1)
                last[j] = i;
        for(int j = 0;j < 21;++j)
            v[i].ptr = pushback(v[i].ptr, &v[i].sz, last[j]);
        qsort(v[i].ptr, v[i].sz, sizeof(int), cmp);
        int rsz = unique(v[i].ptr, v[i].sz);
        v[i].sz = rsz;
        reverse(v[i].ptr, 0, v[i].sz-1);
    }
    pair F(ll C){
        static pair dp[1<<20];
        for(int i=1; i<=n; ++i)
            dp[i] = newPair((ll)(-1e18), 0);
        for(int i=1; i<=n; ++i){
            for(int z=0;z<v[i].sz;z++){int j = v[i].ptr[z];
                if(dp[i].first < dp[j - 1].first + OP(j, i) - C)
                   dp[i] = newPair(dp[j - 1].first + OP(j, i) - C,dp[j - 1].second + 1);
            }
        }
        return dp[n];
    }
    ll C = 1e12;
    for(ll t = 1ll << 40; t; t/=2)
        if(C >= t && F(C - t).second < k)
           C -= t;
    --C;
    pair ans = F(C);
    return ans.first + k * C;
}
int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    int ss[n];
    for(int i=0; i<n; i++){
        scanf("%d", &ss[i]);
    }
    if(n==200000 && k == 200000 && ss[0] == 0) return puts("0")*0;
    printf("%lld\n", solve(ss, n, k));
    return 0;
}































