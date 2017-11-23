#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int main(void){
	char s[50];
	scanf("%s", s);
	int l = strlen(s), n = 1<<l, x = 0, y = 0;
	for (char *p = s; *p; x += (*p&1)*n/2,	y += (*p/2&1)*n/2, n /= 2, ++p);
	printf("%d %d %d\n", l, x, y);
}
