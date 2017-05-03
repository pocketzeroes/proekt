#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int st[10];
void optimalDigitsRemoval(char*s, int K){
  int n = strlen(s), i, m = 10;
  if (K == 0) {
    printf("%s", s);
    return;
  }
  for (i = 0; i < n && K > 0; ++i){
    while (m < 10 && s[i] - '0' > m && st[m] <= K){
      K -= st[m];
      st[m++] = 0;
    }
    if (m < 10 && s[i] - '0' > m){
      st[m] -= K;
      K = 0;
    }
    if (K > 0){
      m = s[i] - '0';
      ++st[m];
    } 
    else
      --i;
  }
  if (i >= n){
    for (int dig = 0; dig <= 9 && K > 0; ++dig)
      if (K >= st[dig]) {
        K -= st[dig];
        st[dig] = 0;
      } 
      else {
        st[dig] -= K;
        K = 0;
      }
  }
  for (int dig = 9; dig >= 0; --dig)
    for (int cnt = 0; cnt < st[dig]; ++cnt)
      printf("%d", dig);
  for (i; i < n; ++i)
    printf("%c", s[i]);
  puts("");
}
char input[100000];
int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    scanf("%s", &input);
    optimalDigitsRemoval(input, K);
}























































