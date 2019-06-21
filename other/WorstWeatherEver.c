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
int upper_bound(pair*a, int n, pair x){
  int l = 0;
  int h = n;
  while(l < h){
    int mid = (l + h) / 2;
    if(cmpP(&x, &a[mid])>=0)
      l = mid + 1;
    else
      h = mid;
  }
  return l;
}
int lower_bound(pair*a, int n, pair x){
  int l = 0;
  int h = n;
  while(l < h){
    int mid = (l + h) / 2;
    if(cmpP(&x, &a[mid])<=0)
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}
/////////////////////////////////
int A, B, C, D, E, F, G, H;

bool solve(int P){
  pair known[55000];
  int  prev [55000],
       next [55000];
  int n, m;
  if (scanf("%d", &n) != 1 || !n)
    return false;
  ++n;
  for (int i = 1; i < n; ++i)
    scanf("%d %d", &known[i].first, &known[i].second);
  known[0] = newPair(-(1<<30), 1<<30);
  known[n] = newPair(  1<<30,  1<<30);
  for (int i = 1, j = 0, k = n; i <= n; j = i, k = n-i, ++i) {
    while (known[j].second < known[i].second)
      j = prev[j];
    prev[i] = j;
    while (known[k].second < known[n-i].second)
      k = next[k];
    next[n-i] = k;
  }
  ++n;
  scanf("%d", &m);
  if (P)
    printf("\n");
  for(int i = 0; i < m; ++i){
    int x, y;
    scanf("%d %d", &y, &x);
    int iX = upper_bound(known, n, newPair(x, -1));
    int iY = upper_bound(known, n, newPair(y, -1));
    pair*X = &known[iX];
    pair*Y = &known[iY];
    if(X->first == x && Y->first == y){
      pair*Z = known + prev[X - known];
      if(Y != Z)
        printf("false\n"), ++A;
      else if(X - Y == x - y)
        printf("true\n"), ++B;
      else
        printf("maybe\n"), ++C;
    }
    else if (X->first == x) {
      pair*Z = known + prev[X - known];
      if (Z->first < y)
        printf("maybe\n"), ++D;
      else
        printf("false\n"), ++E;
    }
    else if (Y->first == y) {
      pair*Z = known + next[Y - known];
      if (Z->first > x)
        printf("maybe\n"), ++F;
      else
        printf("false\n"), ++G;
    }
    else
      printf("maybe\n"), ++H;
  }
  return true;
}
int main(){
  A = B= C= D= E= F= G= H= 0;
  for (int i = 0; solve(i); ++i);
    fprintf(stderr, "case distr: %d %d %d %d %d %d %d %d\n", A, B, C, D, E, F, G, H);
  return 0;
}
