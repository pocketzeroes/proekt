#include<stdio.h>
#include<stdlib.h>

typedef struct{
  long x,y,x1,y1;
}e;
long x[101], y[101];

e up[101], dn[101];
int n, nup, ndn;
long top,top1,top2,bot,bot1,bot2;
long long area;

int cmp(const void*pa, const void*pb){
  e*a=(e*)pa;
  e*b=(e*)pb;
  if (b->y > a->y) 
    return 1;
  if (b->y < a->y) 
    return -1;
  return b->y1 - a->y1;
}
int main(){
  int i,j,k;
  for (n=0;2 == scanf("%d%d",&x[n],&y[n]);n++);
  x[n] = x[0]; y[n] = y[0];
  for (i=0;i<n;i++) {
     if (x[i] < x[i+1]) {
        if (y[i] < y[i+1]) {
           up[nup].x = x[i];
           up[nup].y = y[i];
           up[nup].x1 = x[i+1];
           up[nup++].y1 = y[i+1];
        }
        else {
           dn[ndn].x = x[i];
           dn[ndn].y = y[i];
           dn[ndn].x1 = x[i+1];
           dn[ndn++].y1 = y[i+1];
        }
     }
     else if (x[i+1] < x[i]) {
        if (y[i+1] < y[i]) {
           up[nup].x = x[i+1];
           up[nup].y = y[i+1];
           up[nup].x1 = x[i];
           up[nup++].y1 = y[i];
        }
        else {
           dn[ndn].x = x[i+1];
           dn[ndn].y = y[i+1];
           dn[ndn].x1 = x[i];
           dn[ndn++].y1 = y[i];
        }
     }
  }
  qsort(up, nup, sizeof(e), cmp);
  qsort(dn, ndn, sizeof(e), cmp);
  up[nup].x    = 0;
  up[nup].y    = -1;
  up[nup].x1   = 1000000;
  up[nup++].y1 = -1;
  dn[ndn].x    = 0;
  dn[ndn].y    = -1;
  dn[ndn].x1   = 1000000;
  dn[ndn++].y1 = -1;
  for (i=0;i<1000000;i++) {
     for (j=0;up[j].x > i || up[j].x1 <= i;j++);
     for (k=0;dn[k].x > i || dn[k].x1 <= i;k++);
     while(1){
        bot1 = up[j].y+((long long)i-up[j].x)*(up[j].y1-up[j].y)/(up[j].x1-up[j].x);
        bot2 = dn[k].y+((long long)(i+1-dn[k].x)*(dn[k].y1-dn[k].y)-(dn[k].x1-dn[k].x)+1)/(dn[k].x1-dn[k].x);
        if (bot1 > bot2) {
           bot = bot1;
           for (j++;up[j].x > i || up[j].x1 <= i;j++);
        }
        else if (bot2 > bot1){
           bot = bot2;
           for (k++;dn[k].x > i || dn[k].x1 <= i;k++);
        }
        else break;
           
        top1 = up[j].y+((long long)(i+1-up[j].x)*(up[j].y1-up[j].y)+(up[j].x1-up[j].x)-1)/(up[j].x1-up[j].x);
        top2 = dn[k].y+((long long)i-dn[k].x)*(dn[k].y1-dn[k].y)/(dn[k].x1-dn[k].x);
        if (top1 > top2) {
           top = top1;
           for (j++;up[j].x > i || up[j].x1 <= i;j++);
        }
        else if (k < ndn && top2 > top1){
           top = top2;
           for (k++;dn[k].x > i || dn[k].x1 <= i;k++);
        }
        else {
          fprintf(stderr,"oops!\n;"); *(char *)0 = 1;
        }
        if (bot > top) area = area + bot - top;
     }
  }
  printf("%lld\n",area);
  return 0;
}
