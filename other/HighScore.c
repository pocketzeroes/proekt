#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MAXL 1000
#define MIN(a,b) ((a) < (b) ? (a) : (b))

char name[MAXL+10];

void testcase(){
	int i, j, len, ret, best;
	scanf("%s\n", name);
	ret = 0;
	for(i = 0; name[i]; i++)
		ret += MIN(name[i] - 'A', 26 - name[i] + 'A');
	len = i;
	best = INT_MAX;
	for(i = 0; i < len; i++){
		for(j = i+1; j<len && name[j] == 'A'; j++);
		best = MIN(best,i+(j==len?0:i+len-j));
		best = MIN(best,len-j+i+len-j);
	}
	printf("%d\n", ret+best);
}
int main(){
	int t;
	scanf("%d\n", &t);
	while(t--)
    testcase();
	return 0;
}
