#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int W, L;
char room[21][21];

int findEntrance(int*inX, int*inY){
  int i, direction;
  bool found = false;
  for (i=0; i<W && !found; i++) {
    if (room[0][i] == '*') {
      found     = true;
     *inX       = i;
     *inY       = 0;
      direction = 3;
    }
    if (room[W-1][i] == '*') {
      found     = true;
     *inX       = i;
     *inY       = W-1;
      direction = 2;
    }
  }
  for (i=0; i<L && !found; i++) {
    if (room[i][0] == '*') {
      found     = true;
     *inX       = 0;
     *inY       = i;
      direction = 0;
    }
    if (room[i][L-1] == '*') {
      found     = true;
     *inX       = L-1;
     *inY       = i;
      direction = 1;
    }
  }
  return direction;
}
bool getNextPoint(int direction, int*X, int*Y){
  bool done = false;
  if      (direction == 0) (*X)++;
  else if (direction == 1) (*X)--;
  else if (direction == 2) (*Y)--;
  else if (direction == 3) (*Y)++;
  else
    puts("ERROR: direction never less than 0 greater than 3.");
  if (room[*Y][*X] == 'x')
    done = true;
  return done;
}
int main(){
  int i, j, X, Y, inX, inY, direction, houseNum = 1;
  bool done;
  scanf("%d", &W);
  while(W > 0){
    scanf("%d", &L);
    for(i=0; i<L; i++)
      strcpy(room[i], getstr());
    direction = findEntrance(&inX, &inY);
    X = inX;
    Y = inY;
    done = false;
    int count = 0, maxCount = 2*W*L;
    while (!done && count < maxCount){
      count++;
      done = getNextPoint(direction, &X, &Y);
      if (!done){
        if (room[Y][X] == '/')
          direction = (direction + 2) % 4;
        if(room[Y][X] == '\\') {
          if(direction == 0)
            direction = 3;
          else if(direction == 3)
            direction = 0;
          else if(direction == 1)
            direction = 2;
          else if(direction == 2)
            direction = 1;
        }
      }
    }
    room[Y][X] = '&';
    printf("HOUSE %d\n", houseNum);
    for(i=0; i<L; i++)
      puts(room[i]);
    scanf("%d", &W);
    houseNum++;
  }
  return 0;
}

