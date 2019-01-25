#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
  int t, n;
  for (scanf("%d", &t); scanf("%d", &n) && t--; ) {
    int out[20], pos = 0;
    memset(out, 0, sizeof(out));
    for (int i = 1; i <= n; ++i) {
      for (int j = 0; j <= i; ++j) {
        pos %= n;
        ++pos;
        while (out[pos]) {
          pos %= n;
          ++pos;
        }
      }
      out[pos] = i;
    }
    for(int i = 1; i <= n; ++i) 
      printf("%d%c", out[i], i==n ? '\n' : ' ');
  }
  return 0;
}
