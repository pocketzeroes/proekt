#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

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

long long dp[2][100];

int main() {
    char s[500];
    scanf("%499s", &s);
    inplace_reverse(s);
    int n = strlen(s);
    if (s[0] == '0') {
        dp[0][0] = 0;
        dp[1][0] = 1;
    }
    else {
        dp[0][0] = 1;
        dp[1][0] = 0;
    }
    for (int i = 1; i < n; ++i) {
        if (s[i] == '0') {
            dp[0][i] = dp[0][i - 1];
            dp[1][i] = dp[1][i - 1] + (1ll << i);
        }
        else {
            dp[0][i] = dp[1][i - 1] + (1ll << i);
            dp[1][i] = dp[0][i - 1];
        }
    }
    printf("%lld", dp[0][n - 1]);
}
