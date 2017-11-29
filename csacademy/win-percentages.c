#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int arr[200];
int main() {
	int n;
	double p2, p1, g2, g1;
	scanf("%lf %lf %lf %lf", &p1, &g1, &p2, &g2);
	int por1, res1 = -1;
	for (int i=0; i<=p1; i++){
		por1 = floor(((double) i) * 100.0 / p1);
		if (por1 == g1){
			res1 = i;
			break;
		}
		if (por1 > g1){
			res1 = i-1;
			break;
		}	
 	}
	int por2, res2 = -1;
	for (int i=res1; i<=p2; i++){
		por2 = floor(((double) i) * 100.0 / p2);
		if (por2 == g2){
			res2 = i;
		}
		if (por2 > g2){
			res2 = i-1;
			break;
		}
 	}
 	printf("%d\n", min(res2-res1, (int)p2-(int)p1));
    return 0;
}
