#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp=a; a=b; b=tp; }while(0)

int N;
int*es;
int**edge;

void setEdgeRootedTree(int N__, int M, int A[], int B[]){
  int root=0;
  int reorder=0;
  int*cnv = NULL;
  int i;
  int j;
  int k;
  int *dist;
  int *q;
  int qs;
  int qe;
  int *ind;
  N = N__;
  es   = calloc(N, sizeof(int));
  edge = calloc(N, sizeof(int*));
  for(i=(0);i<(N);i++)
    es[i] = 0;
  for(i=(0);i<(M);i++){
    es[A[i]]++;
    es[B[i]]++;
  }
  for(i=(0);i<(N);i++)
    edge[i] = calloc(es[i], sizeof(int));
  for(i=(0);i<(N);i++)
    es[i] = 0;
  for(i=(0);i<(M);i++){
    edge[A[i]][es[A[i]]++] = B[i];
    edge[B[i]][es[B[i]]++] = A[i];
  }
  dist = calloc(N, sizeof(int));
  q    = calloc(N, sizeof(int));
  ind  = calloc(N, sizeof(int));
  if(cnv==NULL){
    cnv = calloc(N, sizeof(int));
  }
  for(i=(0);i<(N);i++){
    dist[i] = -1;
  }
  dist[root] = 0;
  qs = qe = 0;
  q[qe++] = root;
  while(qs < qe){
    i = q[qs++];
    for(j=(0);j<(es[i]);j++){
      k = edge[i][j];
      if(dist[k]==-1){
        dist[k] = dist[i] + 1;
        q[qe++] = k;
      }
    }
  }
  if(reorder == 0){
    for(i=(0);i<(N);i++){
      cnv[i] = i;
    }
    for(i=(0);i<(N);i++){
      ind[i] = i;
    }
  }
  else{
    for(i=(0);i<(N);i++){
      cnv[i] = q[i];
    }
    for(i=(0);i<(N);i++){
      ind[cnv[i]] = i;
    }
  }
  for(i=(0);i<(N);i++){
    es[i] = 0;
  }
  for(i=(0);i<(M);i++){
    j = A[i];
    k = B[i];
    if(dist[j] > dist[k]){
      swap(j, k);
    }
    es[ind[j]]++;
  }
  for(i=(0);i<(N);i++){
    edge[i] = calloc(es[i], sizeof(int));
  }
  for(i=(0);i<(N);i++){
    es[i] = 0;
  }
  for(i=(0);i<(M);i++){
    j = A[i];
    k = B[i];
    if(dist[j] > dist[k]){
      swap(j, k);
    }
    j = ind[j];
    k = ind[k];
    edge[j][es[j]++] = k;
  }
}
////////////

int a[100000];
int b[100000];
int cnt[100000][26];
int*res;
char*s;

void solve(int n){
  int Q5VJL1cS, k;
  for(k=0; k<26; k++)
    cnt[n][k] = 0;
  cnt[n][s[n]]++;
  for(Q5VJL1cS=0; Q5VJL1cS<es[n]; Q5VJL1cS++){
    int i = edge[n][Q5VJL1cS];
    solve(i);
    for(k=0; k<26; k++)
      cnt[n][k] += cnt[i][k];
  }
  res[n] = cnt[n][s[n]];
}

int*countSubTrees(int n, int**edges, int edgesSz, int*edges0sz, char*labels, int*rsz){
  N=0;
  es=NULL;
  edge=NULL;
  int i, j;
  for(i=(0);i<(n-1);i++){
    {
      int t_ynMSdg = (edges[i][0]);
      int KrdatlYV = (edges[i][1]);
      a[i] = t_ynMSdg;
      b[i] = KrdatlYV;
    }
  }
  setEdgeRootedTree(n, n-1, a, b);
  res = calloc(n, sizeof(int));
  s = strdup(labels);
  for(i=0; i<n; i++)
    s[i] -= 'a';
  for(j=0; j<n; j++)
    for(i=0; i<26; i++)
      cnt[j][i] = 0;
  solve(0);
  free(es);
  for(int i=0;i<edgesSz;i++)
    free(edge[i]);
  free(edge);
  free(s);
 *rsz=n;
  return res;
}
