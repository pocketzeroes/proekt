#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MX = 365};
int cnt[MX + 10];
int n;

int main() {
  scanf("%d", &n);
  for (int i = 0 ; i < n ; i++) {
    int s, t;
    scanf("%d %d", &s, &t);
    cnt[s]++;
    cnt[t+1]--;
  }
  int ret = 0;
  for (int i = 1, tot = 0 ; i <= MX ; i++) {
    tot += cnt[i];
    ret += (tot > 0);
  }
  printf("%d\n", ret);
  return 0;
}
