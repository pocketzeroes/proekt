#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

typedef struct{
   int x, r, loc;
}Can;
Can newCan(int x,int r,int l){
   return(Can){x,r,l};
}
bool canReach(Can lhs, Can rhs){
   return abs(lhs.x-rhs.x) <= lhs.r;
}
int cmpC(const void*pa, const void*pb){
   Can*lhs=(Can*)pa;
   Can*rhs=(Can*)pb;
   return lhs->x - rhs->x;
}
int N;
Can*vs;
bool hasChanged;
int*stk;
int*farthestRight;
int*farthestLeft;

void update(int i){
   while (stk[0] > 0 && canReach(vs[i], vs[stk[stk[0]]])){
      int j = stk[stk[0]--];
      if(farthestRight[i] < farthestRight[j]){
         farthestRight[i] = farthestRight[j];
         hasChanged = true;
      }
      if(farthestLeft[i] > farthestLeft[j]){
         farthestLeft[i] = farthestLeft[j];
         hasChanged = true;
      }
   }
   stk[++stk[0]] = i;
}
int main(){
   int N = in_nextInt();
   vs = calloc(N, sizeof(Can));
   for(int i=0; i<N; i++){
      int xx,yy;
      scanf("%d%d", &xx, &yy);
      vs[i] = newCan(xx,yy,i);
   }
   qsort(vs,N,sizeof(Can),cmpC);
   stk = calloc(N+10, sizeof(int));
   farthestRight = calloc(N,sizeof(int));
   farthestLeft  = calloc(N,sizeof(int));
   for(int i=0; i<N; i++)
      farthestRight[i] = farthestLeft[i] = i;
   hasChanged = true;
   while(hasChanged){
      hasChanged = false;
      for (int i=N-1; i>=0; i--)
         update(i);
      stk[0] = 0;
      for (int i=0; i<N; i++)
         update(i);
      stk[0] = 0;
   }
   for(int i=0; i<N; i++){
      vs[i].x = vs[i].loc;
      vs[i].loc = i;
   }
   qsort(vs, N, sizeof(Can), cmpC);
   for(int i=0; i<N; i++){
      int j = vs[i].loc;
      printf("%d", farthestRight[j]-farthestLeft[j]+1);
      printf(" ");
   }
   puts("");
   return 0;
}
