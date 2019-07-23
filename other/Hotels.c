#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}

typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
/////////////////////////

int F, E, R[123], M[123], d[123][123], c;
pair s[123456];

void doit(){
  c = 1;
  scanf("%d %d", &F, &E);
  s[0] = newPair(0,E);
  for (int i = 0; i < E; i++){
    scanf("%d %d", &R[i], &M[i]);
    for (int j = R[i]; j < F; j += M[i]) {
      s[c] = newPair(j,i);
      c++;
    }
  }
  s[c] = newPair(F-1,E+1);
  c++;
  E+=2;
  for (int i = 0; i < E; i++) {
    for (int j = 0; j < E; j++)
        d[i][j] = 1001001001;
    d[i][i] = 0;
  }
  qsort(s, c, sizeof(pair), cmpP);
  for (int i = 0; i < c-1; i++){
    int e1 = s[i].second;
    int e2 = s[i+1].second;
    d[e1][e2] = min(d[e1][e2], s[i+1].first - s[i].first);
    d[e2][e1] = d[e1][e2];
  }
  for (int i = 0; i < E; i++)
  for (int j = 0; j < E; j++)
  for (int k = 0; k < E; k++)
    d[j][k] = min(d[j][k], d[j][i] + d[i][k]);
  int max = -1;
  int argmax = -1;
  for (int i = 0; i < c-1; i++) {
    int bottom = s[i].first;
    int dbottom = d[E-2][s[i].second];
    int top = s[i+1].first;
    int dtop = d[E-2][s[i+1].second];
    int mid = (bottom + top + dtop - dbottom) / 2;
    if (dbottom + (mid - bottom) > max) {
      max = dbottom + mid - bottom;
      argmax = mid;
    }
  }
  printf("%d %d\n", max, argmax);
}
int main(){
  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; t++)
    doit();
  return 0;
}
