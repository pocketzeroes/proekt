#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
	int p;
  scanf("%d", &p);
	for(int i=1; i<=p; i++){
		int k, n; 
    scanf("%d %d", &k, &n);
		printf("%d ", k);
		printf("%d\n", n+n*(n+1)/2 );
	}
  return 0;
}
