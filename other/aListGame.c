#include<stdio.h>

int main(){
	int K;
	int Y = 0;
	scanf("%d", &K);
	int i;
	for( i = 1; i*i <= K; i++){
		if(K%i == 0){
			K = K/i;
			Y++;
			i = 1;
		}
		if(K==1)
			Y++;
	}
	printf("%d", Y);
  return 0;
}
