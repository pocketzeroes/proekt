#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

typedef struct pair{
  char first;
  char*second;
}pair;

int cmp(const void*pa, const void*pb){
  pair*p1=(pair*)pa;
  pair*p2=(pair*)pb;
  return (128-p1->first < 128-p2->first)?1:-1;
}

char buff[100000];
int main() {
  int n;
  scanf("%d", &n);
  pair a[n];
  for(int i=0;i<n;i++){
    scanf("%s %c", &buff, &a[i].first);
    a[i].second=strdup(buff);
  }
  qsort(a, n, sizeof(pair), cmp);
  for(int i=0;i<n;i++){
    puts( a[i].second );
  }
  return 0;
}





