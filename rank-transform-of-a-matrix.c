#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define REP(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)
int**newmat(int x, int y){
  int**rv = calloc(x, sizeof(int*));
  for(int i=0; i<x; i++)
    rv[i] = calloc(y, sizeof(int));
  return rv;
}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
typedef struct{
  int first, second, third;
}trip;
trip newtrip(int a, int b, int c){
  return(trip){a,b,c};
}
int cmpT(const void*pa, const void*pb){
  trip*a = (trip*)pa;
  trip*b = (trip*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  if(a->third  != b->third) return(a->third  < b->third )?-1:1;
  return 0;
}
/////////////////////////////
int X[330000];
int**matrixRankTransform(int**matrix, int matrixSz, int*matrix0sz, int*rsz, int**csz){
    clr(X);
    int R = matrixSz;
    int C = matrix0sz[0];
    int**ans=newmat(R,C);
    int RR[R]; fill(RR, R, 1);
    int CC[C]; fill(CC, C, 1);
    trip E[R*C];
    int Esz=0;
    REP(i, R) 
      REP(j, C) 
        E[Esz++]=newtrip(matrix[i][j], i, j);
    qsort(E, Esz, sizeof(trip), cmpT);
    for(int i=0; i<Esz;){
        int j = i;
        while(j < Esz && E[i].first == E[j].first)
            j++;
        while(1){
          bool update = false;
          for(int k=i; k<j; k++){
            int d=E[k].first;
            int r=E[k].second;
            int c=E[k].third;
            X[k] = fmax(RR[r], CC[c]);
            if(RR[r] < X[k] || CC[c] < X[k])
                update = true;
            RR[r] = CC[c] = X[k];
          }
          if(!update) 
            break;
        }
        for(int k=i; k<j; k++){
          int d=E[k].first;
          int r=E[k].second;
          int c=E[k].third;
          ans[r][c] = X[k];
          RR[r] = CC[c] = X[k] + 1;
        }
        i = j;
    }
    int*cols=calloc(R, sizeof(int));
    for(int z=0; z<R; z++)
        cols[z]=C;
   *csz=cols;
   *rsz=R;
    return ans;
}
