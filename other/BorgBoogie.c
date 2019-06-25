#include<stdio.h>
#include<string.h>
#include<math.h>

int conn[500][500];
int nconn[500];
double prob[500], probtemp[500];
int N,L;
int walk[500];

void Walk(double* pd, double* ps){
  for(int i = 0; i < N; ++i){
    pd[i] = 0;
    for(int j = 0; j < nconn[i]; ++j)
      pd[i] += ps[conn[i][j]] / nconn[conn[i][j]];
  }
  for(int i = 0; i < N; ++i)
    pd[i] = (2*pd[i] + ps[i])/3;
}
double max(double a, double b){
  return (a > b ? a : b);
}
int main(){
  scanf("%d %d", &N, &L);
  for(int i = 0; i < L; ++i)
    scanf("%d", &walk[i]);
  for(int i = 0; i < N; ++i){
    scanf("%d", &nconn[i]);
    for(int j = 0; j < nconn[i]; ++j)
      scanf("%d", &conn[i][j]);
    prob[i] = 1.0/N;
  }
  int loops = 0;
  for(double diff = 1; diff > 1e-12;){
    ++loops;
    Walk(probtemp, prob);
    Walk(prob, probtemp);
    diff = 0;
    for(int i = 0; i < N; ++i)
      diff = max(diff, fabs(prob[i] - probtemp[i]));
  }
  double ret = 0;
  for(int i = 0; i < L-1; ++i){
    int curr = walk[i];
    int next = walk[i+1];
    ret += prob[curr];
    prob[curr] = 0;
    ret += prob[next]/nconn[next];
    for(int j = 0; j < N; ++j)
      probtemp[j] = prob[j];
    for(int j = 0; j < N; ++j){
      prob[j] = 0;
      for(int k = 0; k < nconn[j]; ++k){
        int other = conn[j][k];
        if(j != curr || other != next) 
          prob[j] += probtemp[other] / nconn[other];
      }
    }
  }
  ret += prob[walk[L-1]];
  printf("%.6lf\n", 1-ret);
  return 0;
}
