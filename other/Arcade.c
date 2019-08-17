#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

int DX[4]= {-1,-1,1,1};
int DY[4]= {-1, 0,0,1};
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
double in_nextDouble(){
  double x;
  scanf("%lf", &x);
  return x;
}

int main(){
  int n = in_nextInt();
  int pts[n][n]; clr(pts);
  for(int i=0; i<n; i++)
    for(int j=0; j<=i; j++)
      pts[i][j] = in_nextInt();
  double probs[n][n][5]; clr(probs);
  for (int i=0; i<n; i++)
    for (int j=0; j<=i; j++)
      for (int k=0; k<5; k++)
        probs[i][j][k] = in_nextDouble();
  double res = 0, probLeft = 1;
  double curState[n][n]; clr(curState);
  curState[0][0] = 1;
  bool inbounds(int x, int y){
    return x >= 0 && y >= 0 && x < n && y <= x;
  }
  while (probLeft > 1e-9){
    double newState[n][n]; clr(newState);
    for (int i=0; i<n; i++){
      for (int j=0; j<=i; j++){
        for (int k=0; k<4; k++){
          int nextX = i+DX[k];
          int nextY = j+DY[k];
          if (!inbounds(nextX, nextY))
            continue;
          newState[nextX][nextY] += curState[i][j]*probs[i][j][k];
        }
        res += (pts[i][j]*curState[i][j]*probs[i][j][4]);
        probLeft -= curState[i][j]*probs[i][j][4];
      }
    }
    memcpy(curState, newState, sizeof(curState));
  }
  printf("%.10f\n", res);
  return 0;
}
