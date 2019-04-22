#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<math.h>
#include<stdbool.h>

int cCnt, canada, status;
int gold[256], silver[256], bronze[256];
double score[256];
char country[256];

enum{ N = 100};

bool canadaWins(double g, double s, double b){
	double best = -1;
	for (int i = 0; i < cCnt; i++) {
		score[i] = g * gold[i] + s * silver[i] + b * bronze[i];
		if (score[i] > best)
			best = score[i];
	}
	return (score[canada] >= best);
}
void work(){
	for (int g = 0; g <= 0; g++)
		for (int s = -2; s <= 2; s++)
			for (int b = -3; b <= 3; b++)
				if (canadaWins(pow(N, (double)-g), pow(N, (double)-s), pow(N, (double)-b))) {
					printf("Canada wins!\n");
					return;
				}
	printf("Canada cannot win.\n");
}
int main(){
	while (scanf("%d", &cCnt) == 1) {
		if (cCnt <= 0)
			break;
		canada = -1;
		for (int i = 0; i < cCnt; i++){
			status = scanf("%s%d%d%d", country, &gold[i], &silver[i], &bronze[i]);
			assert(status == 4);
			if (strcmp(country, "Canada") == 0) {
				assert(canada < 0);
				canada = i;
			}
		}
		if (canada < 0) 
		  printf("Canada cannot win.\n");
		else 
		  work();
	}
	return 0;
}
