#include <stdio.h>
#include <string.h>

#define MAXN 1000
#define MOD 1000000
 
static char zad[MAXN + 1];
static int ways[2][MAXN / 2 + 1];
 
static int get (int old, int l, int b){
  if (b < 0 || b > l)
    return 0;
  return ways[old][b];
}
static int numways(){
  int n = strlen (zad), k, i, j, up, op, cl, t;
  int old, act;
  if (n % 2 != 0)
    return 0;
  k = n / 2;
  ways[0][0] = 1;
  old = 0;
  act = 1;
  for (i = 1; i <= n; i++)
    {
      up = (i <= k ? i : n - i);
      for (j = 0; j <= up; j++)
      {
        op = (zad[i - 1] == ')' ? 0 : get (old, i - 1, j - 1));
        cl = (zad[i - 1] == '(' ? 0 : get (old, i - 1, j + 1));
        t = op + cl;
        if (t > MOD)
          t -= MOD;
        ways[act][j] = t;
      }
      old = act;
      act = 1 - old;
    }
  return ways[old][0];
}
int main(){
  while (scanf ("%s", zad) == 1)
    printf ("%d\n", numways ());
  return 0;
}
