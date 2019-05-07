#include<stdio.h>
#include<string.h>
#include<stdlib.h>

enum{BUFF_SIZE = 26000};
char d[BUFF_SIZE][17];
int dp[BUFF_SIZE];
int z;
int n;

typedef struct adj adj;
struct adj{
  int i;
  adj*next;
};

adj*a   [BUFF_SIZE];
int q   [BUFF_SIZE];
int dist[BUFF_SIZE];

int compar(const void*pa, const void*pb){
  int*a = (int*)pa;
  int*b = (int*)pb;
  int r;
  char at = d[*a][z];
  char bt = d[*b][z];
  if (at)
    d[*a][z] = '_';
  if (bt)
    d[*b][z] = '_';
  r = strcmp(d[*a],d[*b]);
  d[*a][z] = at;
  d[*b][z] = bt;
  return r;
}
int main(){
  int i,j,k,m;
  for(n=0;;n++){
    gets(d[n]);
    if (!d[n][0])
      break;
  }
  for (i=0;i<n;i++)
    dp[i] = i;
  for (z=0;z<16;z++){
    qsort(dp, n, sizeof(int), compar);
    for (i=0;i<n;i++){
      for (j=i+1;j<n;j++){
        if (!compar(&dp[i],&dp[j])) {
          adj*t    = (adj*)malloc(sizeof(adj));
          t->i     = dp[j];
          t->next  = a[dp[i]];
          a[dp[i]] = t;
          t        = (adj*)malloc(sizeof(adj));
          t->i     = dp[i];
          t->next  = a[dp[j]];
          a[dp[j]] = t;
        }
        else
          break;
      }
    }
  }
  for (m=0;;m++){
    int i1, i2;
    char w1[20], w2[20];
    int qn;
    if (2 != scanf(" %s %s",w1,w2))
      break;
    if (m)
      printf("\n");
    for (i1=0;i1<n && strcmp(w1,d[i1]);i1++);
    for (i2=0;i2<n && strcmp(w2,d[i2]);i2++);
    for (i=0;i<n;i++)
      dist[i] = 999999;
    dist[i2] = 0;
    for (i=0;i<n;i++)
      q[i] = -1;
    q[0] = i2;
    qn = 1;
    for (i=0;i<qn && q[i] != i1;i++){
      adj*p;
      for (p=a[q[i]];p;p=p->next){
        if (dist[p->i] == 999999){
          dist[p->i] = dist[q[i]] + 1;
          q[qn++] = p->i;
        }
      }
    }
    if (i1 != n && i2 != n && dist[i1] != 999999){
      int this = i1;
      printf("%s\n", w1);
      while (this != i2){
        adj*p;
        for(p=a[this]; p && dist[p->i] != dist[this]-1; p=p->next);
        this = p->i;
        printf("%s\n", d[this]);
      }
    }
    else
      printf("No solution.\n");
  }
  return 0;
}
