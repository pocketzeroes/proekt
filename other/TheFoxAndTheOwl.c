#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
 
enum{ MAX = 100000+100};
int len;
char N[MAX];
 
void shift(int off) {
	if (off > 0) {
		for (int i = len-1; i >= 0; --i)
			N[i+off] = N[i];
	}
    else {
		for (int i = 0; i < len; ++i)
			N[i] = N[i-off];
	}
	len += off;
}
int main(){
    int tc;
    scanf("%d", &tc);
	for(int z=0;z<tc;z++){
		scanf("%s", N);
		if (N[0] == 'E') 
            break;
		len = strlen(N);
		if (N[0] == '-') {
			int i = len-1;
			while (i > 0 && N[i] == '9') --i;
			if (i == 0) {
				shift(1);
				N[0] = '-';
				N[1] = '1';
			} else {
				N[i] += 1;
			}
		} else {
			int i = len-1;
			while (i >= 0 && N[i] == '9') --i;
			if (i == -1) {
				shift(2);
				N[0] = '-';
				N[1] = '1';
			} else if (i == 0) {
				shift(1);
				N[0] = '-';
				N[1] += 1;
			} else {
				N[i]++;
				while (i > 0 && N[i] == '9') --i;
				if (i == -1 || i == 0) {
					shift(1);
					N[0] = '-';
				} else {
					N[i] += 1;
					i--;
					while (N[i] == '0') --i;
					N[i] -= 1;
					int s = 0;
					for (int j = i+1; j < len; ++j)
						s += N[j] - '0';
					for (int j = i+1; j < len; ++j) {
						if (s > 9) {
							N[j] = '9';
							s -= 9;
						} else {
							N[j] = s + '0';
							s = 0;
						}
					}
					if (N[0] == '0')
						shift(-1);
				}
			}
		}
		N[len] = 0;
		printf("%s\n", N);
	}
	return 0;
}
