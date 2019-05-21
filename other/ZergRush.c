#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpP(pair a, pair b){
  if(a.first  != b.first) return(a.first  < b.first )?-1:1;
  if(a.second != b.second)return(a.second < b.second)?-1:1;
  return 0;
}

enum{ MAXRC = 210};

int  gri [MAXRC][MAXRC],hp [MAXRC][MAXRC];
int  ngri[MAXRC][MAXRC],nhp[MAXRC][MAXRC];
int  dis [MAXRC][MAXRC];
int  q   [MAXRC*MAXRC][2],tail;
int  attack[3],n,turn,a1,d1,a2,d2;
char from[MAXRC][MAXRC][8],
     ft  [MAXRC][MAXRC];
char s   [MAXRC];
char move[MAXRC][MAXRC];
int  dir [9][2]={-1,0,-1,1,0,1,1,1,1,0,1,-1,0,-1,-1,-1,0,0};
int  dir1[4][2]={-1,0,0,1,1,0,0,-1};
char key [4]=".12";

void show(){
  for(int i=(1); i<(n+1); i++){
    for(int j=(1); j<(n+1); j++)
      printf("%c",key[gri[i][j]],hp[i][j]);
    printf("\n");
  }
}
void add(int r1,int c1,int d1){
  if((r1>0)&&(r1<=n)&&(c1>0)&&(c1<=n)&&(dis[r1][c1]==10000)){
    dis[r1][c1] = d1;
    q[tail][0]  = r1;
    q[tail++][1]= c1;
  }
}
void stop(int r1,int c1){
  move[r1][c1]=8;
  for(int i=(0); i<(8); i++) 
    if((r1>=0)&&(c1>=0)&&(r1<=n+1)&&(c1<=n+1)&& (from[r1][c1][i])&&(move[r1+dir[i][0]][c1+dir[i][1]]!=8))
      stop(r1+dir[i][0],c1+dir[i][1]);
}
int main(){
  scanf("%d", &n);
  while(n){
    memset(gri,0,sizeof(gri));
    scanf("%d%d%d%d",&a1,&d1,&a2,&d2);
    attack[1]=a1-d2+5;
    attack[2]=a2-d1+5;
    for(int i=(1); i<(n+1); i++){
      scanf("%s",s);
      for(int j=(0); j<(n); j++){
        if(s[j]!='.'){
          gri[i][j+1]=s[j]-'0';
          hp[i][j+1]=35;
        }
      }
    }
    scanf("%d",&turn);
    while(turn--){
      memset(from,0,sizeof(from));
      memset(ft,0,sizeof(ft));
      for(int side=(1); side<(3); side++){
        tail=0;
        for(int i=(0); i<(n+2); i++)
          for(int j=(0); j<(n+2); j++)
            dis[i][j]=10000;
        for(int i=(1); i<(n+1); i++)
          for(int j=(1); j<(n+1); j++)
            if(gri[i][j]+side==3)
              add(i,j,0);
        if(tail==0)
          goto done;
        for(int i=(0); i<(tail); i++)
          for(int j=(0); j<(4); j++)
            add(q[i][0]+dir1[j][0],q[i][1]+dir1[j][1], dis[q[i][0]][q[i][1]]+1);
        for(int i=(1); i<(n+1); i++){
          for(int j=(1); j<(n+1); j++){
            if(gri[i][j]==side){
              int d=0;
              for(int k=(1); k<(8); k++)
                if(dis[i+dir[k][0]][j+dir[k][1]] < dis[i+dir[d][0]][j+dir[d][1]])
                  d=k;
              if(dis[i+dir[d][0]][j+dir[d][1]]==0){
                move[i][j]=8;
                hp[i+dir[d][0]][j+dir[d][1]]-=attack[side];
              }
              else{
                move[i][j]=d;
                from[i+dir[d][0]][j+dir[d][1]][(d+4)%8]=1;
                ft[i+dir[d][0]][j+dir[d][1]]++;
              }
            }
          }
        }
      }
      for(int i=(1); i<(n+1); i++)
        for(int j=(1); j<(n+1); j++)
          if(hp[i][j]<=0)
            gri[i][j]=hp[i][j]=0;
      for(int i=(1); i<(n+1); i++)
        for(int j=(1); j<(n+1); j++)
          if((gri[i][j])&&(move[i][j]==8))
            stop(i,j);
      else if(ft[i][j]>1){
        int d1=-1;
        for(int k=(0); k<(8); k++)
          if((from[i][j][k])&&((d1==-1)|| cmpP(newPair(i+dir[k ][0], j+dir[k ][1]),
                                               newPair(i+dir[d1][0], j+dir[d1][1]))<0 ))
            d1=k;
        for(int k=(0); k<(8); k++)
          if((from[i][j][k])&&(d1!=k))
            stop(i+dir[k][0],j+dir[k][1]);
      }
      memset(ngri,0,sizeof(ngri));
      memset(nhp,0,sizeof(nhp));
      for(int i=(1); i<(n+1); i++)
        for(int j=(1); j<(n+1); j++)
          if(gri[i][j]){
            int i1=i+dir[move[i][j]][0];
            int j1=j+dir[move[i][j]][1];
            ngri[i1][j1]=gri[i][j];
            nhp[i1][j1]=hp[i][j]+(hp[i][j]<35);
          }
      for(int i=(1); i<(n+1); i++)
        for(int j=(1); j<(n+1); j++){
          gri[i][j]=ngri[i][j];
          hp[i][j]=nhp[i][j];
        }
    }
  done:
    show();
    n=0;
//    scanf("%d",&n);
    if(n)
      printf("\n");
  }
  return 0;
}
