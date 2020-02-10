#pragma GCC optimize "-O3"
#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
char*concats(char*a, char*b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%s", a, b);
  return ptr;
}
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int main(){
    char*s = getstr();
    char*p = getstr();
    if(strcmp(s, p)==0){
        puts("Yes");
        return 0;
    }
    char c[2]; clr(c);
    for(char ch='0'; ch<='9'; ++ch){
        c[0]=ch;
        char*pc=concats(p, c);
        char*cp=concats(c, p);
        if(strcmp(cp, s)==0||
           strcmp(pc, s)==0){
            puts("Yes");
            return 0;
        }
    }
    for(int z=0;p[z];z++){
        #define c p[z]
        if     (c >= 'a' && c <= 'z') c = c - 'a' + 'A';
        else if(c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
        #undef c
    }
    if(strcmp(s, p)==0){
        puts("Yes");
        return 0;
    }
    puts("No");
    return 0;
}
