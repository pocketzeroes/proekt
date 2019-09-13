#include<stdio.h>
#include<string.h>


char level[41][1001];
int dist[41];
int ndist;

void printsol(){
  int h = 0;
  int step;
  for (step = 1; step <= ndist; ++step) {
    if (h-dist[step] >= 0 && level[step][h-dist[step]]) {
      putchar('D');
      h -= dist[step];
    }
    else {
      putchar('U');
      h += dist[step];
    }
  }
  putchar('\n');
}
int canclimb(int maxh){
  int i;
  int h;
  for (i = 0; i <= ndist; ++i)
    for (h = 0; h <= 1000; ++h)
      level[i][h] = 0;
  level[ndist][0] = 1;
  for (i = ndist; i > 0; --i)
    for (h = 0; h <= maxh; ++h)
      if (level[i][h]){
        if (h-dist[i] >= 0)    level[i-1][h-dist[i]] = 1;
        if (h+dist[i] <= maxh) level[i-1][h+dist[i]] = 1;
      }
  return level[0][0];
}
void solve(int cnt){
  int len=0;
  int x;
  int m;
  int lo = 0;
  int hi = 1000;
  int mid;
  scanf("%d",&ndist);
  for(m = 1; m <= ndist; ++m) {
    scanf("%d", dist+m);
  }
  while (hi > lo+1) {
    mid = (lo+hi) / 2;
    if (canclimb(mid)) hi = mid;
    else lo = mid;
  }
  if (canclimb(hi)) {
    printsol(); return;
  }
  printf("IMPOSSIBLE\n");
}
int main(){
  int i, n;
  for (i = 0, scanf("%d",&n); i < n; ++i)
    solve(i);
  return 0;
}
