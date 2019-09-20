#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  int first;
  int second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}

int n, t, m;
int bound[100];
pair score[100][2000][10];


bool better(pair*S1, pair*S2){
  int d = (S1->first-S1->second)-(S2->first-S2->second);
  if(d)
    return d > 0;
  return S1->first > S2->first;
}
pair Score(int t, int e, int d){
  if(!t)
    return newpair(0,0);
  if(t == 45)
    d = 0;
#define r score[t][e][d+4]
  if (r.first < 0) {
    for(int i = 0; i <= fmin(e, n); ++i) {
      int dd = 0;
      if (i < bound[t])
        dd = fmin(d, 0)-1;
      if (i > bound[t])
        dd = fmax(d, 0)+1;
      pair next = Score(t-1, e-i, dd % 5);
      next.first += dd == 5;
      next.second += dd == -5;
      if (!i || better(&next, &r))
        r = next;
    }
  }
  return r;
  #undef r
}
int main(){
  scanf("%d%d%d", &n, &t, &m);
  memset(bound, 0, sizeof(bound));
  memset(score, -1, sizeof(score));
  for (int i = 0; i < m; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    for (int x = a; x < b; ++x)
      ++bound[90-x];
  }
  pair r = Score(90, n*t, 0);
  printf("%d %d\n", r.first, r.second);
  return 0;
}

