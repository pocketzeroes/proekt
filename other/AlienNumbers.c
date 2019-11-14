#pragma GCC optimize "-O3"
#define _GNU_SOURCE 1
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
char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  free(a);
  return ptr;
}
void reverse(char * str)
{
  if (str)
  {
    char * end = str + strlen(str) - 1;
#   define XOR_SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
    while (str < end)
    {
      XOR_SWAP(*str, *end);
      str++;
      end--;
    }
#   undef XOR_SWAP
  }
}
////////////////////

int convTo10(char*num, char*base){
    int fromBase[200];
    int baseLength = strlen(base);
    for(int i=0; i<baseLength; i++)
        fromBase[base[i]] = i;
    int result = 0;
    for(int z=0; num[z]; z++){char c = num[z];
        result *= baseLength;
        result += fromBase[c];
    }
    return result;
}
char*solve(char*num, char*from, char*to){
    char toBase[200];
    int toBaseLength = strlen(to);
    strcpy(toBase, to);
    int b10 = convTo10(num, from);
    char*result = strdup("");
    while(b10){
        result = concatc(result, toBase[b10%toBaseLength]);
        b10 /= toBaseLength;
    }
    reverse(result);
    return result;
}
int main(){
    int cases;
    scanf("%d", &cases);
    for(int i=1; i<=cases; i++){
        char*num  = getstr();
        char*from = getstr();
        char*to   = getstr();
        printf("Case #%d: %s\n", i, solve(num, from, to) );
    }
    return 0;
}
