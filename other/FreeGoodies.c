#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
pair maxP(pair a, pair b){return cmpP(&a,&b)>0?a:b;}

enum{MAXN = 1000};

pair dp[MAXN+1][MAXN+1], val[MAXN];

int main() {
	int tc;
	scanf("%d", &tc);
	assert(tc >= 1 && tc <= 100);
	while(tc--) {
		int n;
		char name[20];
		scanf("%d", &n);
		assert(n >= 1 && n <= MAXN);
		scanf("%s", name);
		int jan_start;
		if (!strcmp(name, "Jan"))
			jan_start = 1;
		else {
			assert(!strcmp(name, "Petra"));
			jan_start = 0;
		}
		for (int i=0; i<n; ++i) {
			scanf("%d %d", &val[i].first, &val[i].second);
			assert(val[i].first >= 0 && val[i].first <= 1000 && val[i].second >= 0 && val[i].second <= 1000);
			val[i].first *= -1;
		}
		qsort(val, n, sizeof(pair), cmpP);
		for(int i=1; i<=n; ++i){
			dp[i][0].second = dp[i-1][0].second - val[i-1].first;
			dp[i][(i+jan_start)/2+1] = newpair(0,0);
			for(int j=1; j<=(i+jan_start)/2; ++j)
				dp[i][j] = maxP(newpair(dp[i-1][j].first, dp[i-1][j].second-val[i-1].first), newpair(dp[i-1][j-1].first+val[i-1].second, dp[i-1][j-1].second));
		}
		printf("%d %d\n", dp[n][(n+jan_start)/2].second, dp[n][(n+jan_start)/2].first);
	}
	return 0;
}
