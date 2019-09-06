#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAXROLL 200
#define MAXAV 11
#define MAXAVV (1<<MAXAV)
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
int a,c,x0;
int rolls[MAXROLL+2];
int best[MAXROLL+2][MAXAVV+2];
int when[MAXROLL+2][MAXAVV+2];
int best_round_score[MAXROLL+2][17][12];
int avv[MAXAV+2];

void genseq(){
  int i;
  long long x;
  x = x0;
  for(i=0;i<MAXROLL;i++){
    x = (x*a+c)&(((long long)1<<32)-1);
    rolls[i] = ((x>>16)%6)+1;
  }
}
void count_score(int *dice, int *ret){
  int i, dcnt[8], dsum=0, maxdcnt=0;
  for(i=1;i<=6;i++) dcnt[i]=0;
  for(i=0;i<5;i++) dcnt[dice[i]]++;
  for(i=1;i<=6;i++) maxdcnt = MAX(maxdcnt, dcnt[i]);
  for(i=0;i<5;i++) dsum+=dice[i];
  for(i=0; i<6;i++){
    ret[i] = (i+1)*dcnt[i+1];
  }
  if(dcnt[2]*dcnt[3]*dcnt[4]*dcnt[5]==1) ret[6] = 30; else ret[6] = 0;
  if(maxdcnt==3 && (dcnt[1]==2 || dcnt[2]==2 || dcnt[3]==2 ||
                    dcnt[4]==2 || dcnt[5]==2 || dcnt[6]==2)) ret[7] = dsum; else ret[7] = 0;
  if(maxdcnt==4)  ret[8] = dsum; else ret[8] = 0;
  if(maxdcnt==5)  ret[9] = 50; else ret[9] = 0;
  ret[10] = dsum;
}
void count_best_round_scores(int from){
  int i,j,k,tmp,tmp2;
  int dice[6];
  int cs_ret[12];
  int rolls_used, diccnt, dcbck, comb;
  for(i=0;i<16;i++) for(j=0;j<11;j++) best_round_score[from][i][j]=-1;
  for(i=0;i<32;i++)
  {
    tmp = i; diccnt = 0;
    for(k=0;k<5;k++)
    {
      if(tmp&1) dice[diccnt++] = rolls[from+k];
      tmp >>=1;
    }
    dcbck = diccnt;
    for(j=0;j<(1<<(5-dcbck));j++)
    {
      diccnt = dcbck;
      tmp = j; tmp2 = 5-diccnt;
      for(k=0;k<tmp2;k++)
      {
        if(tmp&1) dice[diccnt++] = rolls[from+5+k];
        tmp >>=1;
      }
      for(k=from+5+tmp2; diccnt<5; k++)
      {
        dice[diccnt++] = rolls[k];
      }
      rolls_used = k-from;
      count_score(dice, cs_ret);
      for(comb=0;comb<11;comb++)
      {
        tmp = cs_ret[comb];
        best_round_score[from][rolls_used][comb] = MAX(best_round_score[from][rolls_used][comb], tmp);
      }
    }
  }
}
int main(){
  int ii,i,j,k,l,tmp;
  int res, newav;
  for(ii=1;;ii++)
  {
    scanf("%d %d %d ", &a,&c,&x0);
    if(a==0 && c==0 && x0==0) break;
    genseq();
    for(i=0;i<165;i++) count_best_round_scores(i);
    tmp = (1<<11)-1;
    best[0][tmp] = 0;
    when[0][tmp] = ii;
    for(i=0;i<165;i++) for(j=0;j<MAXAVV;j++) if(when[i][j]==ii)
    {
      for(k=5;k<=15;k++)
      {
        tmp = j;
        for(l=0;l<11;l++) { avv[l]=(tmp&1); tmp>>=1; }
        for(l=0;l<11;l++) if(avv[l] && best_round_score[i][k][l]>=0)
        {
          newav = (j^(1<<l));
          assert(newav == j-(1<<l));
          tmp = best[i][j] + best_round_score[i][k][l];
          if(when[i+k][newav]!=ii || best[i+k][newav]<tmp)
          {
            when[i+k][newav] = ii;
            best[i+k][newav] = tmp;
          }
        }
      }
    }
    res=-1;
    for(i=0;i<=165;i++) if(when[i][0]==ii)
    {
      res = MAX(res, best[i][0]);
    }
    printf("%d\n", res);
  }
  return 0;
}