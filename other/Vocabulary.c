#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int max (int a, int b){ return a > b ? a : b;}
enum{ MOD = 1000000009 };
int d[4][4][28][28][28];
char s[3][1 << 20];
int ns[3];
int dp[1 << 20][4];

int check (int a0, int a1, int b0, int b1, int c1, int c2, int c3){
  if (a0 > b0 || a1 > b1)
    return 0;
  if (a0 == 0 && b0 == 1 && c1 >= c2)
    return 0;
  if (a1 == 0 && b1 == 1 && c2 >= c3)
    return 0;
  if (a0 == 0 && b0 == 0 && c1 != c2)
    return 0;
  if (a1 == 0 && b1 == 0 && c2 != c3)
    return 0;
  return 1;
}
int compatible (int p1, int p2, int p3, int c1, int c2, int c3){
  if (p1 < 27 && p1 != c1)
    return 0;
  if (p2 < 27 && p2 != c2)
    return 0;
  if (p3 < 27 && p3 != c3)
    return 0;
  if (c1 == 0 && p1 != 0)
    return 0;
  if (c2 == 0 && p2 != 0)
    return 0;
  if (c3 == 0 && p3 != 0)
    return 0;
  return 1;
}
int main (){
  for (int p1 = 0; p1 < 28; p1++){
    for (int c1 = 0; c1 < 27; c1++){
      if (p1 < 27 && p1 != c1)
        continue;
      for (int p2 = 0; p2 < 28; p2++)
        for (int p3 = 0; p3 < 28; p3++)
          for (int c2 = 0; c2 < 27; c2++)
            for (int c3 = 0; c3 < 27; c3++){
              if (!compatible (p1, p2, p3, c1, c2, c3))
                continue;
              for (int a0 = 0; a0 < 2; a0++)
                for (int a1 = 0; a1 < 2; a1++)
                  for (int b0 = 0; b0 < 2; b0++)
                    for (int b1 = 0; b1 < 2; b1++)
                      if (check (a0, a1, b0, b1, c1, c2, c3))
                        d[a0 + 2 * a1][b0 + 2 * b1][p1][p2][p3]++;
            }
    }
  }
  int te;
  scanf ("%d", &te);
  while (te--){
    int n = 0;
    for (int i = 0; i < 3; i++){
      scanf ("%s", s[i]);
      ns[i] = strlen (s[i]);
      n = max (n, ns[i]);
    }
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < n + 1; j++){
        if (j < ns[i]){
          if (s[i][j] == '?')
            s[i][j] = 27;
          else
            s[i][j] -= 'a' - 1;
        }
        else
          s[i][j] = 0;
      }
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++){
      for (int b = 0; b < 4; b++)
        dp[i][b] = 0;
      for (int a = 0; a < 4; a++)
        for (int b = 0; b < 4; b++)
          dp[i][b] = (dp[i][b] + dp[i - 1][a] * 1LL * d[a][b][s[0][i - 1]][s[1][i - 1]][s[2][i - 1]]) % MOD;
    }
    printf ("%d\n", dp[n][3]);
  }
  return 0;
}
