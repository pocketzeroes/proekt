#include <stdio.h>
#include <stdlib.h>
#define	BUF_SIZE	128

int main(int argc, char **argv){
	int p, k, i, j, m, ov, dv, hv;
	char szBuf[BUF_SIZE];
	if(fgets(&(szBuf[0]), BUF_SIZE-1, stdin) != NULL){
		p = atoi(&(szBuf[0]));
		for(i = 1; i <= p; i++){
			if(fgets(&(szBuf[0]), BUF_SIZE-1, stdin) == NULL)
				break;
			k = atoi(&(szBuf[0]));
			if(k != i){
				fprintf(stderr, "Wrong problem number %d for instance %d\n", k, i);
				break;
			}
			for(j = 0; j < BUF_SIZE; j++){
				if(szBuf[j] == ' ')
					break;
			}
			ov = 0;
			for(m = j; m < BUF_SIZE && szBuf[m] != '\0' && szBuf[m] != '\r' && szBuf[m] != '\n'; m++){
				if(szBuf[m] == ' ')
					continue;
				if(szBuf[m] >= '0' && szBuf[m] <= '7')
					ov = (ov << 3) | (szBuf[m] - '0');
        else {
					ov = 0;
					break;
				}
			}
			sscanf(&(szBuf[j]), "%d", &dv);
			sscanf(&(szBuf[j]), "%x", &hv);
			printf("%d %d %d %d\n", k, ov, dv, hv);
		}
	}
	return(0);
}
