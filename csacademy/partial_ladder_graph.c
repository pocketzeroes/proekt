#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
const ll MOD = 1000000007;

typedef struct matrixS{
	ll a[2][2];
}matrix;

void newMatrix(matrix*z){
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 2; ++j)
      z->a[i][j] = 0;
}
matrix mul(matrix y, matrix x){
  matrix ans;
  newMatrix(&ans);
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 2; ++j) {
      for (int k = 0; k < 2; ++k)
        ans.a[i][k] = (ans.a[i][k] + y.a[i][j] * x.a[k][j]) % MOD;
    }
  return ans;
}
matrix pw(matrix a, ll b){
	matrix ans;
  newMatrix(&ans);
	for (int i = 0; i < 2; ++i)
		ans.a[i][i] = 1;
	while(b){
		while(!(b & 1))
			b >>= 1, a = mul(a , a);
		--b;
		ans = mul(ans, a);
	}
	return ans;
}
int main() {
	matrix a;
  newMatrix(&a);
	a.a[0][0] = 3;
	a.a[0][1] = 2;
	a.a[1][0] = 2;
	a.a[1][1] = 2;
	ll n;
	scanf("%lld", &n);
	a = pw(a, n - 1);
	ll ans = a.a[0][0] + a.a[0][1];
	ans %= MOD;
	printf("%lld\n", ans);
	return 0;
}





















































