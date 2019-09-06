#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>


bool Read(int*first){
  char c,r=0,n=0;
 *first=0;
  for(;;){
   c=getchar();
    if ((c<0) && (!r))
     return(0);
    if ((c=='-') && (!r))
     n=1;
    else
    if ((c>='0') && (c<='9'))
    *first = *first * 10+c-'0',r=1;
    else if (r)
     break;
  }
  if (n)
    *first = - *first;
  return 1;
}
int main(){
 int T,R,C;
 int i,j;
 bool r,d;
 char G[101][101];
 bool right[101][101],down[101][101];
 Read(&R),Read(&C);
  for (i=0; i<R; i++)
   scanf("%s",&G[i]);
 memset(right,0,sizeof(right));
 memset(down,0,sizeof(down));
 for (i=0; i<R; i++)
 {
  for (j=0; j<C; j++)
  {
   r=j ? right[i][j-1] : 0;
   d=i ? down[i-1][j] : 0;
    if (G[i][j]=='A')
    {
      if ((r) || (d))
       goto Imp;
     right[i][j]=down[i][j]=0;
    }
    if (G[i][j]=='B')
    {
      if (r==d)
       goto Imp;
     right[i][j]=r;
     down[i][j]=d;
    }
    if (G[i][j]=='C')
    {
     right[i][j]=!r;
     down[i][j]=!d;
    }
    if (G[i][j]=='D')
    {
      if ((!r) || (!d))
       goto Imp;
     right[i][j]=down[i][j]=1;
    }
  }
 }
 for (i=0; i<R; i++)
  if (right[i][C-1])
   goto Imp;
 for (j=0; j<C; j++)
  if (down[R-1][j])
   goto Imp;
 printf("Possible\n");
 return(0);
Imp:;
 printf("Impossible\n");
 return(0);
}
