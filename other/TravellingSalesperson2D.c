#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}
double in_nextDouble(){
  double xx;
  scanf("%lf", &xx);
  return xx;
}

typedef struct pt{
    double x, y;
}pt;
pt newpt(double x, double y) {
    return(pt){x,y};
}

int *order;
bool*visited;
pt  *points;
int  points_len;



void search(int start, int n){
    if(n == points_len)
        return;
    double dis  = INT_MAX;
    int    best = -1;
    for(int i=0; i<points_len; i++){
        if(!visited[i]){
            double d = sqrt(pow(points[start].x - points[i].x, 2.0) + pow(points[start].y - points[i].y, 2.0));
            if(d < dis){
                dis  = d;
                best = i;
            }
        }
    }
    visited[best] = true;
    order  [best] = n;
    search(best, ++n);
}
int main(){
    int n = in_nextInt();
    points = calloc(n, sizeof(pt));
    points_len = n;
    for(int i=0; i<n; i++){
        double x = in_nextDouble();
        double y = in_nextDouble();
        pt p = newpt(x, y);
        points[i] = p;
    }
    visited = calloc(n, sizeof(bool));
    order   = calloc(n, sizeof(int ));
    visited[0] = true;
    order  [0] = 0;
    search(0, 1);
    for(int i=0; i<n; i++)
        printf("%d\n", order[i]);
    return 0;
}
