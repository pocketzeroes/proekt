#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{MAXN = 100001};

typedef struct edge{
   int         src,
               dst;
   int         color;
   int         state;
   struct edge*next;
}edge;

edge newedge(int src_, int dst_, int color_, edge*next_){
   edge rv;
   rv.src   = src_;
   rv.dst   = dst_;
   rv.color = color_;
   rv.state = 0;
   rv.next  = next_;
   return rv;
}
edge*heads[  MAXN],
     edges[2*MAXN];
int edgealloc;
int colorcount[MAXN];
int edgecount [MAXN];
char badnode  [MAXN];
int n;

void addedge(int src_, int dst_, int c_){
   edge *e = edges + edgealloc++;
   *e = newedge(src_, dst_, c_, heads[src_]);
   heads[src_] = e;
   edgecount[src_]++;
}
edge*q[2*MAXN];
int main(){
   scanf("%d", &n);
   for(int i=1; i<n; i++){
      int a, b, c;
      scanf("%d %d %d", &a, &b, &c);
      addedge(a, b, c);
      addedge(b, a, c);
   }
   int goodnodes = n;
   for(int src=0; src<n; src++)
      if(edgecount[src] > 2) {
         for(edge *e = heads[src]; e; e=e->next)
            colorcount[e->color]++;
         for(edge *e = heads[src]; e; e=e->next)
            if(colorcount[e->color] > 1)
               e->state = 1;
         for(edge *e = heads[src]; e; e=e->next)
            colorcount[e->color] = 0;
      }
      else if(edgecount[src] == 2 && heads[src]->color == heads[src]->next->color){
         heads[src]->state = 1;
         heads[src]->next->state = 1;
      }
   int qput = 0;
   int qget = 0;
   for(int i=0; i<2*n; i++)
      if(edges[i].state)
         q[qput++] = &edges[i];
   while(qget < qput){
      edge *e = q[qget++];
      if(badnode[e->dst] < 2){
         if(badnode[e->dst] == 0)
            goodnodes--;
         badnode[e->dst]++;
         for(edge *e2 = heads[e->dst]; e2; e2=e2->next)
            if(e2->state == 0 && e2->dst != e->src){
               q[qput++] = e2;
               e2->state = 1;
            }
      }
   }
   printf("%d\n", goodnodes);
   for(int i=1; i<=n; i++)
      if(!badnode[i])
         printf("%d\n", i);
   return 0;
}
