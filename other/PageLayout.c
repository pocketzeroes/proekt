#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int max(int a,int b){return a>b?a:b;}
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
bool**newmat(int x, int y){
  bool**rv = calloc(x, sizeof(bool*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(bool));
  return rv;
}

int n;
bool**overlap;
int*areas;

int maximizeArea(int index, bool*chosen){
  if(index == n)
    return 0;
  int mx = 0;
  chosen[index] = true;
  bool valid = true;
  for(int i = 0; i < index; i++){
    if(chosen[i] && overlap[index][i]){
      valid = false;
      break;
    }
  }
  if(valid)
    mx = areas[index] + maximizeArea(index + 1, chosen);
  chosen[index] = false;
  return max(mx, maximizeArea(index + 1, chosen));
}
int main(){
  while(1){
    n = in_nextInt();
    if(n == 0)
      break;
    int w[n];
    int h[n];
    int x[n];
    int y[n];
    areas   = calloc(n, sizeof(int));
    for(int i=0; i<n; i++){
      w[i] = in_nextInt();
      h[i] = in_nextInt();
      x[i] = in_nextInt();
      y[i] = in_nextInt();
      areas[i] = w[i] * h[i];
    }
    overlap = newmat(n, n);
    for(int i=0; i<n; i++){
      for(int j=i+1; j<n; j++){
        bool toLeft  = x[i] + w[i] <= x[j];
        bool toRight = x[j] + w[j] <= x[i];
        bool above   = y[i] + h[i] <= y[j];
        bool below   = y[j] + h[j] <= y[i];
        if (!toLeft && !toRight && !above && !below)
          overlap[i][j] = overlap[j][i] = true;
      }
    }
    bool ch[n]; memset(ch, 0, sizeof(ch));
    printf("%d\n", maximizeArea(0, ch));
  }
  return 0;
}
