#pragma GCC optimize "-O3"
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
    int fs;
    scanf("%d", &fs);
    char*myanswers     = getstr();
    char*friendanswers = getstr();
    int same=0;
    int n = strlen(myanswers);
    for(int i=0; i<n; i++)
        if(myanswers[i] == friendanswers[i])
            same++;
    printf("%d\n", (int)fmin(same, fs) + (int)fmin(n-same, n-fs));
    return 0;
}
