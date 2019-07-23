#include<stdio.h>
#include<stdbool.h>

int L[100000];

int main(){
  int cases, casenr, n, i, first, last;
  bool reversed;
  char p[100001];
  scanf("%d\n", &cases);
  for (casenr = 1; casenr <= cases; casenr++){
    scanf("%s\n%d\n[", p, &n);
    for (i = 0; i < n; i++)
      scanf("%d%*c", &L[i]);
    scanf("%*c ");
    first = 0;
    last = n-1;
    reversed = false;
    for (i = 0; p[i] != '\0'; i++){
      if (p[i] == 'R')
        reversed = !reversed;
      else if (reversed)
        last--;
      else
        first++;
    }
    if (first > last+1)
      printf("error\n");
    else if (first == last+1)
      printf("[]\n");
    else{
      if (reversed)
        for (i = last; i >= first; i--)
          printf("%c%d", i == last ? '[' : ',', L[i]);
      else
        for (i = first; i <= last; i++)
          printf("%c%d", i == first ? '[' : ',', L[i]);
      printf("]\n");
    }
  }
  return 0;
}
