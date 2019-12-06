#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<math.h>

int g[2048][2048],
    d[2048][2048],
    qx[2048*2048],
    qy[2048*2048];
int qn,i,p,x,y,xx,yy,X,Y;

int try(int a, int b){
  if(qx[i]+a > 2000)
    return 0;
  if(qx[i]+a < 0)
    return 0;
  if(qy[i]+b > 2000)
    return 0;
  if(qy[i]+b < 0)
    return 0;
  if(d[qx[i]+a][qy[i]+b] > d[qx[i]][qy[i]]+1){
    d[qx[i]+a][qy[i]+b] = d[qx[i]][qy[i]]+1;
    qx[qn] = qx[i]+a;
    qy[qn++] = qy[i]+b;
  }
  return 1;
}
int main(){
   while (1 == scanf("%d",&p) && p){
      memset(g,0,sizeof(g));
      memset(d,100,sizeof(d));
      qn = 0;
      for(i=0;i<p;i++){
         scanf("%d %d",&x,&y);
         if (g[x][y] )
           printf("dupe!! %d %d\n",x,y);
         if (i && abs(x-xx) + abs(y-yy) != 1)
           printf("oops! %d %d\n",x,y);
         if (!i){
           X=x;
           Y=y;
         }
         xx = x;
         yy = y;
         g[x][y] = 1;
         d[x][y] = 0;
         qx[qn] = x;
         qy[qn++] = y;
      }
      if (abs(x-X) + abs(y-Y) != 1)
        printf("oop! doesn't return\n");
      assert(1 == scanf("%d",&p) && p);
      for (i=0;i<p;i++){
         scanf("%d %d",&x,&y);
         if (g[x][y] )
           printf("dupe!! %d %d\n",x,y);
         if (i && abs(x-xx) + abs(y-yy) != 1)
           printf("oops! %d %d\n",x,y);
         if (!i) {
           X=x;
           Y=y;
         }
         xx = x;
         yy = y;
         g[x][y] = 2;
      }
      if (abs(x-X) + abs(y-Y) != 1)
        printf("oop! doesn't return\n");
      for (i=0;i<qn;i++){
         if (g[qx[i]][qy[i]] == 2){
            printf("%d\n",d[qx[i]][qy[i]]);
            break;
         }
         try(1,0);
         try(0,1);
         try(-1,0);
         try(0,-1);
      }
   }
   if (p)
     printf("no end of input\n");
   return 0;
}
