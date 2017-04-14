#pragma GCC optimize "-Ofast"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>


typedef long long ll;
typedef double ld;

typedef struct cmplxS{
	ld x, y;
}cmplx;

cmplx newCmplx0() {//constructor
    cmplx rez;
    rez.x = 0.;
    rez.y = 0.;
    return rez;
}
cmplx newCmplx1(ld a) {//constructor
    cmplx rez;
    rez.x = a;
    rez.y = 0.;
    return rez;
}
cmplx newCmplx(ld a, ld b) {//constructor
    cmplx rez;
    rez.x = a;
    rez.y = b;
    return rez;
}

ld real(cmplx c){
    return c.x;
}
cmplx cMul(cmplx c, cmplx a){
    return newCmplx(c.x*a.x - c.y*a.y,
                    c.x*a.y + c.y*a.x);
}
cmplx cAdd(cmplx c, cmplx a){
    return newCmplx(c.x+a.x, c.y+a.y);
}
cmplx cSub(cmplx c, cmplx a){
    return newCmplx(c.x-a.x, c.y-a.y);
}

    

enum{ MOD  =(ll) 1e9 + 7};
enum{ MAXN = 150000     };
const ld PI    = 3.14159265359;
ll ml[2 * MAXN];
ll fc[2 * MAXN];
ll bfc[2 * MAXN];
int n, k;
ll a[MAXN * 2];
ll b[MAXN * 2];
ll c[MAXN * 2];
ll dp[MAXN * 2];
cmplx aa[MAXN * 2];
cmplx ab[MAXN * 2];
cmplx ac[MAXN * 2];
cmplx ba[MAXN * 2];
cmplx bb[MAXN * 2];
cmplx bc[MAXN * 2];
cmplx cc[MAXN * 2];



