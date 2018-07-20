#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
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

int main() {
  int n, w;
  scanf("%d %d", &n, &w);
  pair a[n];
  for(int i=0; i<n; ++i)
    scanf("%d %d", &a[i].first, &a[i].second);
  int f[n];
  for(int i=0; i<n; ++i)
    f[i] = a[i].second + (i > 0 ? f[i - 1] : 0);
  for(int i=0; i<n;){
    if(a[i].first == 0){
      ++i;
      continue;
    }
    int j = i+1;
    while(j < n && a[j].first == 1)
      ++j;
    int sum = f[j - 1] - (i > 0 ? f[i - 1] : 0);
    if(sum >= w){
      printf("%d\n", i+1);
      return 0;
    }
    i = j;
  }
  puts("-1");
  return 0;
}
