#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
enum{ N   =(int) 200 + 7};
enum{ MOD =(int) 1e9 + 7};

int dp[N][N][N];
int c [N][N];

int add(int*a, int b)
{
	(*a) += b;
	if (*a >= MOD)
		(*a) -= MOD;
	if (*a < 0)
		(*a) += MOD;
	return *a;
}
int main()
{
	for (int i=0; i<N; i++)
		c[i][0] = 1;
	for (int i=1; i<N; i++)
		for (int j=1; j<=i; j++)
		{
			add(&c[i][j], c[i-1][j]);
			add(&c[i][j], c[i-1][j-1]);
		}
	dp[0][0][0] = 1;
	for (int i=1; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
			for (int k=0; k<N; k++)
			{
				dp[i][j][k] = dp[i-1][j][k];
				if (j > 0 && k >= i)
					add(&dp[i][j][k], dp[i-1][j-1][k-i]);
			}
		}
	}
	int t, n, k;
	scanf("%d %d %d", &t, &n, &k);
	t /= 2;
	if (t == 0)
	{
		printf("%d\n", c[2*n][k] );
		return 0;
	}
	int ans = 0;
	if (t <= n && k > 0)
	{
		add(&ans, c[n - t + n][k-1]);
	}
	for (int i=0; i<t; i++)
	{
		if (i > 0 && t - i > 0 && k > 0)
			for (int j=2; j<=k; j++)
			{
				int A = (j+1) / 2;
				int B = j / 2;
				for (int x=1; x<=n && x <= t - i; x++)
					for (int y=1; y<=n && y <= i; y++)
					{
						add(&ans, 1LL * dp[x-1][A-1][t-i-x] * dp[y-1][B-1][i-y] % MOD * c[2*n-x-y][k-j] % MOD);
					}
			}
		for (int j=0; j<=k; j++)
		{
			for (int x=1; x + j <= k - j + 1 && x * (n+1) <= t - i; x++)
			{
				int rem = t - i - x * (n+1);
				for (int y=0; y<2; y++)
				{
					int need = x + j - 1 + y;
					if (need + j > k)
						continue;
					if (need == 0)
					{
						if (i == 0)
						add(&ans, 1LL * dp[n][j][rem] * c[n][k-j] % MOD);
					}
					else if(i > 0)
						for (int l=1; l<=n && l <= i; l++)
							add(&ans, 1LL * dp[n][j][rem] * dp[l-1][need-1][i-l] % MOD * c[n-l][k - j - need] % MOD);
				}
			}
		}
		if (k > 0)
		for (int j=0; j<=k; j++)
		{
			for (int x=1; x + j <= k - j && x * (n+1) <= i; x++)
			{
				int rem = i - x * (n+1);
				for (int y=0; y<2; y++)
				{
					int need = x + j + y;	
					if (t - i > 0)
						for (int l=1; l<=n && l <= t - i; l++)
							add(&ans, 1LL * dp[n][j][rem] * dp[l-1][need-1][t-i-l] % MOD * c[n-l][k - j - need] % MOD);
				}
			}
		}
		if (i > 0 && t - i > 0)
			for (int j=0; j<=k; j++)
				for (int x=1; x*(n+1) <= t - i; x++)
					for (int y=1; y*(n+1) <= i; y++)
						if (x + j == y + k - j || x + j - 1 == y + k - j)
						{
							int R1 = t - i - x * (n+1);
							int R2 = i - y * (n+1);
							add(&ans, 1LL * dp[n][j][R1] * dp[n][k-j][R2] % MOD);
						}
	}
	printf("%d\n", ans);
}
































































