#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{MAXN = 1000};
int cnt[MAXN*4+1], height[MAXN+1], lb[MAXN+1], res[MAXN+1];
char grid[MAXN][MAXN+1];

int main(){
	int t;
    scanf("%d", &t);
	while (t--){
		int n, m;
		scanf("%d %d", &n, &m);
		assert(n >= 1 && m >= 1 && n <= MAXN && m <= MAXN);
		for (int i=0; i<n; ++i) {
			scanf("%s", grid[i]);
			for (int j=0; j<m; ++j)
				assert(grid[i][j] == '.' || grid[i][j] == '#');
			assert(grid[i][m] == 0);
		}
		memset(height, 0, sizeof(int) * (m+1));
		memset(cnt, 0, sizeof(int) * ((n+m)*2+1));
		for (int i=0; i<n; ++i) {
			int l = 1;
			lb[0] = 0;
			for (int j=0; j<m; ) {
				if (grid[i][j++] == '#') {
					height[j] = 0;
					l = 1;
					lb[0] = j;
					res[j] = 0;
				}
				else {
					int best = 0;
					++height[j];
					while(height[j] < height[lb[l-1]]) {
						--l;
						best = fmax(best, j-lb[l]+1+height[j]);
					}
					res[j] = fmax(res[lb[l-1]], height[j])+j-lb[l-1];
					lb[l++] = j;
					best = fmax(best, res[j]);
					++cnt[best*2];
				}
			}
		}
		for (int i=1; i<=(n+m)*2; ++i)
			if (cnt[i] > 0)
				printf("%d x %d\n", cnt[i], i);
	}
	return 0;
}
