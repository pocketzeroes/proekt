#pragma GCC optimize "-O3"
#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  free(a);
  return ptr;
}
char buff[100000];
char*getstr(){
  int rv = scanf("%s", &buff);
  return strdup(buff);
}
////////////////

int ctoi(char c){
    if (c <= '9')
        return c - '0';
    else
        return c - 'a' + 10;
}
char itoc(int i){
    if (i <= 9)
        return i + '0';
    else if (i <= 35)
        return i + 'a' - 10;
    else
        return '0';
}
int main(){
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; ++i){
        char*s[3];
        char op, eq;
        s[0] = getstr(); getchar();
        op = getchar();
        s[1] = getstr(); getchar();
        eq = getchar();
        s[2] = getstr();
        char*result=strdup("");
        for(int j = 1; j <= 36; ++j){
            bool err = false;
            long a[3] = {0, 0, 0};
            for(int k = 0; k < 3; ++k){
                for(int z=0;s[k][z];z++){char c = s[k][z];
                    int digit = ctoi(c);
                    if(j > 1)
                        err = err || digit >= j;
                    else
                        err = err || digit != 1;
                    a[k] = a[k] * j + digit;
                }
                err = err || a[k] >= 1ll << 32;
            }
            switch(op){
                case '+': err = err || a[0] + a[1] != a[2]; break;
                case '-': err = err || a[2] + a[1] != a[0]; break;
                case '*': err = err || a[0] * a[1] != a[2]; break;
                case '/': err = err || a[2] * a[1] != a[0]; break;
            }
            if(!err)
               result = concatc(result, itoc(j));
        }
        if(strlen(result)>0)
            puts(result);
        else
            puts("invalid");
    }
    return 0;
}
