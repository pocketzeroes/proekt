#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

double in_nextDouble(){
  double xx;
  scanf("%lf", &xx);
  return xx;
}

double refund;
double p;

double solve(int win, int loss){
  double factor = (1-p)/p;
  double x = pow(factor, loss);
  double y = pow(factor, win+loss);
  double pLoss = (x-y)/(1-y);
  double pWin = (1-x)/(1-y);
  return -pLoss*loss*(1-refund) + pWin*win;
}
int main(){
  refund = in_nextDouble()/100.;
  p = in_nextDouble()/100.;
  int win, loss, bestwin = 1;
  double best = 0;
  loss = 1;
  while(1){
    if(p == 0) 
      break;
    double prev = 0;
    bool flag = false;
    win=bestwin;
    while(1){
      double cur = solve(win, loss);
      if(cur > best){
        best = cur;
        bestwin = win;
        flag = true;
      }
      if(cur < prev) 
        break;
      prev = cur;
      win++;
    }
    if(!flag) 
      break;
    loss++;
  }
  printf("%.10lf\n", best);
  return 0;
}
