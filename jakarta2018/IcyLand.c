#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char*GetString(void){
  char x[1000005];
  scanf("%s", x);
  return strdup(x);
}

enum{ MAXR = 505};
int r,c;
char*data[MAXR];

int main(){
  scanf("%d %d", &r, &c);
  for(int i=0; i<r; ++i)
    data[i] = GetString();
  int risan = 0;
  if (r == 1 || c == 1){
    if (r == 1){
      for(int j=1; j<c-1; ++j)
        if(data[0][j] == '.')
          ++risan;
    }
    else{
      for(int i=1; i<r-1; ++i)
        if(data[i][0] == '.')
          ++risan;
    }
  }
  else if (r == 2 && c == 2){
    risan = 0;
  }
  else if (r == 2){
    for (int j=1; j<c-1; ++j)
      if(data[0][j] == '.' && data[1][j] == '.')
        ++risan;
  }
  else if (c == 2){
    for (int i=1; i<r-1; ++i)
      if(data[i][0] == '.' && data[i][1] == '.')
        ++risan;
  }
  else{
    for (int i=1; i<r-1; ++i)
      for(int j=1; j<c-1; ++j)
        if(data[i][j] == '.')
          ++risan;
    for(int i=0; i<r; ++i)
      for(int j=0; j<c; ++j){
        if((i == 0 || i == r - 1) && (j == 0 || j == c - 1))
          continue;
        if(i != 0 && i != r - 1 && j != 0 && j != c - 1)
          continue;
        if(data[i][j] == '#')
          goto ok;
      }
    ++risan;
 ok:;
  }
  printf("%d\n",risan);
}
