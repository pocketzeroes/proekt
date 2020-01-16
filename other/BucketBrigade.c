#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef double dbl;

int main(){
	int n;
	dbl v, x, f, t;
	while(scanf("%d %lf %lf %lf %lf", &n, &v, &x, &f, &t) == 5){
		int m = ceil(v/x);
		dbl a = v / m;
		dbl z = n * t + (n + 1) * (a/f) + (m - 1) * (2 * t + 2 * (a/f));
		printf("%.10f\n", z);
  }
	return 0;
}
