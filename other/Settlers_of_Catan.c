#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

const int dx[] = { 1, 0, -1, -1, 0, 1};
const int dy[] = {-1, -1, 0, 1, 1, 0};

int val[500][500], freq[10];

void solve() {
  int n;
  scanf("%d", &n);
  assert(1 <= n && n <= 10000);
  int x = 250, y = 250, dir = 0;
  memset(freq, 0, sizeof(freq));
  memset(val, -1, sizeof(val));
  ++freq[val[y][x] = 1];
  while (--n > 0) {
    y += dy[dir];
    x += dx[dir];
    while (val[y+dy[(dir+1)%6]][x+dx[(dir+1)%6]] == -1)
      dir = (dir+1) % 6;
    int mt = 20000, c = 0;
    for (int i = 1; i <= 5; ++i) {
      int f = 0;
      for (int d = 0; d < 6; ++d) 
        if (val[y+dy[d]][x+dx[d]] == i)
          ++f;
      if (!f && freq[i] < mt)
        mt = freq[i], c = i;
    }
    ++freq[val[y][x] = c];
  }
  printf("%d\n", val[y][x]);
}
int main(){
  int T;
  scanf("%d", &T);
  for (int i = 0; i < T; ++i)
    solve();
  return 0;
}
