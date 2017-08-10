#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int a[5010], b[5010];

int main()
{
	int n, i;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) 
        scanf("%d", &a[i]);
	for (i = 1; i <= n; i++) 
        scanf("%d", &b[i]);
	if (n > 1 && a[2] != b[2])
	{
		printf("-1\n");
		return 0;
	}
	printf("%d\n", 2 * n - 3);
	for (i = 1; i < n; i++) 
        printf("%d %d\n", b[i], b[i + 1]);
	for (i = 3; i <= n; i++) 
        printf("1 %d\n", a[i]);
	return 0;
}
