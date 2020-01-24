#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef struct{
  int first, second;
}pair;

int main(){
  while(1){
    int n, x, y;
    scanf("%d", &n);
    if(!n)
      break;
    pair a[n];
    for(int i=0; i<n; i++){
      scanf("%d %d", &x, &y);
      a[i] = (pair){x, y};
    }
    int m = 1;
    for(int i=0; i<n; i++){
      int x0, y0, x1, y1;
      x0 = a[i].first;
      y0 = a[i].second;
      for(int j=i+1; j<n; j++){
        int c = 2;
        x1 = a[j].first;
        y1 = a[j].second;
        int x = x1 - x0,
            y = y1 - y0;
        for(int k=j+1; k<n; k++){
          x1 = a[k].first;
          y1 = a[k].second;
          if(!(x * (y1 - y0) - (x1 - x0) * y))
            c++;
        }
        if(c > m)
          m = c;
      }
    }
    printf("%d\n", m);
  }
  return 0;
}
