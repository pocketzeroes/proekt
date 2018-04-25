#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

#define MOD 1000000007LL


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
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
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
ll pw(ll a, ll b) {
    ll ans = 1; while (b) {
        while (!(b & 1)) b >>= 1, a = (a * a) % MOD;
        ans = (ans * a) % MOD, --b;
    } 
    return ans;
}
enum{ MX = 3100000};

vec vv;
ll fc[MX * 2];
ll bfc[MX * 2];
int a[210000];
int n, k;
ll ct[MX];

ll run(int l, int r, int x){
    if (x == vv.sz)
        return ct[r - l - 1];
    if (vv.ptr[x] <= l || vv.ptr[x] >= r)
        return 0;
    if (x + 1 == vv.sz) {
        return ct[vv.ptr[x] - l - 1] * ct[r - vv.ptr[x] - 1] % MOD;
    }
    if (vv.ptr[x + 1] < vv.ptr[x]) {
        return run(l, vv.ptr[x], x + 1) * ct[r - vv.ptr[x] - 1] % MOD;
    }
    else
        return run(vv.ptr[x], r, x + 1) * ct[vv.ptr[x] - l - 1] % MOD;
}
ll solve(){
    scanf("%d %d", &n, &k);
    for (int j = 0; j < k; ++j)
        scanf("%d", &a[j]), --a[j];
    int l = -1;
    int r = -1;
    for (int i = 0; i < k; ++i)
        if (l == -1 || a[i] < a[l])
            l = i;
    for (int i = 0; i < k; ++i)
        if (r == -1 || a[i] > a[r])
            r = i;
    if (k <= 1)
        return ct[n];
    if(l > r){
        reverse(a, 0, k-1);
        l = k - 1 - l;
        r = k - 1 - r;
    }
    ll ans = ct[a[l] + 1 + n - 1 - a[r]];
    for (int i = l; i < r; ++i) {
        if (a[i] > a[i + 1])
            return 0;
    }
    for (int i = l + 1; i < r - 1; ++i)
        ans = (ans * ct[a[i + 1] - a[i] - 1]) % MOD;
    ll av = r - l - 1;
    if (l == 0)
        ++av;
    if (r == k - 1)
        ++av;
    ans = (ans * av) % MOD;
    if (ans == 0)
        return 0;
    if (l + 1 == r) {
        vv.sz=0;
        for (int i = l - 1; i >= 0; --i)
            vv.ptr = pushback(vv.ptr, &vv.sz, a[i]);
        for (int i = r + 1; i < k; ++i)
            vv.ptr = pushback(vv.ptr, &vv.sz,a[i]);
        ans = (ans * run(a[r - 1], a[r], 0)) % MOD;
    }
    else {
        vv.sz=0;
        for (int i = l - 1; i >= 0; --i)
            vv.ptr = pushback(vv.ptr, &vv.sz, a[i]);
        ans = (ans * run(a[l], a[l + 1], 0)) % MOD;
        vv.sz=0;
        for (int i = r + 1; i < k; ++i)
            vv.ptr = pushback(vv.ptr, &vv.sz, a[i]);
        ans = (ans * run(a[r - 1], a[r], 0)) % MOD;
    }
    return ans;
}
ll cnk(int n, int k){
    return fc[n] * bfc[k] % MOD * bfc[n - k] % MOD;
}
int main(){
    fc[0] = 1;
    for (int i = 1; i < 2 * MX; ++i)
        fc[i] = (fc[i - 1] * i) % MOD;
    bfc[2 * MX - 1] = pw(fc[2 * MX - 1], MOD - 2);
    for (int i = 2 * MX - 2; i >= 0; --i)
        bfc[i] = bfc[i + 1] * (i + 1) % MOD;
    for (int i = 0; i < MX; ++i)
        ct[i] = cnk(2 * i, i) * fc[i] % MOD * bfc[i + 1] % MOD;
    int tt;
    scanf("%d", &tt);
    for(int it = 0; it < tt; ++it)
        printf("%lld\n", solve());
    return 0;
}


