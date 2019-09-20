#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
enum{ MOD = 1000003};

int cmpstr(const void*p1, const void*p2){
  return strcmp(*(char* const*) p1, *(char* const*) p2);
}
int main(){
  char strings[2010][1010], *lights[1010], *switches[1010];
  int n, m;
  scanf("%d%d", &n, &m);
  memset(strings, 0, sizeof(strings));
  for(int i = 0; i < n; ++i)
    lights[i] = strings[i], switches[i] = strings[i+n];
  for(int j = 0; j < m; ++j){
    scanf("%s", strings[2*n]);
    for(int i = 0; i < n; ++i)
      switches[i][j] = strings[2*n][i];
    scanf("%s", strings[2*n]);
    for(int i = 0; i < n; ++i)
      lights[i][j] = strings[2*n][i];
  }
  qsort(lights  , n, sizeof(char*), cmpstr);
  qsort(switches, n, sizeof(char*), cmpstr);
  int res = 1;
  for(int i = 0; i < n; ++i){
    int j = i;
    for(; j < n && !strcmp(switches[i], switches[j]); ++j)
      if(strcmp(lights[j], switches[i]))
        res = 0;
    for(int k = 1; k <= (j-i); ++k)
      res = (res*k) % MOD;
    i = j-1;
  }
  printf("%d\n", res);
  return 0;
}
