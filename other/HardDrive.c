#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int bits[500000];

int main(){
	int n,e,b;
  scanf("%d %d %d", &n, &e, &b);
	for (int i = 0; i < n; i++)
    bits[i] = -1;
	int f;
	if (n == 1) {
		printf("0\n");
		return 0;
	}
	for (int i = 0; i < b; i++){
		int p;
    scanf("%d", &p);
		if (!i)
      f = p-1;
		bits[p-1] = 0;
	}
	bits[0] = 0; 
	for (int i = 1; i < n; i++) {
		if (e == 0 || (e == -1 && bits[1]) || (e == 1 && !bits[1]))
      break;
		if (bits[i] == 0)
      continue;
		bits[i] = 1 - bits[i-1];
		if (bits[i])
      e-=2;
	}
	if (e) {
		bits[0] = 1;
		if (bits[1])
      e++;
    else
      e--;
	}
	if (e){
		bits[0] = 0;
		for(int i = 0; i < f; i++)
      bits[i] = 1 - bits[i];
	}
	for(int i = 0; i < n; i++)
    printf("%d",bits[i]==1);
  return 0;
}
