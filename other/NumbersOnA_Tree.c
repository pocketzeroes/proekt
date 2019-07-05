#include<stdio.h>

int main(){
	int n;
	char str[100];
	if (scanf("%d%s", &n, str) == 1)
    *str = 0;
	int i = 1;
	for (char *s = str; *s; ++s)
    i = 2*i + (*s=='R');
	printf("%lld\n", (2ll<<n)-i);
	return 0;
}
