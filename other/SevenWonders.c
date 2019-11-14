#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int main(){
    char*line = getstr();
    int sum = 0;
    int a = 0,
        b = 0,
        c = 0;
    for(int i=0; line[i]; i++){
        char now = line[i];
        if(now == 'T') a++;
        if(now == 'C') b++;
        if(now == 'G') c++;
    }
    sum += pow(a,2) + pow(b,2) + pow(c,2) + fmin(a, fmin(b, c))*7;
    printf("%d\n", sum);
    return 0;
}
