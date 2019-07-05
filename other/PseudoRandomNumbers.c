#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXL =     20};
enum{ MAXH = 100000};
int t   [MAXH][MAXL];
int len [MAXH];
int used[MAXH];
int pos [MAXH];

void clear() {
  for (int i = 0; i < MAXH; ++i) {
    for (int j = 0; j < MAXL; ++j)
      t[i][j] = 0;
    len[i] = pos[i] = 0;
    used[i] = 1;
  }
}
void solve() {
  clear();
  int B; 
  scanf("%d", &B);
  int m; 
  scanf("%d", &m);
  for (int i = 0; i < m; ++i){
    scanf("%d", &t[i][0]);
    len[i] = 1;
  }
  int q; 
  scanf("%d", &q);
  bool imp = false;
  for (int i = 0; i < m; ++i){
    if (len[i] >= MAXL) 
      puts("ERROR: Too long!");
    if (len[i] == pos[i]) 
      continue;
    if (i == 0)
      pos[i] = len[i];
    else if (len[i-1] - used[i-1] > 0){
      int res = t[i-1][used[i-1]] + t[i-1][used[i-1]-1];
      if (t[i][pos[i]] != res || (res/B > 0 && len[i] > pos[i]+1 && t[i][pos[i]+1] != 1)) {
        imp = true;
        break;
      }
      used[i-1]++;
      pos[i]++;
      if (res/B > 0) {
        if (len[i] == pos[i]+1) {
          t[i][len[i]] = 1;
          len[i]++;
        }
        pos[i]++;
      }
    }
    else {
      int res = t[i][pos[i]] - t[i-1][used[i-1]-1];
      t[i-1][len[i-1]] = res<0 ? res+B : res;
      len[i-1]++;
      used[i-1]++;
      pos[i]++;
      if (res < 0){
        t[i][len[i]] = 1; 
        len[i]++;
        pos[i]++;
      }
      i -= 2;
      continue;
    }
  }
  if (imp){
    puts("impossible");
    return;
  }
  int h = m;
  int i = h-1;
  while(h < q){
    if (i < 0){
      puts("unpredictable");
      return;
    }
    if (len[i] >= MAXL)
      puts("ERROR: Too long!");
    if (len[i] > used[i]) {
      int res = t[i][used[i]] + t[i][used[i]-1];
      used[i]++;
      t[i+1][len[i+1]] = res%B;
      len[i+1]++;
      if (res/B > 0) {
        t[i+1][len[i+1]] = 1;
        len[i+1]++;
      }
      i++;
    } 
    else
      i--;
    if(i == h)
      ++h;
  }
  printf("%d\n", t[q-1][0]);
}
int main(){
  int n;
  scanf("%d", &n);
  for(;n; --n)
    solve();
  return 0;
}
