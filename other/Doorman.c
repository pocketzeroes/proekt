#include <stdio.h>

enum{ MAXC = 101};

int main(){
	int i, cnt,X;
	char buf[MAXC];
	scanf("%d",&X);
	scanf("%s",buf);
	i=0;cnt = 0;X++;
	while (buf[i] && cnt<=X && -cnt<=X){
		cnt += buf[i++]=='W'?1:-1;
	}
	if (cnt>X || -cnt>X)
		printf("%d\n",i-2);
	else if (cnt==X || cnt==-X)
		printf("%d\n",i-1);
	else
		printf("%d\n",i);
	return 0;
}
