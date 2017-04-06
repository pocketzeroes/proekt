#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
  
  
int main() {
	int h, w;
	scanf("%d %d", &h, &w);
	int*x=NULL;int xsz=0;
	int*y=NULL;int ysz=0;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			int tmp;
			scanf("%d", &tmp);
			if (tmp == 1) {
				y=pushback(y,&ysz,i);
				x=pushback(x,&xsz,j);
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			int d = INT_MAX;
			for (int k = 0; k < ysz; k++) {
				d = min(d, max(abs(y[k] - i), abs(x[k] - j)));
			}
			ans = max(ans, d);
		}
	}
	printf("%d", ans);
}