void swap(cmplx*nums, int i, int j) {
   cmplx t  = nums[i];
   nums[i]  = nums[j];
   nums[j]  = t;
}
ll pw(ll a, ll b) {
	ll ans = 1;
	while (b) {
		while (!(b & 1))
			b >>= 1, a = (a * a) % MOD;
		--b;
		ans = (ans * a) % MOD;
	}
	return ans;
}
ll cnk(int a, int b) {
	if (a < b)
		return 0;
	ll ans = (fc[a] * bfc[b]) % MOD;
	return (ans * bfc[a - b]) % MOD;
}
void init() {
	fc[0] = 1;
	for (int i = 1; i < MAXN * 2; ++i)
		fc[i] = (fc[i - 1] * i) % MOD;
	bfc[MAXN * 2 - 1] = pw(fc[MAXN * 2 - 1], MOD - 2);
	for (int i = MAXN * 2 - 2; i >= 0; --i)
		bfc[i] = (bfc[i + 1] * (i + 1)) % MOD;
	ml[1] = 1;
	for (int i = 2; i <= 2 * k; i += 2) {
		int nn = (i / 2) - 1;
		ml[i] = (cnk(2 * nn, nn) * pw(nn + 1, MOD - 2)) % MOD;
	}
}
double asmSin(double x) {
  __asm__ ("fsin" : "+t" (x));
  return x;
}
double asmCos(double x) {
  __asm__ ("fcos" : "+t" (x));
  return x;
}
void fft(cmplx a[], int n, int inv) {
	int kk = 0;
	while ((1 << kk) < n)
		++kk;
	int x = 0;
	for (int i = 0; i < n; ++i) {
		if (x > i)
			swap(a, i, x);
		if (i != n - 1) {
			for (int k = kk - 1; k >= 0; --k) {
				x ^= (1 << k);
				if ((x >> k) & 1)
					break;
			}
		}
	}
	for (int bl = 1; bl < n; bl *= 2) {
		ld ang = PI / bl;
		if (inv)
			ang = -ang;
		cmplx wang=newCmplx(    asmCos(ang), asmSin(ang)  );
		for (int i = 0; i < n; i += 2 * bl) {
			cmplx w = newCmplx1(1);
			for (int j = i; j < i + bl; ++j, w = cMul(w, wang) ) {
				cmplx u = a[j];
				cmplx v = cMul(w , a[j + bl]);
				a[j] = cAdd(u , v);
				a[j + bl] = cSub(u , v);
			}
		}
	}
	if (inv) {
		for (int i = 0; i < n; ++i)
			a[i].x /= n, a[i].y /= n;
	}
}
void mult(int n) {
	ll M = 1000;
	for (int i = 0; i < n; ++i){
		aa[i] = newCmplx1(a[i] % M);
        ba[i] = newCmplx1(b[i] % M);
    }
	for (int i = 0; i < n; ++i){
		ab[i] = newCmplx1((a[i] / M) % M); 
        bb[i] = newCmplx1((b[i] / M) % M);
    }
	for (int i = 0; i < n; ++i){
		ac[i] = newCmplx1(a[i] / (M * M)); 
        bc[i] = newCmplx1(b[i] / (M * M));
    }
	fft(aa, n, 0);
	fft(ab, n, 0);
	fft(ac, n, 0);
	fft(ba, n, 0);
	fft(bb, n, 0);
	fft(bc, n, 0);
	for (int i = 0; i < n; ++i)
		cc[i] = cMul(aa[i] , ba[i]);
	fft(cc, n, 1);
	for (int i = 0; i < n; ++i) {
		ll x = llround(real(cc[i]));
		c[i] = (c[i] + x) % MOD;
	}
	for (int i = 0; i < n; ++i)
		cc[i] = cAdd(cMul(aa[i],bb[i]) , cMul(ab[i],ba[i]));
	fft(cc, n, 1);
	for (int i = 0; i < n; ++i) {
		ll x = (llround(real(cc[i])) % MOD) * M;
		c[i] = (c[i] + x) % MOD;
	}
	for (int i = 0; i < n; ++i)
		cc[i] = cAdd(cMul(ab[i],bb[i]), cAdd(cMul(aa[i],bc[i]) , cMul(ac[i],ba[i])));
	fft(cc, n, 1);
	for (int i = 0; i < n; ++i) {
		ll x = (llround(real(cc[i])) % MOD) * M * M;
		c[i] = (c[i] + x) % MOD;
	}
	for (int i = 0; i < n; ++i)
		cc[i] = cAdd(cMul(ac[i],bb[i]) , cMul(ab[i],bc[i]));
	fft(cc, n, 1);
	for (int i = 0; i < n; ++i) {
		ll x = (llround(real(cc[i])) % MOD) * ((M * M * M) % MOD);
		c[i] = (c[i] + x) % MOD;
	}
	for (int i = 0; i < n; ++i)
		cc[i] = cMul(ac[i] , bc[i]);
	fft(cc, n, 1);
	for (int i = 0; i < n; ++i) {
		ll x = (llround(real(cc[i])) % MOD) * ((M * M * M * M) % MOD);
		c[i] = (c[i] + x) % MOD;
	}
}
void run(int l, int r) {
	if (l + 1 == r) {
		if (l == 0)
			dp[l] = 1;
		return;
	}
	int m = (l + r) >> 1;
	run(l, m);
	int len = 1;
	while (len < r - l + m - l)
		len *= 2;
	for (int i = 0; i < len; ++i)
		a[i] = b[i] = c[i] = 0;
	for (int i = l; i < m; ++i)
		a[i - l] = dp[i];
	for (int i = 0; i < r - l; ++i)
		b[i] = ml[i];
	mult(len);
	for (int i = m; i < r; ++i)
		dp[i] = (dp[i] + c[i - l]) % MOD;
	run(m, r);
}
int main(){
	scanf("%d %d", &n, &k);
	init();
	run(0, n + 1);
	printf("%lld\n", dp[n]);
	return 0;
}






























































