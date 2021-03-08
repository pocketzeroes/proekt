#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
typedef long long ll;

int N;
int*es;
int**edge;
void setEdge(int N__, int M, int A[], int B[]){
  int i;
  N = N__;
  es   = calloc(N, sizeof(int));
  edge = calloc(N, sizeof(int*));
  for(i=(0);i<(N);i++){
    es[i] = 0;
  }
  for(i=(0);i<(M);i++){
    es[A[i]]++;
    es[B[i]]++;
  }
  for(i=(0);i<(N);i++){
    edge[i] = calloc(es[i], sizeof(int));
  }
  for(i=(0);i<(N);i++){
    es[i] = 0;
  }
  for(i=(0);i<(M);i++){
    edge[A[i]][es[A[i]]++] = B[i];
    edge[B[i]][es[B[i]]++] = A[i];
  }
}

int m;
int a[100000];
int b[100000];
int deg[100000];

int*countPairs(int n, int**edges, int edgesSz, int*edges0sz, int*queries, int queriesSz, int*rsz){
  int i;
  ll c, r, f;
  int*res = calloc(queriesSz, sizeof(int));
  m = edgesSz;
  for(i=0; i<m; i++){
    int Q5VJL1cS = ((edges[i][0]-1));
    int e98WHCEY = ((edges[i][1]-1));
    a[i]=Q5VJL1cS;
    b[i]=e98WHCEY;
  }
  setEdge(n, m, a, b);
  for(i=0; i<n; i++){
    deg[i] = es[i];
  }
  qsort(deg, n, sizeof(int), cmp);
  for(i=0; i<n; i++){
    qsort(edge[i], es[i], sizeof(int), cmp);
  }
  for(int z=0; z<queriesSz; z++){int q = queries[z];
    q++;
    c = 0;
    for(i=0; i<n; i++){
      int YREPHmFM;
      int tU__gIr_;
      int a2conNHc;
      int hCmBdyQB;
      tU__gIr_ = 0;
      a2conNHc = n;
      while(tU__gIr_ < a2conNHc){
        if((tU__gIr_ + a2conNHc)%2==0){
          hCmBdyQB = (tU__gIr_ + a2conNHc) / 2;
        }
        else{
          hCmBdyQB = (tU__gIr_ + a2conNHc + 1) / 2;
        }
        if(es[i] + deg[hCmBdyQB-1] < q){
          tU__gIr_ = hCmBdyQB;
        }
        else{
          a2conNHc = hCmBdyQB - 1;
        }
      }
      c += n -a2conNHc;
      if(es[i] + es[i] >= q){
        c--;
      }
      f = -1;
      for(YREPHmFM=(0);YREPHmFM<(es[i]);YREPHmFM++){
        int j = edge[i][YREPHmFM];
        if(f != j){
          f = j;
          r = -1;
        }
        r++;
        if(es[i] + es[j] == q + r){
          c--;
        }
      }
    }
    res[z]=(c/2);
  }
 *rsz=queriesSz;
  return res;
}
