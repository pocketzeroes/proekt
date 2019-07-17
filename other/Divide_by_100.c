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
    char*s1 = getstr();
    char*s2 = getstr();
    while(s1[strlen(s1)-1]=='0' && 
          s2[strlen(s2)-1]=='0'   ){
        s1[strlen(s1)-1] = '\0';
        s2[strlen(s2)-1] = '\0';
    }
    int s1len=strlen(s1);
    int s2len=strlen(s2);

    int len = s2len;
    len--;
    len = s1len - len;
    if(len == s1len){
        puts(s1);
        return 0;
    }
    if(s1len < s2len){
        printf("0.");
        for(int i=0; i<s2len - s1len-1; i++)
            putchar('0');
        puts(s1);
        return 0;
    }
    for(int i=0; i<len; i++)
        putchar(s1[i]);
    if(len == 0)
        putchar('0');
    putchar('.');
    printf("%s\n", s1+len);
    return 0;
}
