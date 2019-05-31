#include <stdio.h>

int main(){
	int b,b1,b2,c,d;
	scanf("%d %d %d",&b1,&b2,&c);
	b=b1+b2;
	d=0;
	while (b>=c){
		b-=c;
		b++;
		d++;
	}
	printf("%d\n", d);
	return 0;
}
