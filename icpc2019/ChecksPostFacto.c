#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#include<ctype.h>

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
typedef struct{
  char a[8][8];
  bool isEmpty;
}mat;
typedef struct{
  mat first;
  mat second;
  bool isEmpty;
}pair;

pair empty;
char startPlayer;
char*moveType;
vec*moves;
int N;

inline char opp(char player){
  return player == 'W' ? 'B' : 'W';
}
inline int sqX(int sq){
  return (sq-1)%4*2 + 1-((sq-1)/4)%2;
}
inline int sqY(int sq){
  return (sq-1)/4;
}
pair doit(mat start){
  mat board = start;
  char player = startPlayer;
  for(int i = 0; i < N; i++, player = opp(player))
  for(int j = 0; j+1 < moves[i].sz; j++) {
    int sx = sqX(moves[i].ptr[j  ]), sy = sqY(moves[i].ptr[j  ]);
    int ex = sqX(moves[i].ptr[j+1]), ey = sqY(moves[i].ptr[j+1]);
    bool promoted = ((player == 'W' && ey == 0) || (player == 'B' && ey == 7)) && islower(board.a[sy][sx]);
    if (moveType[i] == '-'){
      for (int y = 0; y < 8; y++)
      for (int x = 0; x < 8; x++)
        if (toupper(board.a[y][x]) == player)
      for (int dx = -1; dx <= 1; dx += 2)
      for (int dy = -1; dy <= 1; dy += 2) {
        if (board.a[y][x] == 'w' && dy == 1)
          continue;
        if (board.a[y][x] == 'b' && dy == -1)
          continue;
        int x2 = x+dx+dx, y2 = y+dy+dy;
        if (x2 < 0 || x2 >= 8 || y2 < 0 || y2 >= 8)
          continue;
        if (toupper(board.a[y+dy][x+dx]) != opp(player))
          continue;
        if (board.a[y2][x2] == '.')
          return empty;
        if (board.a[y2][x2] == '?') {
          start.a[y2][x2] = (y2 == 0) ? 'W' : 'w';
          pair ret = doit(start);
          if(!ret.isEmpty)
            return ret;
          start.a[y2][x2] = (y2 == 7) ? 'B' : 'b';
          return doit(start);
        }
      }
    }
    board.a[ey][ex] = board.a[sy][sx];
    if (promoted) board.a[ey][ex] = toupper(board.a[ey][ex]);
    board.a[sy][sx] = '.';
    if (moveType[i] == 'x') {
      int mx = (sx+ex)/2, my = (sy+ey)/2;
      board.a[my][mx] = '.';
      if (j+2 == moves[i].sz && !promoted) {
        int x = ex, y = ey;
        for (int dx = -1; dx <= 1; dx += 2)
        for (int dy = -1; dy <= 1; dy += 2) {
          if (board.a[y][x] == 'w' && dy == 1)
            continue;
          if (board.a[y][x] == 'b' && dy == -1)
            continue;
          int x2 = x+dx+dx, y2 = y+dy+dy;
          if (x2 < 0 || x2 >= 8 || y2 < 0 || y2 >= 8)
            continue;
          if (toupper(board.a[y+dy][x+dx]) != opp(player))
            continue;
          if (board.a[y2][x2] == '.')
            return empty;
          if (board.a[y2][x2] == '?') {
            start.a[y2][x2] = (y2 == 0) ? 'W' : 'w';
            pair ret = doit(start);
            if(!ret.isEmpty)
              return ret;
            start.a[y2][x2] = (y2 == 7) ? 'B' : 'b';
            return doit(start);
          }
        }
      }
    }
  }
  return(pair){start, board};
}
int main(){
  empty.isEmpty=true;
  bool first = true;
  while(scanf("%c %d", &startPlayer, &N)==2){
    moveType = calloc(N, sizeof(char));
    moves    = calloc(N, sizeof(vec) );
    for (int i = 0; i < N; i++){
      char*s = getstr();
      int j = 0;
      int ssize=strlen(s);
      for(;;){
        int sq = s[j]-'0';
        if (j+1 < ssize && isdigit(s[j+1]))
          sq = 10*sq + s[++j]-'0';
        moves[i].ptr = pushback(moves[i].ptr, &moves[i].sz, sq);
        if (++j == ssize)
          break;
        moveType[i] = s[j++];
      }
    }
    mat start,board;
    for(int i=0;i<8;i++)
      for(int j=0;j<8;j++)
        board.a[i][j] = start.a[i][j]='?';
    char player = startPlayer;
    vec startX[8]={0};
    vec startY[8]={0};
    for(int y = 0; y < 8; y++)
    for(int x = 0; x < 8; x++) {
      startX[y].ptr = pushback(startX[y].ptr, &startX[y].sz, x);
      startY[y].ptr = pushback(startY[y].ptr, &startY[y].sz, y);
    }
    for (int i = 0; i < N; i++, player = opp(player))
    for (int j = 0; j+1 < moves[i].sz; j++) {
      int sx = sqX(moves[i].ptr[j  ]), sy = sqY(moves[i].ptr[j  ]);
      int ex = sqX(moves[i].ptr[j+1]), ey = sqY(moves[i].ptr[j+1]);
      bool promoted = ((player == 'W' && ey == 0) || (player == 'B' && ey == 7));
      if (board.a[sy][sx] == '?') {
        board.a[sy][sx] = start.a[sy][sx] = tolower(player);
      }
      if (board.a[ey][ex] == '?') {
        board.a[ey][ex] = start.a[ey][ex] = '.';
      }
      if (((player == 'W') ^ (ey < sy)) && islower(board.a[sy][sx])) {
        board.a[sy][sx] = start.a[startY[sy].ptr[sx]][startX[sy].ptr[sx]] = toupper(board.a[sy][sx]);
      }
      board.a[ey][ex] = board.a[sy][sx];
      if (promoted && j+2 == moves[i].sz) board.a[ey][ex] = toupper(board.a[ey][ex]);
      board.a[sy][sx] = '.';
      startX[ey].ptr[ex] = startX[sy].ptr[sx];
      startY[ey].ptr[ex] = startY[sy].ptr[sx];
      if (moveType[i] == 'x') {
        int mx = (sx+ex)/2, my = (sy+ey)/2;
        if (board.a[my][mx] == '?') {
          board.a[my][mx] = start.a[my][mx] = tolower(opp(player));
        }
        board.a[my][mx] = '.';
      }
    }
    pair ret = doit(start);
    if (!first)
      puts("");
    first = false;
    for (int y = 0; y < 8; y++)
    for (int x = y%2; x < 8; x += 2) {
      ret.first.a[y][x] = ret.second.a[y][x] = '-';
    }
    for (int y = 0; y < 8; y++)
    for (int x = 1-y%2; x < 8; x += 2) {
      if (ret.first .a[y][x] == '?') ret.first .a[y][x] = '.';
      if (ret.second.a[y][x] == '?') ret.second.a[y][x] = '.';
    }
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        printf("%c", ret.first.a[i][j]);
      }
      printf(" ");
      for(int j=0; j<8; j++){
        printf("%c", ret.second.a[i][j]);
      }
      puts("");
    }
  }
  return 0;
}
