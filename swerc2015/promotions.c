#include <stdio.h>
#include <string.h>

enum{ MAX = 5002};
int adj[MAX][MAX], nef[MAX];
int rev[MAX][MAX], ner[MAX];
int N;
int done[MAX], ndone;
int q[MAX], nq;

inline int Bfs(int a[MAX][MAX], int na[MAX], int i){
  nq = 1;
  q[0] = i;
  done[i] = ++ndone;
  int nfound = -1, w, k, j;
  for (k = 0; k < nq; ++k) {
    w = q[k];
    ++nfound;
    for (j = 0; j < na[w]; ++j)
      if (done[a[w][j]] != ndone) {
        q[nq++] = a[w][j];
        done[a[w][j]] = ndone;
      }
  }
  return nfound;
}
int main(){
  int i, j, P, A, B;
  scanf("%d %d %d %d", &A, &B, &N, &P);
  while (P--) {
    scanf("%d %d", &i, &j);
    adj[i][nef[i]++] = j;
    rev[j][ner[j]++] = i;
  }
  int mustA = 0, mustB = 0, cant = 0, nchildren, npred;
  for (i = 0; i < N; ++i){
    nchildren = Bfs(adj, nef, i);
    npred = Bfs(rev, ner, i);
    mustA += A >= (N - nchildren);
    mustB += B >= (N - nchildren);
    cant += npred >= B;
  }
  printf("%d\n%d\n%d\n", mustA, mustB, cant);
  return 0;
}
