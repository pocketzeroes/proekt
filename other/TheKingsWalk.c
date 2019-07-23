#include<stdio.h>
#include<stdlib.h>

enum{ MAGIC = 5318008};

int scan(int const N, int const D, int const start, int const dest){
  int line[N][2];
  for (int i = 0; i < N; ++i)
    line[i][0] = 0;
  line[start][0] = 1;
  for (int i = 1; i <= D; ++i){
    for (int j = 0; j < N; ++j){
      line[j][i % 2] = line[j][(i - 1) % 2];
      if (j > 0)
        line[j][i % 2] += line[j - 1][(i - 1) % 2];
      if (j < N - 1)
        line[j][i % 2] += line[j + 1][(i - 1) % 2];
      line[j][i % 2] %= MAGIC;
    }
  }
  return line[dest][D % 2];
}
int main(){
  int T;
  if (scanf("%d\n", &T) != 1)
    return 1;
  for (int t = 0; t < T; ++t){
    int N;
    int x1, y1;
    int x2, y2;
    if (scanf("%d\n%d %d %d %d\n", &N, &x1, &y1, &x2, &y2) != 5)
      return 1;
    if (abs(x1 - x2) > abs(y1 - y2))
      printf("%d\n", scan(N, abs(x1 - x2), y1 - 1, y2 - 1));
    else if (abs(x1 - x2) < abs(y1 - y2))
      printf("%d\n", scan(N, abs(y1 - y2), x1 - 1, x2 - 1));
    else
      printf("1\n");
  }
  return 0;
}
