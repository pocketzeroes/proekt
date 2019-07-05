#include<stdio.h>

int main(){
	int D;
	scanf("%d", &D);
	for (int x = 1; x*x <= D; ++x) {
		int rem = (D-x*x);
		if (rem % (2*x) == 0) {
			printf("%d %d\n", rem/(2*x), rem/(2*x)+x);
			return 0;
		}
	}
	printf("impossible\n");
	return 0;
}
