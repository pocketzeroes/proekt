#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  double first;
  double second;
}pair;
int N, K;
pair*cake;
double cnt;
double sum;

double choose(double a, double b){
  if(b < 0 || b > a)
    return 0 ;
  if(b + b > a)
    b = a - b ;
  double r = 1 ;
  for(double i=1; i<=b; i++)
    r = r * (a - i + 1) / i;
  return r ;
}
double incr(int i, int j){
  return(cake[i].second + cake[j].second) * (cake[j].first - cake[i].first) * 0.5;
}
int main(){
  scanf("%d %d", &N, &K);
  cake = calloc(N, sizeof(pair));
  for(int i=0; i<N; i++)
    scanf("%lf %lf", &cake[i].first, &cake[i].second);
  for(int i=0; i<N; i++){
    double p = K * (K - 1) / (double)(N * (N - 1));
    for(int m=1; m<N; m++){
      sum += p * incr(i, (i + m) % N);
      p *= (1 - (K - 2) / (double)(N - m - 1));
    }
  }
  printf("%.15lf\n", sum);
  return 0;
}
