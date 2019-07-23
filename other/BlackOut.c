#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(){
	char cmd[5];
	int t, r1, c1, r2, c2;
	scanf("%d", &t);
	while(t--) {
		printf("3 1 3 6\n");
		fflush(NULL);
		while(true) {
			scanf("%s",cmd);
			if(cmd[0] == 'M') {
				scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
				printf("%d %d %d %d\n", 6-r2, 7-c2, 6-r1, 7-c1);
				fflush(NULL);
			}
			else break;
		}
	}
	return 0;
}
