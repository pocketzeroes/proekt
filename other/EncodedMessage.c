#include <stdio.h>
#include <string.h>
#include <math.h>

char Message[10001];

int main()
{ int cases, casenr, n, i, j;
  scanf("%d\n", &cases);
  for (casenr = 1; casenr <= cases; casenr++)
  { scanf("%s\n", Message);
    n = (int)sqrt(strlen(Message));
    for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
        putchar(Message[j*n + n-1-i]);
    putchar('\n');
  }
  return 0;
}

