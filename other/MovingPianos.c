#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define WED(x) (((x) % 7)>=5)
#define MAX_DAYS (100)

int Weeks [MAX_DAYS*MAX_DAYS];
int Weeks2[MAX_DAYS*MAX_DAYS];

void clearweeks(){
  int i,j;
  for (i=0;i<MAX_DAYS;i++){
    for (j=0;j<=i;j++){
      Weeks [j+i*MAX_DAYS] = 0;
      Weeks2[j+i*MAX_DAYS] = 0;
    }
  }
}
int solve(int* pWeek, int weekends, int p, int m){
  int i,j,k,cap;
  for (i=0;i<MAX_DAYS;i++){
    if (!weekends && WED(i))
      cap = 0;
    else
      cap = p;
    for (j=i;j<MAX_DAYS && cap;j++)
      for (k=0;k<=i && cap;k++)
        if (pWeek[k+j*MAX_DAYS]){
          if (pWeek[k+j*MAX_DAYS]<=cap){
            cap-=pWeek[k+j*MAX_DAYS];
            m-=pWeek[k+j*MAX_DAYS];
            pWeek[k+j*MAX_DAYS] = 0;
          }
          else{
            m-= cap;
            pWeek[k+j*MAX_DAYS] -= cap;
            cap = 0;
          }
        }
  }
  return (m==0);
}
int main(){
  int i,j,m,p,n,b,e;
  scanf("%d",&n);
  for (i=0;i<n;i++){
    clearweeks();
    scanf("%d %d",&m,&p);
    p=p/2;
    for (j=0;j<m;j++){
      scanf("%d %d",&b,&e);
      Weeks [b-1+(e-1)*MAX_DAYS]++;
      Weeks2[b-1+(e-1)*MAX_DAYS]++;
    }
    if (solve(Weeks,0,p,m)){
      printf("fine\n");
    }
    else if (solve(Weeks2,1,p,m)){
      printf("weekend work\n");
    }
    else{
      printf("serious trouble\n");
    }
  }
  return 0;
}
