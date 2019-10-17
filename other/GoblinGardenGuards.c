#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ maxn = 10305};
int cnt[maxn][maxn];
typedef long long ll;

int main(){
	int g;
    scanf("%d", &g);
	for (int i = 0; i < g; i++){
		int x, y;
        scanf("%d%d", &x, &y);
		cnt[x][y]++;
	}
	int t;
    scanf("%d", &t);
	int ans = 0;
	for(int i = 0; i < t; i++){
		int x, y, r;
        scanf("%d%d%d", &x, &y, &r);
		for (int j = fmax(x-r, 0); j <= x+r; j++){
			for (int k = fmax(y-r, 0); k <= y+r; k++){
				if ((j-x)*(j-x) + (k-y)*(k-y) > r*r)
                    continue;
				ans += cnt[j][k];
				cnt[j][k] = 0;
			}
		}
	}
	printf("%d\n", g-ans);
	return 0;
}
