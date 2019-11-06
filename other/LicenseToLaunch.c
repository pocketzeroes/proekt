#include<stdio.h>
int n, minI, minJ = (1 << 30), tmpJ;
int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &tmpJ);
		if(tmpJ < minJ){
			minJ = tmpJ;
			minI = i;
		}
	}
	printf("%d\n", minI);
	return 0;
}
