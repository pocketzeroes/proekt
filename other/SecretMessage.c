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
  int rv = scanf("%s", &buff);
  return strdup(buff);
}
int main(){
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        char*s=getstr();
        int w=0;
        int ssize=strlen(s);
        while(w * w < ssize)
            ++w;
        for(int j = 0; j < w; ++j){
            for(int i = w - 1; i >= 0; --i){
                if(i * w + j < ssize)
                    putchar(s[i*w+j]);
            }
        }
        puts("");
    }
    return 0;
}
