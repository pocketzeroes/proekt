#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
enum{ MAXN = 300005};
int n, chk[1123455];
char buf[669];

int main(){
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf("%s", buf);
		if(strlen(buf) > 8)
      continue;
		int x;
    sscanf(buf, "%d", &x);
		if(x >= 0 && x < 1010101)
      chk[x] = 1;
	}
	for(int i=0;;i++){
		if(!chk[i]){
			printf("%d\n", i);
			return 0;
		}
	}
  return 0;
}
