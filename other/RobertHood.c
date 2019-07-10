#include<stdio.h>
#include<math.h>

int distSq(int x1, int y1, int x2, int y2){
	int dx = x1 - x2;
	int dy = y1 - y2;
	return dx*dx + dy*dy;
}
int main(){
	int hasValue[2002];
	int yMins   [2002];
	int yMaxs   [2002];
	int c;
	scanf("%d", &c);
	if (c <= 1)
		printf("-1\n");
	else{
		int retSq = 0;
		int i, x1;
		for (i = 0; i <= 2001; ++i)
			hasValue[i] = 0;
		for (i = 0; i < c; ++i){
			int x, y;
			scanf("%d %d", &x, &y);
			x += 1000;
			if (!hasValue[x]){
				hasValue[x] = 1;
				yMins[x] = yMaxs[x] = y;
			}
			else{
				if (y < yMins[x])
					yMins[x] = y;
				else if (y > yMaxs[x])
					yMaxs[x] = y;
			}
		}
		for (x1 = 0; x1 <= 2001; ++x1){
			int x2;
			if (!hasValue[x1])
				continue;
			for (x2 = x1; x2 <= 2001; ++x2){
				if (hasValue[x2]){
					int distSq1 = distSq(x1, yMins[x1], x2, yMaxs[x2]);
					int distSq2 = distSq(x1, yMaxs[x1], x2, yMins[x2]);
					if (distSq1 > retSq)
						retSq = distSq1;
					if (distSq2 > retSq)
						retSq = distSq2;
				}
			}
		}
		printf("%.9lf\n", sqrt(retSq));
	}
	return 0;
}
