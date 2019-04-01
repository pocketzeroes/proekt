#include<stdio.h>
#include<string.h>

int main() {
	char buffer[1001];
	int i, j;
	scanf("%s", buffer);
	i = strlen(buffer);
	scanf("%s", buffer);
	j = strlen(buffer);
	printf("%s\n", i < j ? "no" : "go");
	return 0;
}
