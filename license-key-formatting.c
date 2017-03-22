#include <stdio.h>
#include <string.h>
#include <ctype.h>
char result[12001]={'\0'};

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

char* licenseKeyFormatting(char* S, int K) {
    memset(result,0,sizeof(result));
    int resultLen=0;
    for (int it = strlen(S)-1; it>=0; it--) {
        if (S[it] == '-')
            continue;
        if (resultLen % (K + 1) == K) 
            result[resultLen++] = '-';
        result[resultLen++] = toupper(S[it]);
    }
    inplace_reverse(result);
    return result;
}









