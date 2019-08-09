#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

typedef struct{
  int x, y, r, a, b, l;
}Circle;
Circle newCircle(int x, int y, int r, int a, int b, int l){
  Circle rez;
  rez.x = x;
  rez.y = y;
  rez.r = r;
  rez.a = a;
  rez.b = b;
  rez.l = l;
  return rez;
}
int cmpC(const void*pa, const void*pb){
  Circle*ac=(Circle*)pa;
  Circle*bc=(Circle*)pb;
  Circle a = *ac;
  Circle b = *bc;
  if(a.r!=b.r)return(a.r<b.r)?-1:1;
  return(a.l<b.l)?-1:1;
}
bool isInside(Circle a, Circle b){
  return((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)<b.r*b.r);
}
int main(){
  int N = in_nextInt();
  Circle circles[N]; memset(circles, 0, sizeof(circles));
  for(int i=0; i<N; i++){
    int rx = in_nextInt();
    int ry = in_nextInt();
    int rr = in_nextInt();
    int ra = in_nextInt();
    int rb = in_nextInt();
    circles[i] = newCircle(rx, ry, rr, ra, rb, i+1);
  }
  qsort(circles, N, sizeof(Circle), cmpC);
  int values      [N]; memset(values      ,0, sizeof(values      ));
  int maxValues   [N]; memset(maxValues   ,0, sizeof(maxValues   ));
  int ancestors   [N]; memset(ancestors   ,0, sizeof(ancestors   ));
  int minAncestors[N]; memset(minAncestors,0, sizeof(minAncestors));
  int parent      [N]; memset(parent      ,0, sizeof(parent      ));
  int total = 0;
  for(int i=0; i<N; i++){
    Circle c = circles[i];
    for(int j = i + 1; j < N; j++){
      if(isInside(c, circles[j])){
        if(parent[i] == 0) 
           parent[i] = j;
        ancestors[i]++;
        values   [i] += (ancestors[i] % 2 == 1 ? c.a : c.b);
        maxValues[i] = max(maxValues[i], values[i]);
      }
    }
    total += maxValues[i];
    int curValue = values[i];
    for(int j = ancestors[i]; j >= 0; j--){
      if(curValue == maxValues[i])
        minAncestors[i] = j;
      curValue -= (j % 2 == 1 ? c.a : c.b);
    }
  }
  printf("%d\n", total);
  bool active[N]; memset(active, 0, sizeof(active));
  bool locked[N]; memset(locked, 0, sizeof(locked));
  for(int i = 0; i < N; i++){
    if(i > 0)
      printf(" ");
    memset(locked, 0, sizeof(locked));
    int best = -1;
    for(int j = 0; j < N; j++){
      if(locked[j]){
        locked[parent[j]] = true;
        continue;
      }
      if(active[j])
        continue;
      if(values[j] == maxValues[j] && (best == -1 || circles[j].l < circles[best].l))
        best = j;
      if(ancestors[j] == minAncestors[j])
        locked[parent[j]] = true;
    }
    active[best] = true;
    for(int j=0; j<best; j++){
      if(isInside(circles[j], circles[best])){
        values   [j] -= (ancestors[j] % 2 == 1 ? circles[j].a : circles[j].b);
        ancestors[j]--;
      }
    }
    printf("%d", circles[best].l);
  }
  puts("");
  return 0;
}
