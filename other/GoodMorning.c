#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int GetRow(int x){
  if (x > 0)
    return (x - 1) / 3;
  else
    return 3;
}
int GetCol(int x){
  if (x > 0)
    return (x - 1) % 3;
  else
    return 1;
}
bool LessEq(int x, int y){
  return GetRow(x) <= GetRow(y) && GetCol(x) <= GetCol(y);
}
bool IsOk(int sec){
  assert(0 < sec && sec <= 200);
  if (sec < 10)
    return true;
  else
    return LessEq((sec / 10) % 10, sec % 10);
}
int main(){
  int Z;
  scanf("%d", &Z);
  while (Z--) {
    int sec;
    scanf("%d", &sec);
    int delta = 0;
    while (true){
      if (IsOk(sec + delta)){
        printf("%d\n", sec + delta);
        break;
      }
      if (IsOk(sec - delta)) {
        printf("%d\n", sec - delta);
        break;
      }
      ++delta;
    }
  }
  return 0;
}
