#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define S(x) ((x)*(x))

int main(){
	int numCases;
	scanf("%d", &numCases);
	while (numCases-- > 0){
		int radius, numPoints;
		scanf("%d %d", &radius, &numPoints);
		double firstX, firstY, lastX, lastY, curX, curY;
		scanf("%lf %lf", &curX, &curY);
		firstX = lastX = curX;
		firstY = lastY = curY;
		double o = 0;
		for (int i = 1; i < numPoints; i++){
			scanf("%lf %lf", &curX, &curY);
			o += sqrt(S(curX - lastX) + S(curY - lastY));
			lastX = curX;
			lastY = curY;
		}
		curX = firstX;
		curY = firstY;
		o += sqrt(S(curX - lastX) + S(curY - lastY));
		double c = 2. * 2 * acos(0) * radius;
		if (c > o)
			puts("Not possible");
        else
			printf("%lf\n", (o-c)/o);
	}
	return 0;
}
