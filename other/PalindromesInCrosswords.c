#pragma GCC optimize "-O3"
#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  free(a);
  return ptr;
}
int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
char**newmat(int x, int y){
  char**rv = calloc(x, sizeof(char*));
  for(int i=0; i<x; i++)
    rv[i] = calloc(y, sizeof(char));
  return rv;
}
/////////////////////////////

enum{ MAX           = 100};
enum{ MAX_SQUARED   = MAX * MAX};
enum{ MAX_CUBED     = MAX * MAX * MAX};
enum{ UNSOLVED      = -1000};
enum{ UNINITIALIZED = -5000};
char**grid;
int n;
int memoLongest[MAX][MAX][MAX][MAX];
int memoPath   [MAX][MAX][MAX][MAX];





int encodePairOfLocations(int x1, int y1, int x2, int y2){
  return ((x1 * MAX + y1) * MAX + x2) * MAX + y2;
}
int dist(int x1, int y1, int x2, int y2){
  return x2 - x1 + y2 - y1;
}
int find(int x1, int y1, int x2, int y2){
  if(x1 > x2 || y1 > y2 || x1 >= n || y1 >= n || x2 < 0 || y2 < 0)
    return INT_MIN;
  if(x1 == x2 && y1 == y2)
    return memoLongest[x1][y1][x2][y2] = 1;
  bool lettersMatch = grid[y1][x1] == grid[y2][x2];
  if(dist(x1, y1, x2, y2) == 1 && lettersMatch)
    return memoLongest[x1][y1][x2][y2] = 2;
  if(memoLongest[x1][y1][x2][y2] != UNSOLVED)
    return memoLongest[x1][y1][x2][y2];
  int longest = UNINITIALIZED;
  int path = UNINITIALIZED;
  int result;
  if(lettersMatch){
    result = find(x1 + 1, y1, x2 - 1, y2) + 2;
    if(result > longest){
      longest = result;
      path = encodePairOfLocations(x1 + 1, y1, x2 - 1, y2);
    }
    result = find(x1 + 1, y1, x2, y2 - 1) + 2;
    if(result > longest){
      longest = result;
      path = encodePairOfLocations(x1 + 1, y1, x2, y2 - 1);
    }
    result = find(x1, y1 + 1, x2 - 1, y2) + 2;
    if(result > longest){
      longest = result;
      path = encodePairOfLocations(x1, y1 + 1, x2 - 1, y2);
    }
    result = find(x1, y1 + 1, x2, y2 - 1) + 2;
    if(result > longest){
      longest = result;
      path = encodePairOfLocations(x1, y1 + 1, x2, y2 - 1);
    }
  }
  memoPath[x1][y1][x2][y2] = path;
  memoLongest[x1][y1][x2][y2] = longest;
  result = find(x1 + 1, y1, x2, y2);
  result = find(x1, y1 + 1, x2, y2);
  result = find(x1, y1, x2 - 1, y2);
  result = find(x1, y1, x2, y2 - 1);
  return lettersMatch ? longest : INT_MIN;
}
int decodeX1(int encoded){
  return encoded / MAX_CUBED;
}
int decodeY1(int encoded){
  return (encoded / MAX_SQUARED) % MAX;
}
int decodeX2(int encoded){
  return (encoded / MAX) % MAX;
}
int decodeY2(int encoded){
  return encoded % MAX;
}
int main(){
  int t = in_nextInt();
  while (t-- > 0){
    n = in_nextInt();
    grid = newmat(n, n);// of char
    getchar();
    for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
        grid[i][j] = getchar();
      }
      getchar();
    }
    for(int a=0; a<n; a++){
      for(int b=0; b<n; b++){
        for(int c=0; c<n; c++){
          fill(memoLongest[a][b][c], MAX, UNSOLVED);
          fill(memoPath   [a][b][c], MAX, UNSOLVED);
        }
      }
    }
    find(0, 0, n - 1, n - 1);
    int longest = 0, curX1 = 0, curY1 = 0, curX2 = 0, curY2 = 0;
    for(int x1 = 0; x1 < n; x1++){
      for(int y1 = 0; y1 < n; y1++){
        for(int x2 = 0; x2 < n; x2++){
          for(int y2 = 0; y2 < n; y2++){
            if(memoLongest[x1][y1][x2][y2] > longest){
              longest = memoLongest[x1][y1][x2][y2];
              curX1 = x1;
              curY1 = y1;
              curX2 = x2;
              curY2 = y2;
            }
          }
        }
      }
    }
    int startingRow = curY1 + 1;
    int startingCol = curX1 + 1;
    int path[longest]; clr(path);
    int start = 0;
    int end = longest - 1;
    while (start <= end) {
      if (start == end) {
        path[start++] = encodePairOfLocations(curX1, curY1, 0, 0);
      }
      else {
        path[start++] = encodePairOfLocations(curX1, curY1, 0, 0);
        path[end--] = encodePairOfLocations(curX2, curY2, 0, 0);
      }
      int nextPairOfLocations = memoPath[curX1][curY1][curX2][curY2];
      curX1 = decodeX1(nextPairOfLocations);
      curY1 = decodeY1(nextPairOfLocations);
      curX2 = decodeX2(nextPairOfLocations);
      curY2 = decodeY2(nextPairOfLocations);
    }
    char*palindromeBuilder = strdup("");
    char*pathBuilder       = strdup("");
    int prevX = -1;
    for(int i = 0; i < longest; i++){
      int x = decodeX1(path[i]);
      int y = decodeY1(path[i]);
      if(i > 0){
        if(x > prevX) pathBuilder = concatc(pathBuilder, 'R');
        else          pathBuilder = concatc(pathBuilder, 'D');
      }
      palindromeBuilder = concatc(palindromeBuilder, grid[y][x]);
      prevX = x;
    }
    printf("%s %d %d %sS\n", palindromeBuilder, startingRow, startingCol, pathBuilder);
  }
  return 0;
}
