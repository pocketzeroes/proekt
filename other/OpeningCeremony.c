#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int min(int a,int b){return a<b?a:b;}
int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}

int h[200000];

int main(){
  int n;
  scanf("%d", &n);
  for(int i = 0; i < n; ++i)
    scanf("%d", h+i);
  qsort(h, n, sizeof(int), cmp);
  int r = n;
  for(int i = 0; i < n; ++i)
    r = min(r, h[i]+n-i-1);
  printf("%d\n", r);
  return 0;
}
