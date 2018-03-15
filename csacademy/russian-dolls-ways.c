#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
#define N     100000
#define modP 1000000007
typedef long long ll;
int n, arr[N], fact[N + 1], ifact[N + 1];


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
vec p;
///////////
int quick_power(int n, int i, int qpp) {
    ll r = 1;
    for (; i; i >>= 1, n = 1LL * n * n % qpp)
        (i & 1) && (r = r * n % qpp);
    return r;
}
int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    int x = -1;
    qsort(arr, n, sizeof(int), cmp);
    for (int i = 0; i < n; i++)
        if (arr[i] == x)
            p.ptr[p.sz-1]++;
        else {
            x = arr[i];
            p.ptr = pushback(p.ptr, &p.sz, 1);
        }
    int mcnt = 0;
    for(int z=0;z<p.sz;z++){int pp = p.ptr[z];
        if (pp > mcnt)
            mcnt = pp;
    }
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = (ll) fact[i - 1] * i % modP;
    ifact[n] = quick_power(fact[n], modP - 2, modP);
    for (int i = n - 1; i >= 0; i--)
        ifact[i] = (ll) ifact[i + 1] * (i + 1) % modP;
    ll ans = 1;
    for(int z=0;z<p.sz;z++){int pp = p.ptr[z];
        ans = ans * fact[mcnt] % modP * ifact[mcnt - pp] % modP;
    }
    ans = ans * ifact[mcnt] % modP;
    printf("%lld\n", ans);
    return 0;
}
