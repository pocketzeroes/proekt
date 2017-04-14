#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef long long ll;

inline ll min(ll a,ll b){return a<b?a:b;}
   ll max(ll a,ll b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll*pushback(ll*array, int*size, ll value){
    ll*output = resizeArray(array, ll, *size+1);
    output[(*size)++] = value;
    return output;
}



enum{ MAXN = 120000};
ll*ans;
int n;
ll  a [MAXN];
int p [MAXN];
int en[MAXN];
int lb[MAXN];
int rb[MAXN];
ll  sb[MAXN];

int main(){
    ans=NULL;
    int ansSz=0;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%lld", a + i);
	for(int i = n-1; i >= 0; i--){
        int val;
		scanf("%d", &val);
        --val;
        p[i]=val;
    }
	ll mx = 0;
	for (int i = 0; i < n; ++i) {
		int x = p[i];
		en[x] = 1;
		int l = x;
		int r = x;
		ll sm = a[x];
		if (x > 0 && en[x - 1])
			l = lb[x - 1], sm += sb[x - 1];
		if (x < n - 1 && en[x + 1])
			r = rb[x + 1], sm += sb[x + 1];
		sb[l] = sm;
		sb[r] = sm;
		rb[l] = r;
		lb[r] = l;
		mx = max(mx, sm);
		ans = pushback(ans, &ansSz, mx);
	}
	for(int i = n-1; i >= 0; i--){
		printf("%lld\n", ans[i]);
	}
	return 0;
}



















































