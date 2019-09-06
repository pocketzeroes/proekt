#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define MAX(a,b) (((a)>(b))?(a):(b))
enum{ MAXN = 4000   };
enum{ MAXM = 1000000};
enum{ MAXW = 100000 };

typedef struct{
  int a,b,w;
  int intree;
} Edge;

int n,m;
Edge ed[MAXM];

int treew, treesize;
int replw[MAXN][MAXN];

int edge_cmp(const void *e1, const void *e2){
  return ((const Edge *)e1)->w - ((const Edge *)e2)->w;
}
int ca[MAXN];
int cb[MAXN];
int cacnt, cbcnt;
int result;

int main(){
  int ii,i,j,tmpa,tmpb,tmpw;
  int ci,cj;
  while(1){
    n=m=-1;
    scanf(" %d %d ", &n, &m);
    if(n<0 || m<0)
      return 0;
    for(i=0;i<m;i++){
      scanf(" %d %d %d ", &(ed[i].a), &(ed[i].b), &(ed[i].w));
      ed[i].a--;
      ed[i].b--;
      ed[i].intree = 0;
    }
    qsort(ed,m,sizeof(ed[0]),edge_cmp);
    for(i=0;i<n;i++)
      for(j=0;j<n;j++)
        replw[i][j] = -1;
    for(i=0;i<n;i++)
      replw[i][i] = 0;
    treesize = 0;
    treew = 0;
    for(ii=0;ii<m;ii++){
      tmpa = ed[ii].a;
      tmpb = ed[ii].b;
      tmpw = ed[ii].w;
      if(replw[tmpa][tmpb] != -1)
        continue;
      ed[ii].intree=1;
      cacnt = cbcnt = 0;
      for(i=0;i<n;i++){
        assert(replw[i][tmpa] == -1 || replw[i][tmpb] == -1);
        if(replw[i][tmpa] != -1)
          ca[cacnt++] = i;
        if(replw[i][tmpb] != -1)
          cb[cbcnt++] = i;
      }
      for(i=0;i<cacnt;i++)
        for(j=0;j<cbcnt;j++){
          ci = ca[i];
          cj = cb[j];
          if(ci!=cj)
            replw[cj][ci] = replw[ci][cj] = MAX(replw[ci][tmpa],MAX(tmpw,replw[cj][tmpb]));
        }
      treew += tmpw;
      treesize++;
      if(treesize == n-1)
        break;
    }
    if(treesize < n-1){
      printf("disconnected\n");
      continue;
    }
    result = treew;
    for(i=0;i<m;i++){
      tmpw = treew-ed[i].w-replw[ed[i].a][ed[i].b];
      if(tmpw<result){
        result = tmpw;
      }
    }
    printf("%d\n", result);
  }
  return 0;
}
