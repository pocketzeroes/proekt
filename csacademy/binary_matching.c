#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}

typedef long long ll;
typedef long double ld;

int pr[510];
char s[510];
char t[510];
int go[510][2];
int pv1[510];
int pv0[510];
pair dp[2][510][510];
int n, m;
const int INF = 1000000;

void upd(pair*a, pair b, int add) {
	b.second += add;
	if(b.first > a->first || (b.first == a->first && b.second < a->second))
		*a = b;
}
int main() {
	scanf("%s %s", s, t);
	n = strlen(s);
	m = strlen(t);
	pr[0] = 0;
	for (int i = 1; i < m; ++i) {
		int k = pr[i - 1];
		while (k > 0 && t[k] != t[i])
			k = pr[k - 1];
		if (t[k] == t[i])
			++k;
		pr[i] = k;
	}
	for (int i = 0; i <= m; ++i) {
		for (int j = 0; j < 2; ++j) {
			if (i < m && t[i] - '0' == j)
				go[i][j] = i + 1;
			else {
				int k = i;
				while (k > 0 && t[k] - '0' != j)
					k = pr[k - 1];
				if (t[k] - '0' == j)
					++k;
				go[i][j] = k;
			}
		}
	}
	int cc0 = 0;
	int cc1 = 0;
	for (int i = 0; i < n; ++i)
		if (s[i] == '1')
			++cc1, pv1[cc1] = cc0;
		else
			++cc0, pv0[cc0] = cc1;
	for (int i = 0; i <= cc0; ++i) {
		int d = i & 1;
		for (int j = 0; j <= cc1; ++j)
			for (int k = 0; k <= m; ++k)
				dp[d][j][k] = newPair(0, INF);
		dp[d][0][0] = newPair(0, 0);
		if (i != 0) {
			for (int j = 0; j <= cc1; ++j) {
				for (int k = 0; k <= m; ++k)
					upd(&dp[d][j][go[k][0]], dp[1 - d][j][k], max(0, j - pv0[i]));
			}
		}
		for (int j = 0; j < cc1; ++j) {
			if (dp[d][j][m].second < INF)
				dp[d][j][m].first++;
			for (int k = 0; k <= m; ++k)
				upd(&dp[d][j + 1][go[k][1]], dp[d][j][k], max(0, i - pv1[j + 1]));
		}
		if (dp[d][cc1][m].second < INF)
			dp[d][cc1][m].first++;
	}
	pair mx = newPair(0, 0);
	for (int i = 0; i <= m; ++i)
		upd(&mx, dp[cc0 & 1][cc1][i], 0);
    printf("%d %d\n", mx.first , mx.second);
	return 0;
}


























































