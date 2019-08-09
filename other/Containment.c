#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}

int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

int**newmat(int x, int y){
  int**rv = calloc(x, sizeof(int*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(int));
  return rv;
}

enum{gn = 1002};

int augment(int**g, int**now, int at, int sink, bool*seen, int sofar){
   if(at == sink)
      return sofar;
   if(seen[at])
      return 0 ;
   seen[at] = true;
   for(int i=0; i<gn; i++){
      if(now[at][i] < g[at][i]){
         int t = augment(g, now, i, sink, seen, min(sofar, g[at][i]-now[at][i]));
         if(t > 0){
            now[at][i] += t;
            now[i][at] -= t;
            return t ;
         }
      }
   }
   return 0 ;
}
int**Flow(int**g, int src, int sink){
   int**now = newmat(gn, gn);
   bool sn[gn];
   do{
      memset(sn, 0, sizeof(sn));
   }
   while(augment(g, now, src, sink, sn, 1000000000) > 0);
   return now;
}
int ind(int x, int y, int z){
   return x + 10 * (y + 10 * z);
}
void connect2(int**g, int g1, int g2){
   g[g1][g2] = g[g2][g1] = 1 ;
}
void connect1(int**g, int g1, int g2, int quant){
   g[g1][g2] += quant;
}
int main(){
   int src  = 1000;
   int sink = 1001;
   int**flow = newmat(gn, gn);
   for(int x=0; x<10; x++){
      for(int y=0; y<10; y++){
         for(int z=0; z<9; z++){
            connect2(flow, ind(x,y,z), ind(x,y,z+1));
            connect2(flow, ind(y,z,x), ind(y,z+1,x));
            connect2(flow, ind(z,x,y), ind(z+1,x,y));
         }
         connect1(flow, ind(x,y,0), sink, 1);
         connect1(flow, ind(x,y,9), sink, 1);
         connect1(flow, ind(x,0,y), sink, 1);
         connect1(flow, ind(x,9,y), sink, 1);
         connect1(flow, ind(0,x,y), sink, 1);
         connect1(flow, ind(9,x,y), sink, 1);
      }
   }
   int R = in_nextInt();
   for(int i=0; i<R; i++){
      int x = in_nextInt();
      int y = in_nextInt();
      int z = in_nextInt();
      connect1(flow, src, ind(x,y,z), 6);
   }
   int**r = Flow(flow, src, sink);
   int sum = 0;
   for(int i=0; i<gn; i++)
      sum += r[src][i];
   printf("%d\n", sum);
   return 0;
}
