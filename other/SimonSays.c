#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char line[100000];
char*getln(){
  gets(line);
  return strdup(line);
}

int main(){
    int n;
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; ++i){
        char*s=getln();
        if(strncmp(s, "Simon says ", 11)==0)
            puts(s+11);
    }
    return 0;
}
