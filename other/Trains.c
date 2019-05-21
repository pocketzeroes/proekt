#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char place[400][100],
     from [100],
     to   [100];
int  start[400], 
     d    [400][400];
typedef struct{
  int go, dur;
}tt;
tt travel[400];
int nt;

int comp(const void*pa, const void*pb){
  tt*a=(tt*)pa;
  tt*b=(tt*)pb;
   if (a->go == b->go)
     return b->dur-a->dur;
   return a->go - b->go;
}
int s,z,i,j,k,m,h,n,N,T,S,time;

int main(){
   scanf("%d", &N);
   while (N--){
      if (z++)
        printf("\n");
      memset(d,32,sizeof(d));
      scanf("%d",&T);
      s = 0;
      for (i=0;i<T;i++) {
         scanf("%d %d:%d",&S,&h,&m);
         start[s] = h*60 + m;
         for (j=0;j<S;j++,s++){
            scanf(" %s",&place[s]);
            if (j < S-1) {
               scanf("%d:%d",&h,&m);
               start[s+1] = (start[s] + h*60 + m) % (60*24);
               d[s][s+1] = h*60+m;
            }
         }
      }
      for (i=0;i<s;i++) for (j=0;j<s;j++){
         if (strcmp(place[i],place[j])) 
           continue;
         d[i][j] = (24*60 + start[j] - start[i]) % (24*60);
      }
      for (i=0;i<s;i++) for (j=0;j<s;j++) for (k=0;k<s;k++){
         if (d[j][i]+d[i][k] < d[j][k]) d[j][k] = d[j][i]+d[i][k];
      }
      scanf(" %s %s",from,to);
      nt = 0;
      for (i=0;i<s;i++) {
         if (strcmp(place[i],from)) continue;
         for (j=0;j<s;j++) {
            if (strcmp(place[j],to)) continue;
            if (d[i][j] > 32<<24) continue;
            travel[nt].go = start[i];
            travel[nt++].dur = d[i][j];
         }
      }
      qsort(travel,nt,sizeof(tt),comp);
      for (i=0;i<nt;i++) {
         for (j=i+1;j<nt;j++) {
            if (travel[j].go >= travel[i].go && 
                travel[j].go+travel[j].dur <= travel[i].go+travel[i].dur) break;
         }
         if (j<nt) continue;
         for (j=0;j<nt;j++) {
            if (travel[j].go+60*24 >= travel[i].go &&
                travel[j].go+60*24+travel[j].dur <= travel[i].go+travel[i].dur) break;
         }
         if (j<nt) continue;
         printf("%02d:%02d %d:%02d\n",travel[i].go/60,travel[i].go%60,
                      travel[i].dur/60, travel[i].dur%60);
      }
   }
   return 0;
}
