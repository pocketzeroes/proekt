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
    int a = in_nextInt();
    int b = in_nextInt();
    int h = in_nextInt();
    int numClimbs = 0;
    double x = h - a;
    if(x > 0.0)
        numClimbs += ceilf(x/(double)(a - b));
    numClimbs++;
    printf("%d\n", numClimbs);
    return 0;
}
