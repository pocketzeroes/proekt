#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

enum{ MAXN = 501};
int board[22] = {20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5, 20, 1};
double p[MAXN + 1][MAXN + 1][2];

int main(){
  memset(p, 0, sizeof(p));
  for (int n = 1; n <= MAXN; n++)
    p[0][n][1] = 0.0;
  for (int m = 1; m <= MAXN; m++)
    p[m][0][0] = 0.0;
  for (int m = 1; m <= MAXN; m++){
    for (int n = 1; n <= MAXN; n++){
      double a0 = 0.0, pr0 = 0.0;
      for (int i = 1; i <= 20; i++){
        if (i <= m)
          pr0 += (1.0 - p[m - i][n][1]) / 20.0;
        else
          a0 += 1.0 / 20.0;
      }
      double pr1[4];
      for (int i = 0; i < 4; i++)
        pr1[i] = -1.0;
      for (int i = 1; i <= 20; i++){
        int b = 0;
        double pri = 0.0;
        for (int j = -1; j < 2; j++)
          if (board[i + j] > n)
            b++;
          else
            pri += (1.0 - p[m][n - board[i+j]][0]) / 3.0;
        pr1[b] = max(pr1[b], pri);
      }
      p[m][n][1] = -1e9;
      for (int i = 0; i < 4; i++){
        if (pr1[i] > -0.5){
          double c = (double)i / 3.0;
          p[m][n][1] = max(p[m][n][1], (pr1[i] + c * (1 - pr0 - a0)) / (1.0 - c * a0));
        }
      }
      p[m][n][0] = a0 * (1 - p[m][n][1]) + pr0;
    }
  }
  for (;;){
    int n;
    scanf("%u", &n);
    if(n == 0)
      break;
    printf("%.12lf %.12lf\n", p[n][n][0], p[n][n][1]);
  }
  return 0;
}
