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
    long double d;
    scanf("%Lf", &d);
    char*a    =getstr();
    char*garbo=getstr();
    char*b    =getstr();
    if(strcmp(a, "th")==0 ||strcmp(a, "thou")==0)   goto end1; d *= 1000;
    if(strcmp(a, "in")==0 ||strcmp(a, "inch")==0)   goto end1; d *= 12;
    if(strcmp(a, "ft")==0 ||strcmp(a, "foot")==0)   goto end1; d *= 3;
    if(strcmp(a, "yd")==0 ||strcmp(a, "yard")==0)   goto end1; d *= 22;
    if(strcmp(a, "ch")==0 ||strcmp(a, "chain")==0)  goto end1; d *= 10;
    if(strcmp(a, "fur")==0||strcmp(a, "furlong")==0)goto end1; d *= 8;
    if(strcmp(a, "mi")==0 ||strcmp(a, "mile")==0)   goto end1; d *= 3;
    if(strcmp(a, "lea")==0||strcmp(a, "league")==0) goto end1;
end1:;
    if(strcmp(b, "th")==0 ||strcmp(b, "thou")==0)   goto end2; d /= 1000;
    if(strcmp(b, "in")==0 ||strcmp(b, "inch")==0)   goto end2; d /= 12;
    if(strcmp(b, "ft")==0 ||strcmp(b, "foot")==0)   goto end2; d /= 3;
    if(strcmp(b, "yd")==0 ||strcmp(b, "yard")==0)   goto end2; d /= 22;
    if(strcmp(b, "ch")==0 ||strcmp(b, "chain")==0)  goto end2; d /= 10;
    if(strcmp(b, "fur")==0||strcmp(b, "furlong")==0)goto end2; d /= 8;
    if(strcmp(b, "mi")==0 ||strcmp(b, "mile")==0)   goto end2; d /= 3;
    if(strcmp(b, "lea")==0||strcmp(b, "league")==0) goto end2;
 end2:;
    printf("%.13Lf\n", d);
    return 0;
}
