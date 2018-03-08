#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char*itoa(int a){
  char*ptr=NULL;
  asprintf(&ptr, "%d", a);
  return ptr;
}
void inplace_reverse(char * str)
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

int main(){
    int x;
    scanf("%d", &x);
    char*s = itoa(x);
    inplace_reverse(s);
    int y = atoi(s);
    printf("%d\n", x<y );
    return 0;
}
