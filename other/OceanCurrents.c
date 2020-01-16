#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}

char  to [1001][1001];
short dis[1001][1001];
int   dir[8][2]={-1,0,-1,1,0,1,1,1,1,0,1,-1,0,-1,-1,-1};

pair q[1001*1001];
int r,c,r1,c1,r2,c2,n,head,tail,tail1,r3,c3,d;

void add(int r1, int c1, int d1){
  if((r1>=0)&&(r1<r)&&(c1>=0)&&(c1<c)&&(dis[r1][c1]==-1)){
    dis[r1][c1]=d1;
    q[tail++]=newpair(r1,c1);
  }
}
int main(){
  scanf("%d %d", &r, &c);
  for(int i=0; i<r; i++){
    scanf("%s", to[i]);
    for(int j=0; j<c; j++)
      to[i][j]-='0';
  }
  scanf("%d", &n);
  while(n--){
    scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
    tail=0;
    for(int i=0; i<r; i++)
      for(int j=0; j<c; j++)
        dis[i][j]=-1;
    add(--r1, --c1, 0);
    head=0;
    while(head < tail){
      for(int i=head; i<tail; i++){
        r3=q[i].first;
        c3=q[i].second;
        d=to[r3][c3];
        add(r3+dir[d][0], c3+dir[d][1], dis[r3][c3]);
      }
      tail1=tail;
      while(head<tail1){
        for(int j=0; j<8; j++)
          add(q[head].first+dir[j][0], q[head].second+dir[j][1], dis[q[head].first][q[head].second]+1);
        head++;
      }
    }
    printf("%d\n", dis[--r2][--c2]);
  }
  return 0;
}
