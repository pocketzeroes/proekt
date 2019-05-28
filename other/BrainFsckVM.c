#include<stdio.h>
#include<stdlib.h>
#include<string.h>

unsigned char data[100000];
char input  [4096];
char program[4096];
int  ip;
int  jumparr[4096];

int main(){
	int ntc, i, j;
	scanf("%d", &ntc);
	while(ntc--){
		int memsize, progsize, inputsize;
		scanf("%d %d %d ", &memsize, &progsize, &inputsize);
		fgets(program, 4096, stdin);
		fgets(input, 4096, stdin);
		memset(data, 0, memsize);
		memset(jumparr, -1, sizeof jumparr);
		for(i = 0; i < progsize; i++) {
			if(program[i] == '[') {
				jumparr[i] = -2;
			}
            else if(program[i] == ']') {
				for(j = i-1; j >= 0; j--) {
					if(jumparr[j] == -2) {
						jumparr[j] = i;
						jumparr[i] = j;
						break;
					}
				}
			}
            else
				jumparr[i] = -1;
		}
		const int maxcount = 50000100;
		int count          = 0;
		int ip             = 0;
		int inputidx       = 0;
		int dp             = 0;
		int maxip          = 0,
            minip          = 0;
		while(count++ < 2*maxcount){
			switch(program[ip]){
                case '[':
                    if(data[dp] == 0){
                        ip = jumparr[ip];
                    }
                    break;
                case ']':
                    if(data[dp] != 0) {
                        ip = jumparr[ip];
                    }
                    break;
                case '+':
                    data[dp]++;
                    break;
                case '-':
                    data[dp]--;
                    break;
                case '<':
                    if(dp == 0) dp = memsize-1;	else dp--;
                    break;
                case '>':
                    if(dp == memsize-1) dp = 0; else dp++;
                    break;
                case '.':
                    fputc(data[dp], stderr);
                    break;
                case ',':
                    if(inputidx < inputsize) {
                        data[dp] = input[inputidx++];
                    }
                    else {
                        data[dp] = 255;
                    }
                    break;
                default:
                    break;
			}
			if(count == maxcount) {
				minip = ip;
				maxip = ip;
			}
			if(minip > ip)
                minip = ip;
			ip++;
			if(maxip < ip)
                maxip = ip;
			if(ip >= progsize)
                break;
		}
		if(count < maxcount){
			printf("Terminates\n");
		}
        else {
			printf("Loops %d %d\n", minip, maxip);
		}
	}
	return 0;
}
