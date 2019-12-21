#include <string.h>
#include <stdio.h>

int high[5000+10][26+10][26+10];
int low[5000+10][26+10][26+10];
int N, M;
char dict[10000+10][128];


int MIN(int x, int y) {
	if(x < y) return x;
	else return y;
}

int main() {
	scanf("%d%d", &N, &M);
	int t,i,j,q;
	char c,d,e;
	for(t = 0; t < N; ++t) {
		scanf("%s", dict[t]);
		int L = strlen(dict[t]);
		for(c=0;c <='z'-'a';++c)for(d=0;d<='z'-'a';++d) high[t][c][d] = low[t][c][d] = -1;
		for(i = 0; i < L; ++i) for(j = i+1; j < L; ++j) {
			c = dict[t][i];
			d = dict[t][j];
			c -= 'a'; d -= 'a';
			if(low[t][c][d] == -1) low[t][c][d] = j;
			else low[t][c][d] = MIN(low[t][c][d], j);
			high[t][c][d] = i;
		}
	}
	for(q = 0; q < M; ++q) {
		char p[3];
		scanf("%s", p);
		for(i = 0; i < 3; ++i)
			p[i] += 'x' - 'X';
		c = p[0] - 'a', d = p[1] - 'a', e = p[2] - 'a';
		int t = 0;
		while(t < N) {
			if(low[t][c][d] != -1 && high[t][d][e] != -1)
					if(low[t][c][d] <= high[t][d][e])
						break;
			++t;
		}
		if(t == N) printf("No valid word\n");
		else printf("%s\n", dict[t]);
	}
    return 0;
}
