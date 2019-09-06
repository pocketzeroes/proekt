#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
enum{ maxsize=30+5};
const int MX[]={-1,1,0,0};
const int MY[]={0,0,-1,1};
int sizeX,sizeY;
char A[maxsize][maxsize];
int  D[maxsize][maxsize];
int  sizeQ;
int  Q[maxsize*maxsize];

int ID(int x,int y){
  return (x-1)*sizeY+y;
}
void addnode(int x,int y,int d){
  if (x<1 || x>sizeX || y<1 || y>sizeY)
    return;
  if (A[x][y]=='.')
    return;
  if (D[x][y]>=0)
    return;
  D[x][y]=d;
  Q[sizeQ++]=x*10000+y;
}
int main(){
  int testcase;
  scanf("%d",&testcase);
  for (int caseId=1;caseId<=testcase;caseId++){
    printf("Case #%d: ",caseId);
    scanf("%d%d",&sizeX,&sizeY);
    for (int i=1;i<=sizeX;i++)
      scanf("%s",A[i]+1);
    A[1][1]='G';
    int result=0;
    while (1){
      sizeQ=0;
      memset(D,255,sizeof(D));
      for (int i=1;i<=sizeX;i++)
        for (int j=1;j<=sizeY;j++)
          if (A[i][j]=='G')
            addnode(i,j,0);
      for (int cl=0;cl<sizeQ;cl++){
        int x=Q[cl]/10000;
        int y=Q[cl]%10000;
        for (int d=0;d<4;d++){
          int x2=x+MX[d],y2=y+MY[d];
          addnode(x2,y2,D[x][y]+1);
        }
      }
      int x=-1,y=-1,m=10000000;
      for (int i=1;i<=sizeX;i++)
        for (int j=1;j<=sizeY;j++)
          if (A[i][j]=='T' && D[i][j]>=0 && D[i][j]<m){
            m=D[i][j];
            x=i;
            y=j;
          }
      if (x<0)
        break;
      bool first=true;
      while (1){
        if (A[x][y]=='G' || A[x][y]=='P')
          break;
        result+=D[x][y];
        if (first)
          first=false,A[x][y]='G';
        else
          A[x][y]='P';
        for (int d=0;d<4;d++){
          int x2=x+MX[d],y2=y+MY[d];
          if (x2>=1 && x2<=sizeX && y2>=1 && y2<=sizeY && D[x2][y2]>=0 && D[x2][y2]+1==D[x][y]){
            x=x2;
            y=y2;
            break;
          }
        }
      }
    }
    for (int i=1;i<=sizeX;i++)
      for (int j=1;j<=sizeY;j++)
        if (A[i][j]=='#')
          result+=D[i][j];
    printf("%d\n",result);
    fflush(stdout);
  }
  return 0;
}
