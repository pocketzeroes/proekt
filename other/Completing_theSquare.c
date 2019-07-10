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

int main(){
    int ax = in_nextInt();
    int ay = in_nextInt();
    int bx = in_nextInt();
    int by = in_nextInt();
    int cx = in_nextInt();
    int cy = in_nextInt();
    int dx, dy;
    while((bx-ax)*(cx-ax) + (by-ay)*(cy-ay) != 0){
        int oldax = ax, olday = ay;
        ax = bx; ay = by; bx = cx; by = cy; cx = oldax; cy = olday; 
    }
    dx = bx + cx - ax; dy = by + cy - ay;
    printf("%d %d\n", dx, dy);
    return 0;
}
