#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

bool ok(char c) {
  if (c == 'a' || c == 'e' || c == 'o' || c == 'u' || c == 'i') 
    return 1;
  return 0;
}
char buff[100000];
int main() {
  int ans = 0;
  int N;
  scanf("%d", &N);
  scanf("%s", &buff);
  for(int i=0; i<(N-1); i++)
    if(ok(buff[i]) && ok(buff[i+1]))
      ans++;
  printf("%d\n", ans);
}
