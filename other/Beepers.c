#include<stdio.h>
#include<stdlib.h>

int x_pos[11], y_pos[11], used[11], best_path, x_size, y_size, start_x, start_y, n_beepers;

void test (int n_left, int cur_x, int cur_y, int len){
  int next_x, next_y, i;
  if (n_left == 0) {
    len += abs(cur_x-start_x)+abs(cur_y-start_y);
    if (len < best_path)
      best_path = len;
    return;
  }
  for (i = 1;  i <= n_beepers;  ++i){
    if (used[i])
      continue;
    used[i] = 1;  next_x = x_pos[i];  next_y = y_pos[i];
    test(n_left-1, next_x, next_y, len+abs(next_x-cur_x)+abs(next_y-cur_y));
    used[i] = 0;
  }
}
void scenario(){
  int i;
  scanf("%d%d", &x_size, &y_size);
  scanf("%d%d", &start_x, &start_y);
  scanf("%d", &n_beepers);
  for (i = 1;  i <= n_beepers;  ++i)
    scanf("%d%d", &x_pos[i], &y_pos[i]);
  best_path = 9999;
  test(n_beepers, start_x, start_y, 0);
  printf("%d\n", best_path);
}
int main(){
  int n, i;
  scanf("%d", &n);
  for (i = 1;  i <= n;  ++i)
    scenario();
  return 0;
}
