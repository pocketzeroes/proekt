#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

ll max(ll a,ll b){return a>b?a:b;}

typedef struct pair{
    ll first;
    ll second;
}pair;
pair newPair(ll a, ll b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair *pushback(pair *array, int *size, pair value) {
    pair *output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	pair*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


#define X first
#define Y second


typedef pair pll;
enum{ N = 755};
ll n, m, a[N][N], b[N], ans[N][N], sum;
char ipt[N];
vec st;

void rect (ll XS, ll XE, ll YS, ll YE, ll K){
	ll L = (YE - YS + 1);
	ans[XS][YS] += L * K;
	ans[XS][YS+1] -= (L+2) * K;
	ans[XS][YE+2] += (L+2) * K;
	ans[XS][YE+3] -= L * K;
	ans[XE+1][YS] -= L * K;
	ans[XE+1][YS+1] += (L+2) * K;
	ans[XE+1][YE+2] -= (L+2) * K;
	ans[XE+1][YE+3] += L * K;
}
void solve (ll I){
	st.sz=0;
	st.ptr = pushback(st.ptr, &st.sz ,newPair(0, I+1));
	ll S = 0;
	for(ll i=1;i<=m;i++) {
		for(ll j=st.sz;--j;) {
			if(st.ptr[j].Y >= b[i]) break;
			if(st.ptr[j-1].Y > b[i]) {
				rect(st.ptr[j].Y, b[i]-1, st.ptr[j].X, i-1, 1);
				rect(I+1, I+1, st.ptr[j].X, i-1, -b[i]+st.ptr[j].Y);
				S -= (b[i] - st.ptr[j].Y) * (i-st.ptr[j].X);
				st.ptr[j].Y = b[i]; break;
			}
			rect(st.ptr[j].Y, st.ptr[j-1].Y-1, st.ptr[j].X, i-1, 1);
			rect(I+1, I+1, st.ptr[j].X, i-1, -st.ptr[j-1].Y+st.ptr[j].Y);
			S -= (st.ptr[j-1].Y-st.ptr[j].Y) * (i-st.ptr[j].X);
			st.sz--;
		}
#define st_back st.ptr[st.sz-1]
		S += I+1 - st_back.Y;
		if(st_back.Y > b[i]) {
			S += st_back.Y-b[i];
			st.ptr = pushback(st.ptr, &st.sz ,newPair(i, b[i]));
		}
		sum += S;
	}
	for(ll j=st.sz;--j;) {
		rect(st.ptr[j].Y, st.ptr[j-1].Y-1, st.ptr[j].X, m, 1);
		rect(I+1, I+1, st.ptr[j].X, m, -st.ptr[j-1].Y+st.ptr[j].Y);
	}
}
int main(){
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++) {
		scanf("%s",ipt+1);
		for(ll j=1;j<=m;j++) 
            a[i][j] = ipt[j] - '0';
	}
	for(ll i=1;i<=m;i++) 
        b[i] = 1;
	for(ll i=1;i<=n;i++) {
		for(ll j=1;j<=m;j++) 
            if(a[i][j] == 0) 
                b[j] = i+1;
		solve(i);
	}
	for(ll i=1;i<=n;i++) 
        for(ll j=1;j<=m;j++) 
            ans[i][j] += ans[i][j-1];
	for(ll k=0;k<2;k++) 
        for(ll i=1;i<=n;i++) 
            for(ll j=1;j<=m;j++) 
                ans[i][j] += ans[i][j-1] + ans[i-1][j] - ans[i-1][j-1];
	ll mx = 0;
	for(ll i=1;i<=n;i++) 
        for(ll j=1;j<=m;j++) 
            mx = max(mx, ans[i][j]);
	printf("%lld\n",sum-mx);
}






























































