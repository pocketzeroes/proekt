#include<stdio.h>
#include<stdlib.h>
enum{ MAX = 100};
FILE *f1, *f2;
int K,N,M;
char **A, **B, **h;
char s[MAX][MAX];

void init() {
  int i;
  f1 = stdin;
  f2 = stdout;
  A = calloc(MAX, sizeof(char*));
  B = calloc(MAX, sizeof(char*));
  h = calloc(MAX, sizeof(char*));
  for (i=0; i<MAX; i++){
    A[i] = calloc(MAX, sizeof(char));
    B[i] = calloc(MAX, sizeof(char));
    h[i] = calloc(MAX, sizeof(char));
  }
}
void deinit(){
  int i;
  for (i=0; i<MAX; i++){
    free(A[i]);
    free(B[i]);
    free(h[i]);
  }
  free(A);
  free(B);
  free(h);
}
void flip(int r, char** w){
  int i;
  for(i=0; i<M; i++)
    w[r][i] = 1 - w[r][i];
}
void exchange(int c1, int c2, char** w){
  int i,p;
  for(i=0; i<N; i++){
    p = w[i][c1];
    w[i][c1] = w[i][c2];
    w[i][c2] = p;
  }
}
void blueColumn(int c, char** w){
  int i;
  for(i=0; i<N; i++)
    if(w[i][c] == 1)
      flip(i,w);
}
int cmp(const void *a, const void *b){
  char *col1,*col2;
  char i,n1,n2,ret;
  col1 = (char *)a;
  col2 = (char *)b;
  n1 = 0;
  n2 = 0;
  for (i=0; i<N; i++){
    n1 += col1[i];
    n2 += col2[i];
    if (col1[i]<col2[i])
      ret = 1;
    if (col1[i]>col2[i])
      ret = -1;
  }
  if (n1<n2)
    return 1;
  if (n1>n2)
    return -1;
  return ret;
}
void sort(char** w){
  int i,j;
  for (i=0; i<N; i++)
    for (j=0; j<M; j++)
      s[j][i] = w[i][j];
  qsort((void *)s,M,sizeof(s[0]),cmp);
  for (i=0; i<N; i++)
    for (j=0; j<M; j++)
      w[i][j] = s[j][i];
}
int compare(){
  int i,j;
  for (i=0; i<N; i++)
    for (j=0; j<M; j++)
      if (A[i][j] != B[i][j])
        return 0;
  return 1;
}
int possible() {
  int i,j,k;
  for (i=0; i<N; i++)
    for (j=0; j<M; j++)
      h[i][j] = B[i][j];
  blueColumn(0,A);
  sort(A);
  for (k=0; k<M; k++) {
    blueColumn(k,B);
    sort(B);
    if (compare())
      return 1;
    for (i=0; i<N; i++)
      for (j=0; j<M; j++) B[i][j] = h[i][j];
  }
  return 0;
}
int main() {
  int i,j,k;
  char pom[10];
  init();
  fscanf(f1,"%d ",&K);
  for (i=0; i<K; i++) {
    fscanf(f1,"%d %d ",&N,&M);
    for (j=0; j<N; j++)
      for (k=0; k<M; k++){
        fscanf(f1,"%s ",pom);
        A[j][k] = (pom[0] == 'R');
      }
    for (j=0; j<N; j++)
      for (k=0; k<M; k++){
        fscanf(f1,"%s ",pom);
        B[j][k] = (pom[0] == 'R');
      }
    if (possible()) fprintf(f2,"YES\n");
    else fprintf(f2,"NO\n");
  }
  deinit();
  return 0;
}