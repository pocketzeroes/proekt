#include <stdio.h>
#include <stdlib.h>

#define EASY_WAY
#undef LONG_WAY

int main(){
	int n, i, v, k;
#ifdef LONG_WAY
	int oddsum, evensum, sum, j;
#endif
	scanf("%d", &n);
	for(i = 1; i <= n; i++){
		scanf("%d %d", &(k), &(v));
#ifdef EASY_WAY
		printf("%d %d %d %d\n", i, v*(v+1)/2, v*v, v*(v+1));
#endif
#ifdef LONG_WAY
		oddsum = evensum = sum = 0;
		for(j = 1; j <= v; j++){
			evensum += j*2;
			oddsum += j*2 - 1;
			sum += j;
		}
		printf("%d %d %d %d\n", i, sum, oddsum, evensum);
#endif
	}
	return(0);
}
