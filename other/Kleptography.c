#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char c[1000];
char k[1000];

int main(){
	int n,m;
  scanf("%d %d", &n, &m);
	scanf("%c",k);
	for (int i = 0; i < n; i++)
    scanf("%c", k+m-n+i);
	scanf("%c",k);
	for (int i = 0; i < m; i++)
    scanf("%c", c+i);
	for (int i = m-1; i >= n; i--)
    k[i-n] = ((c[i] - k[i] + 26) % 26) + 'a';
	for (int i = 0; i < m; i++)
    printf("%c",k[i]);
	return 0;
}
