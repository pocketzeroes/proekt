#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

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

int maxPalindPrefix(char* s){
    int res           = -1;
    long long base    = 263;
    long long basePow = 1;
    long long mod     = (int)1e9+7;
    long long hash    = 0;
    long long hashRev = 0;
    for (int i = 0; s[i]; ++i){
        hash    = (hash * base + (s[i] + 1)) % mod;
        hashRev = (hashRev + (s[i] + 1) * basePow) % mod;
        basePow = basePow * base % mod;
        if (hash == hashRev){
            res = i + 1;
        }
    }
    return res;
}
int palindromeCreation(char* s){
    int bestPrefix = maxPalindPrefix(s);
    inplace_reverse(s);
    int bestSuffix = maxPalindPrefix(s);
    return strlen(s) - max(bestPrefix, bestSuffix);
}
char S[100000];
int main() {
    scanf("%s", &S);
    printf("%d", palindromeCreation(S) );
    return 0;
}

