#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int  rr[20];
char input[5][1000];

void prep(){
  rr[0]=32319;
  rr[1]=31744;
  rr[2]=24253;
  rr[3]=32437;
  rr[4]=31879;
  rr[5]=30391;
  rr[6]=30399;
  rr[7]=31777;
  rr[8]=32447;
  rr[9]=32439;
}
int nonempty(int y){
 for(int _n=(5),x=0; x<_n; ++x)
    if (input[x][y])
      return 1;
 return 0;
}
int mask(int y){
 int m=0;
 for(int _n=(3),dy=0; dy<_n; ++dy)
    for(int _n=(5),x=0; x<_n; ++x)
      if (input[x][y+dy])
        m|=(1<<(5*dy+x));
 return m;
}
int main(){
 prep();
 int m,d,n,nn;
        int r;
 for(int _n=(5),x=0; x<_n; ++x) gets(input[x]);
 for(int _n=(5),x=0; x<_n; ++x) if ((strlen(input[x])+1)%4!=0) goto hell;
 nn=strlen(input[0]);
 n=(nn+1)/4;
 for(int _n=(5),x=0; x<_n; ++x) for(int _n=(nn),i=0; i<_n; ++i){
  if (input[x][i]==' ') input[x][i]=0; else
  if (input[x][i]=='*') input[x][i]=1; else goto hell;
 }
 for(int _n=(n-1),y=0; y<_n; ++y) if (nonempty(3+4*y)) goto hell;
 r=0;
 for(int _n=(n),y=0; y<_n; ++y){
  m=mask(y*4);
  d=-1;
  for(int _n=(10),i=0; i<_n; ++i) if (rr[i]==m) d=i;
  if (d<0) goto hell;
  r=r*10+d;
 }
 if (r%6!=0) goto hell;
 printf("BEER!!\n");
 return 0;
hell:
 printf("BOOM!!\n");
 return 0;
}
