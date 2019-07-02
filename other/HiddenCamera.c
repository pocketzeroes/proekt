#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

enum{ MAXN = 1000};
double complex pt[MAXN];

double trianglearea(double complex p1, double complex p2){
	return creal(p1) * cimag(p2) - creal(p2) * cimag(p1);
}
void testcase(){
	int i, j, n, x, y;
	double complex camera, rotate, cur, prev;
	double angle, area, unused;
	scanf("%d\n", &n);
	for(i = 0; i < n; i++) {
		scanf("%d %d\n", &x, &y);
		pt[i] = x + y * I;
	}
	area = 0;
	for(i = 0; i < n; i++)
		area += trianglearea(pt[i], pt[(i+1)%n]);
	camera = (pt[0] + pt[1]) / 2;
	for(i = 0; i < n; i++)
		pt[i] -= camera;
	angle = -atan2(cimag(pt[1]), creal(pt[1])) - atan(1);
	rotate = cos(angle) + sin(angle) * I;
	for(i = 0; i < n; i++)
		pt[i] *= rotate;
	unused = 0;
	for(j = -1; j <= 1; j += 2) {
		for(i = (n-j)%n; 1 <= i && i <= n; i -= j) {
			cur = pt[i%n];
			prev = pt[(i+j)%n];
			if(cimag(cur) >= 0) {
				unused -= j*trianglearea(prev, creal(prev) + (creal(cur) - creal(prev)) * cimag(prev) / (cimag(prev) - cimag(cur)));
				break;
			}
			unused -= j*trianglearea(prev, cur);
		}
		angle = 2*atan(1);
		rotate = cos(angle) + sin(angle) * I;
		for(i = 0; i < n; i++)
			pt[i] *= rotate;
	}
	printf("%lf\n", 1 - unused / area);
}
int main(){
	int n;
	scanf("%d\n", &n);
	while(n--) 
    testcase();
	return 0;
}
