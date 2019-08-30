#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
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
int cmpP(pair a, pair b){
  if(a.first  != b.first) return(a.first  < b.first )?-1:1;
  if(a.second != b.second)return(a.second < b.second)?-1:1;
  return 0;
}
typedef struct{
  int   first;
  pair second;
}trip;
trip newTrip(int a, pair b){
  trip rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpT(const void*pa, const void*pb){
  trip*a = (trip*)pa;
  trip*b = (trip*)pb;
  if(a->first != b->first)return(a->first < b->first )?-1:1;
  return cmpP(a->second, b->second);
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
trip*pushbackT(trip*array, int *size, trip value){
  trip*output = resizeArray(array, trip, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  trip*ptr;
  int sz;
}vect;
vect newVecT() {
  vect rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}


int main(){
  int N;
  while(scanf("%d", &N)==1){
    int c[2*N][2*N];clr(c);
    for(int i=0; i<2*N; i++)
      c[i][i] = 1000000001;
    vect e=newVecT();//of trip{int, pair}
    for(int i = 0; i < N; i++)
      for(int j = i+1; j < N; j++){
        int d;
        scanf("%d", &d);
        c[i][j+N] = fmax(c[i][j+N], d);
        c[j][i+N] = fmax(c[j][i+N], d);
        e.ptr = pushbackT(e.ptr, &e.sz, newTrip(d, newPair(i, j)));
      }
    if (N <= 2){puts("0"); continue;}
    for (int k = 0; k < 2*N; k++)
      for (int i = 0; i < 2*N; i++)
        for (int j = 0; j < 2*N; j++){
          c[i][j] = fmax(c[i][j], fmin(c[i][k], c[k][j]));
        }
    qsort(e.ptr, e.sz, sizeof(trip), cmpT);
    int ret = e.ptr[e.sz-1].first;
    for(int i = e.sz-1; i >= 0; i--){
      int mx = 0;
      for (int j = 0; j < N; j++) 
        mx = fmax(mx, fmin(c[j][j+N], c[j+N][j]));
      ret = fmin(ret, mx + e.ptr[i].first);
      int a = e.ptr[i].second.first, 
          b = e.ptr[i].second.second;
      if (c[a+N][b] < 1000000001)
        for (int j = 0; j < 2*N; j++)
          for (int k = 0; k < 2*N; k++){
            c[j][k] = fmax(c[j][k], fmin(c[j][a+N], c[b][k]));
          }
      if (c[a][b+N] < 1000000001)
        for (int j = 0; j < 2*N; j++)
          for (int k = 0; k < 2*N; k++){
            c[j][k] = fmax(c[j][k], fmin(c[j][a], c[b+N][k]));
          }
      if (c[b+N][a] < 1000000001)
        for (int j = 0; j < 2*N; j++)
          for (int k = 0; k < 2*N; k++){
            c[j][k] = fmax(c[j][k], fmin(c[j][b+N], c[a][k]));
          }
      if (c[b][a+N] < 1000000001)
        for (int j = 0; j < 2*N; j++)
          for (int k = 0; k < 2*N; k++){
            c[j][k] = fmax(c[j][k], fmin(c[j][b], c[a+N][k]));
          }
    }
    printf("%d\n", ret);
  }
  return 0;
}
