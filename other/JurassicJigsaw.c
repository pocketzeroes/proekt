#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
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
///////////////////////////////////
enum{ maxn = 1000};
int N, K, D[maxn], P[maxn];
char*S[maxn];

int sim(int a, int b){
  int r = 0;
  for(int i = (0); i != (K); ++i)
    r += S[a][i] != S[b][i];
  return r;
}
int main(){
  scanf("%d %d", &N, &K);
  for(int i = (0); i != (N); ++i)
    S[i] = getstr();
  for(int i = (0); i != (N); ++i)
    D[i] = sim(0, i);
  D[0] = -1;
  vecp ret = newVecP();
  int sum = 0;
  for(int i = (0); i != (N - 1); ++i){
    int nxt = -1, nxtD = 1e8;
    for(int j = (0); j != (N); ++j)
      if (D[j] >= 0 && D[j] < nxtD)
        nxtD = D[nxt = j];
    ret.ptr = pushbackP(ret.ptr, &ret.sz, newPair(nxt, P[nxt]));
    sum += D[nxt];
    D[nxt] = -1;
    for(int j = (0); j != (N); ++j)
      if(D[j] >= 0){
        int alt = sim(nxt, j);
        if(alt < D[j])
          D[j] = alt, P[j] = nxt;
      }
  }
  printf("%d\n", sum);
  for(int z=0;z<ret.sz;z++){pair pr = ret.ptr[z];
    printf("%d %d\n", pr.first, pr.second);
  }
  return 0;
}
