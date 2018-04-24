#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#if 1
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
  int *output = resizeArray(array, int, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

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
  if(a->first == b->first)
    return (a->second < b->second)?-1:1;
  return (a->first < b->first)?-1:1;
}
#endif

int main() {
  int N, M;
  while(scanf("%d %d", &N, &M)==2){
    pair v[N]; memset(v, 0, sizeof(v));
    for(int i = 0; i < N; i++)
      v[i].second = i;
    for(int i = 0; i < M; i++){
      int x, y;
      scanf("%d %d", &x, &y);
      v[x].first++; 
      v[y].first++;
    }
    qsort(v, N, sizeof(pair), cmpP);
    int ret = 0, tot = M*2;
    for(int i = N-1; tot > 2*N-2; i--){
      int amt = min(tot-(2*N-2), v[i].first-1);
      tot -= amt;
      v[i].first -= amt;
      ret++;
    }
    qsort(v, N, sizeof(pair), cmpP);
    printf("%d\n", ret);
    printf("%d %d\n", N, N-1);
    if(N == 2){
      puts("0 1");
      continue; 
    }
    vec st = newVec();
    int i;
    for(i = 0; v[i].first == 1; i++){
      st.ptr = pushback(st.ptr, &st.sz, v[i].second);
    }
    for(; i < N; i++){
      for(int j = 0; j < v[i].first-(i+1 < N); j++){
        printf("%d %d\n", v[i].second, st.ptr[st.sz-1]);
        st.sz--;
      }
      st.ptr = pushback(st.ptr, &st.sz, v[i].second);
    }
  }
}
