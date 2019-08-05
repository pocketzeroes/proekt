#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

enum{ MAXN = 25000};

char line[MAXN+10];
int count[256];
bool done[256];

void testcase(){
	int i, n, ret, time;
	scanf("%d\n", &n);
	scanf("%s\n", line);
	memset(count, 0, sizeof(count));
	for(i = 0; i < n; i++)
		count[line[i]]++;
	ret = 0;
	time = n - 1;
	memset(done, 0, sizeof(done));
	for(i = n - 1; i >= 0; i--) {
		if(!done[line[i]]) {
			ret += (i - time)*count[line[i]];
			time -= count[line[i]];
			done[line[i]] = true;
		}
	}
	printf("%d\n",ret*5);
}
int main(){
	int t;
	scanf("%d\n",&t);
	while(t--)
    testcase();
	return 0;
}
