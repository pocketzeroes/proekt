#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define min(X,Y) ((X) < (Y)? (X):(Y))
#define max(X,Y) ((X) > (Y)? (X):(Y))

#define EPS   1e-8
#define DELTA 1e-7
enum{ MAXN = 10};
enum{ MAXM = 10};


int n, m;
double p[MAXM];
double probW[MAXM];

int pos[MAXM];
double cProb[MAXN];

int lowestUniqueNumber(){
  for (int i = 0; i < m; i++)
    if (pos[i]==1)
      return i;
  return -1;
}
double placement(int number, double sumOver, int k){
  if (k == n){
    if (lowestUniqueNumber() == number)
      return cProb[n-1];
    else
      return 0;
  }
  double sum = 0;
  for (int i = 0; i <= number; i++) {
    pos[i]++;
    cProb[k] = cProb[k-1]*p[i];
    sum += placement(number, sumOver, k+1);
    pos[i]--;
  }
  if (number+1 < m) {
    pos[number+1]++;
    cProb[k] = cProb[k-1]*sumOver;
    sum += placement(number, sumOver, k+1);
    pos[number+1]--;
  } 
  return sum;
}
void probWinning(){
  double sumOver = 0;
  memset(probW, 0, sizeof(probW));
  for (int i = m-1; i >=0; i--) {
    pos[i]++;
    cProb[0] = p[i];
    probW[i] = placement(i, sumOver, 1)/p[i];
    pos[i]--;
    sumOver += p[i];
  }
}
void normalize(){
  double sum = 0;
  for (int i = 0; i < m; i++) sum += p[i];
  for (int i = 0; i < m; i++) p[i] /= sum;
}
int main(){
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) p[i] = pow(0.5, i+1);
  normalize();
  double maior, menor;
  do {
    probWinning();
    double avg = 0;
    maior = 0; menor = 1;
    for (int i = 0; i < m; i++) {
      maior = max(maior, probW[i]);
      menor = min(menor, probW[i]);
      avg += probW[i];
    }
    avg /= m;
    double sum = 0;
    for (int i = 0; i < m; i++) {
      p[i] += 0.5*(probW[i]-avg);
      sum += p[i];
    }
    for (int i = 0; i < m; i++) 
      p[i] /= sum;
  } while (maior - menor > DELTA);
  for (int i = 0; i < m; i++)
    printf("%0.5lf\n", p[i]);
  return 0;
}
