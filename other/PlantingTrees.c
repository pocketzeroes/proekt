#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cmp(const void *b, const void *a){//rev
  return ( *(int*)a - *(int*)b );
}
int main(){
  int n, res = 0;
  scanf("%d\n",&n);
  int t[n];
  for(int i=0; i<n; i++)
    scanf("%d", &t[i]);
  qsort(t, n, sizeof(int), cmp);//rev
  for(int i=0; i<n; i++)
    if(i+2+t[i]>res)
      res = i+2+t[i];
  printf("%d\n", res);
  return 0;
}
