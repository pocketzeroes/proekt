#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
typedef struct{
  int  first;
  char second;
}pair;
pair newpair(int a, char b){
  return(pair){a,b};
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

vecp re6enie;

void razporedi(int a[500], int n, char X, char Y){
  int index[500];
  for(int i=0; i<n; ++i)
    index[i] = i;
  for(int i=0; i<n; ++i)
    for(int j=i+1; j<n; ++j)
      if(a[j]<a[i]){
        swap(a[i], a[j]);
        swap(index[i], index[j]);
      }
  for(int i=0; i<n; ++i)
    for(; a[i]>i; --a[i])
      pbp(re6enie, newpair(index[i]+1, X));
  for(int i = n-1; i >= 0; --i)
    for(; a[i]<i; ++a[i])
      pbp(re6enie, newpair(index[i]+1, Y));
}
int main(){
  int n;
  scanf("%d", &n);
  int r[500], s[500];
  for(int i=0; i<n; ++i){
    scanf("%d %d", &r[i], &s[i]);
    --r[i]; --s[i];
  }
  razporedi(r, n, 'U', 'D');
  razporedi(s, n, 'L', 'R');
  printf("%d\n", re6enie.sz);
  for(int z=0;z<re6enie.sz;z++){pair it = re6enie.ptr[z];
    printf("%d %c\n", it.first, it.second);
  }
  return 0;
}
