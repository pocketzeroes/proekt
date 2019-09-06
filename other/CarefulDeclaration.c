#include<stdio.h>
#include<string.h>
#include<stdlib.h>

enum{ MAXW   = 2100};
enum{ MAXLEN = 1000};

typedef struct{
  char*w;
  int  sentence;
  int  pos;
}Words;

char word[2][MAXW+2][MAXLEN+2];
int n,n0,n1;
Words w    [2* MAXW+2];
int numseq [2][MAXW+2], diffwcnt;
int best   [MAXW+2][MAXW+2];
int bestlen[MAXW+2][MAXW+2];
int bestbeg[MAXW+2][MAXW+2];


int w_cmp(const void *e1, const void *e2){
  return strcmp(((Words *)e1)->w, ((Words *)e2)->w);
}
int main(){
  int i,j,tmp;
  while(1){
    for(i=0;; i++){
      scanf(" %s ", word[0][i]);
      if(word[0][i][0]=='.')
        break;
      w[i].w = word[0][i];
      w[i].sentence = 0;
      w[i].pos = i;
    }
    n0 = i;
    if(n0==0)
      break;
    for(i=0;; i++){
      scanf(" %s ", word[1][i]);
      if(word[1][i][0]=='.')
        break;
      w[n0+i].w = word[1][i];
      w[n0+i].sentence = 1;
      w[n0+i].pos = i;
    }
    n1 = i;
    n=n0+n1;
    qsort(w,n,sizeof(w[0]),w_cmp);
    diffwcnt=0;
    for(i=0;i<n;i++){
      if(i>0 && strcmp(w[i].w, w[i-1].w))
        diffwcnt++;
      numseq[w[i].sentence][w[i].pos] = diffwcnt;
    }
    for(i=0;i<n0;i++) { bestlen[i][n1] = n0-i; bestbeg[i][n1] = numseq[0][i]; best[i][n1] = 1; }
    for(i=0;i<n1;i++) { bestlen[n0][i] = n1-i; bestbeg[n0][i] = numseq[1][i]; best[n0][i] = 2; }
    bestlen[n0][n1] = 0; bestbeg[n0][n1] = 0; best[n0][n1] = -1;
    for(i=n0-1;i>=0;i--) for(j=n1-1;j>=0;j--){
      if(numseq[0][i]==numseq[1][j]){
        bestlen[i][j] = 1+bestlen[i+1][j+1];
        bestbeg[i][j] = numseq[0][i];
        best[i][j] = 0;
        continue;
      }
      if(bestlen[i+1][j] <  bestlen[i][j+1] ||
        (bestlen[i+1][j] == bestlen[i][j+1] && numseq[0][i] < numseq[1][j])){
        bestlen[i][j] = bestlen[i+1][j]+1;
        bestbeg[i][j] = numseq[0][i];
        best[i][j] = 1;
      }
      else{
        bestlen[i][j] = bestlen[i][j+1]+1;
        bestbeg[i][j] = numseq[1][j];
        best[i][j] = 2;
      }
    }
    i=0; j=0;
    while(1){
      tmp = best[i][j];
      if(tmp==0 || tmp==1)
        printf("%s ", word[0][i]);
      if(tmp==2)
        printf("%s ", word[1][j]);
      if(tmp==-1)
        break;
      if(tmp==0 || tmp==2)
        j++;
      if(tmp==0 || tmp==1)
        i++;
    }
    printf(".\n");
  }
  return 0;
}
