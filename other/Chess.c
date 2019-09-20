#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
	int n;
	char c[4];
	char a[4];
	scanf("%d", &n);
	for(;n--;){
		scanf("%s %s %s %s", &c[0], &c[1], &c[2], &c[3]);
		c[0] -= 'A';
		c[1] -= '1';
		c[2] -= 'A';
		c[3] -= '1';
		a[0] = c[0] + c[1];
		a[1] = c[0] - c[1];
		a[2] = c[2] + c[3];
		a[3] = c[2] - c[3];
		if((a[0]) % 2 != (a[2]) % 2){
			puts("Impossible");
		}
    else if(c[0] == c[2] && c[1] == c[3]){
			printf("0 %c %c\n", c[0] + 'A', c[1] + '1');
		}
    else if(a[0] == a[2] || a[1] == a[3]){
			printf("1 %c %c %c %c\n", c[0] + 'A', c[1] + '1', c[2] + 'A', c[3] + '1');
		}
    else if(a[0] + a[3] >= 0 && a[0] + a[3] < 16 && a[0] - a[3] >= 0 && a[0] - a[3] < 16){
			printf("2 %c %c %c %c %c %c\n", c[0] + 'A', c[1] + '1', (a[0] + a[3])/2 + 'A', (a[0] - a[3])/2 + '1', c[2] + 'A', c[3] + '1');
		}
    else {
			printf("2 %c %c %c %c %c %c\n", c[0] + 'A', c[1] + '1', (a[1] + a[2])/2 + 'A', (a[2] - a[1])/2 + '1', c[2] + 'A', c[3] + '1');
		}
	}
  return 0;
}
