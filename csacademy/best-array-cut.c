#include <stdio.h>
#include <math.h>
inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int main() {
	int n, s = 0;
    scanf("%d", &n);
	int a[n];
	for(int i = 0; i < n; i++) {
		scanf("%d", a+i);
		s += a[i];
		if(i > 0)
			a[i] += a[i - 1];
	}
	int ans = 1e9;	
	for(int i = 0; i < n - 1; i++) {
		ans = min(ans, abs(2 * a[i] - s));
	}
    printf("%d", ans);
	return 0;
}

