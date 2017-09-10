#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

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
enum{ N = 50000};
int n, L, k;
pair a[N], b[N];
int main(){
	scanf("%d%d%d", &n, &L, &k);
	for (int i = 0; i < n; ++i)
		scanf("%d%d", &a[i].first, &a[i].second);
	for (int i = 0; i < n; ++i)
		scanf("%d%d", &b[i].first, &b[i].second);
	for (int i = 0; i < k; ++i) {
		double l = 0, r = 2e9, m, res;
		pair at;
		for (int it = 0; it < 64; ++it) {
			m = (l + r) / 2;
			double mxA = -1e18, mnB = 1e18;
			for (int i = 0; i < n; ++i) {
				if (a[i].first != -1 && m >= a[i].first) {
					double loc = (m - a[i].first)*a[i].second;
					if (mxA < loc) {
						mxA = loc;
						at.first = i;
					}
				}
				if (b[i].first != -1 && m >= b[i].first) {
					double loc = L - (m - b[i].first)*b[i].second;
					if (mnB > loc) {
						mnB = loc;
						at.second = i;
					}
				}
			}
			if (mxA > mnB)
				r = m;
			else
				l = m;
		}
		a[at.first ].first = -1;
		b[at.second].first = -1;
		printf("%d %d\n", at.first + 1, at.second + 1);
	}
	return 0;
}
