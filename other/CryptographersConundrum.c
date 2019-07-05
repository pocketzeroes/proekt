#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int main(){
    char*t = strdup("PER");
    char*s = getstr();
    int res = 0;
    for(int i=0; s[i]; i++)
        res += s[i] != t[i % 3];
    printf("%d\n", res);
    return 0;
}
