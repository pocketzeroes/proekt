#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
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
///////////////
vecp implications[30][2];
int val[30], val2[30];

bool doit(int n, int v){
  if (val[n] != -1)
    return val[n] == v;
  val[n] = v;
  vecp*imp = &implications[n][v];
  for(int i = 0; i < imp->sz; i++)
    if(!doit(imp->ptr[i].first, imp->ptr[i].second))
      return false;
  return true;
}
int main(){
  int N, M;
  while(scanf("%d %d", &N, &M)==2 && N){
    for (int i = 0; i < N; i++)
      for (int j = 0; j < 2; j++)
        implications[i][j].sz=0;
    for (int i = 0; i < M; i++) {
      char a, b;
      int an, bn;
      scanf("%d%c %d%c", &an, &a, &bn, &b);
      implications[an][a=='h'].ptr = pushbackP(implications[an][a=='h'].ptr, &implications[an][a=='h'].sz, newPair(bn, b=='w'));
      implications[bn][b=='h'].ptr = pushbackP(implications[bn][b=='h'].ptr, &implications[bn][b=='h'].sz, newPair(an, a=='w'));
    }
    memset(val, -1, sizeof(val));
    if (!doit(0, 1))
      goto fail;
    for (int i = 0; i < N; i++){
      if (val[i] == -1){
        memcpy(val2, val, sizeof(val));
        if (!doit(i, 0)) {
          memcpy(val, val2, sizeof(val));
          if (!doit(i, 1))
            goto fail;
        }
      }
    }
    for (int i = 1; i < N; i++){
      if (i > 1) 
        printf(" ");
      printf("%d%c", i, (val[i] ? 'w' : 'h'));
    }
    puts("");
    continue;
  fail:
    puts("bad luck");
  }
  return 0;
}
