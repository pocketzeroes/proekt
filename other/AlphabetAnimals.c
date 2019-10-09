#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}
char buff[100000];
char*getstr(){
  int rv = scanf("%s", &buff);
  return strdup(buff);
}
///////////////////
int main(){
    char*w = getstr();
    char e = w[strlen(w)-1];
    int  n = in_nextInt();
    char*t[n];
    for(int i = 0; i < n; i++)
        t[i] = getstr();
    int c[128]; clr(c);
    for(int i = 0; i < n; i++)
        c[t[i][0]]++;
    for(int i = 0; i < n; i++){
        char a = t[i][0];
        char b = t[i][strlen(t[i])-1];
        if(a == e && (c[b] == 0 || (a == b && c[b] == 1))){
            printf("%s!\n", t[i]);
            return 0;
        }
    }
    for(int i = 0; i < n; i++){
        if(t[i][0] == e){
            puts(t[i]);
            return 0;
        }
    }
    puts("?");
    return 0;
}
