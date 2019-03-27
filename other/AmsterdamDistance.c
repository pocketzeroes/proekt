#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long double ld;
ld min(ld a, ld b){return a<b?a:b;}

int main(){
	int m, n;
	ld r, d1, a0, a1, b0, b1;
	scanf("%d %d %Lf %Lf %Lf %Lf %Lf", &m, &n, &r, &a0, &b0, &a1, &b1);
	d1 = labs(b0 - b1) + M_PI * min(b0, b1) * labs(a0 - a1) / m;
  printf("%.15Lf\n", min(d1, b0 + b1)*r/n);
	return 0;
}
