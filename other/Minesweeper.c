#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

char buff[100000];
int main(){
  int count, x,y,xc,yc;
  int xSize, ySize;
  scanf("%d %d", &xSize, &ySize);
  for(count = 1; xSize != 0 && ySize != 0; ++count){
    if (count != 1)
      puts("");
    int mineCount[xSize+2][ySize+2];
    memset(mineCount, 0, sizeof(mineCount));
    for(x = 1; x <= xSize; ++x){
      scanf("%s", &buff);
      for(y = 1; y <= ySize; ++y){
        if (buff[y - 1] == '*'){
          mineCount[x][y] = 10;
          for(xc = -1; xc < 2; ++xc){
            for(yc = -1; yc < 2; ++yc){
              ++mineCount[x + xc][y + yc];
            }
          }
        }
      }
    }
    printf("Field #%d:\n", count);
    for(x = 1; x <= xSize; ++x){
      for(y = 1; y <= ySize; ++y){
        if (mineCount[x][y] > 10)
          putchar('*');
        else
          printf("%d", mineCount[x][y]);
      }
      puts("");
    }
    scanf("%d %d", &xSize, &ySize);
  }
}
