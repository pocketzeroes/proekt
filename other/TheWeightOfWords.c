#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}

int main(){
    int l = in_nextInt();
    int w = in_nextInt();
    if (w < l)
        return puts("impossible")*0;
    int num = w / l;
    if (num > 26)
        return puts("impossible")*0;
    char c1 = (char) (num + 96);
    int a = (num) * (l - 1);
    int b = w - a;
    if (b > 26){
        num++;
        if (num > 26)
            return puts("impossible")*0;
        c1 = (char) (num + 96);
        a = (num) * (l - 1);
        b = w - a;
        if (b > 26)
            return puts("impossible")*0;
    }
    char c2 = (char)(b + 96);
    char*ans = strdup("");
    for(int i = 0; i < l - 1; i++)
        ans = concatc(ans, c1);
    ans = concatc(ans, c2);
    puts(ans);
    return 0;
}
