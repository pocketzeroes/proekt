#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#ifdef _WIN32
  #define inline static
#endif

typedef struct pair{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpP(pair a, pair b){
  if(a.first == b.first)return (a.second < b.second)?-1:1;
  return (a.first < b.first)?-1:1;
}




inline int parent(int i) { return (i-1)/2; }
inline int left  (int i) { return (2*i + 1); }
inline int right (int i) { return (2*i + 2); }

////////////////////
void amin(int*x, int y){
  if(y < *x)
    *x =  y;
}
void amax(int*x, int y){
  if(*x < y)
     *x = y;
}

const int  dy [] = { 0, 1, 0, -1 };
const int  dx [] = { 1, 0, -1, 0 };
const char dir[] = "RDLU";
enum{ INF = 1 << 29};
int R, C;
int N;
char F[511][511];
char S[1000111];
int nxt[1000111][4];
pair dp[511][511];
int Sx, Sy, Tx, Ty;
enum{ BASE = 511};
char G[BASE * 2][BASE * 2];
int GR, GD, GL, GU;
int Ey, Ex;




int get_dir (char c){
  if (c == 'R') return 0;
  if (c == 'D') return 1;
  if (c == 'L') return 2;
  if (c == 'U') return 3;
  return -1;
}
bool in(int y, int x){
  return 0 <= y && y < R && 0 <= x && x < C;
}
void build_snake(){
  int y = 0, x = 0;
  G[BASE][BASE] = 1;
  for(int i = 0, i_len = (N); i < i_len; ++i){
    int d = get_dir(S[i]);
    y += dy[d];
    x += dx[d];
    amax(&GR, x);
    amax(&GD, y);
    amin(&GL, x);
    amin(&GU, y);
    if (BASE <= x || BASE <= y || x <= -BASE || y <= -BASE)
      break;
    G[y + BASE][x + BASE] = 1;
  }
  Ey = y;
  Ex = x;
}
typedef struct State_s{
  int y, x;
  int len, pos;
}State;

State newState (int a, int b, int c, int d){
  State rez;
  rez.y   = a;
  rez.x   = b;
  rez.len = c;
  rez.pos = d;
  return rez;
} 

int cmpS(State this, State other){
  return (this.len != other.len ? this.len > other.len : this.pos > other.pos)?-1:1;
}
void swap(State *x, State *y){
    State temp = *x;
    *x = *y;
    *y = temp;
}
#define INIT_CAP 100
typedef struct{
    State *harr;
    int capacity;
    int heasize;
}Heap;
void MinHeapify(Heap*h, int i);
Heap newHeap(){
    int cap = INIT_CAP;
    Heap rez;
    rez.heasize = 0;
    rez.capacity  = cap;
    rez.harr      =(State*) calloc(cap,sizeof(State));
    return rez;
}
State top(Heap*h) {
    return h->harr[0];
}
size_t size(Heap*h){
    return h->heasize;
}
bool empty(Heap*h){
    return (h->heasize==0);
}
void push(Heap*h, State k){
    if (h->heasize == h->capacity)
    {
        int newcap = 2*h->capacity;
        h->harr = realloc(h->harr, newcap*sizeof(State));
        h->capacity = newcap;
    }
    h->heasize++;
    int i = h->heasize - 1;
    h->harr[i] = k;
    while (i != 0 && cmpS(h->harr[parent(i)] , h->harr[i])<0 )//h->harr[parent(i)] < h->harr[i])
    {
       swap(&h->harr[i], &h->harr[parent(i)]);
       i = parent(i);
    }
}
void pop(Heap*h){
    if (h->heasize <= 0) assert( !"cannot pop INT_MAX");
    if (h->heasize == 1)
    {
        h->heasize--;
        return;// h->harr[0];
    }
    State root = h->harr[0];
    h->harr[0] = h->harr[h->heasize-1];
    h->heasize--;
    MinHeapify(h, 0);
}
void MinHeapify(Heap*h, int i){
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < h->heasize && cmpS(h->harr[l] , h->harr[i])>0) //h->harr[l] > h->harr[i])
        smallest = l;
    if (r < h->heasize && cmpS(h->harr[r] , h->harr[smallest])>0)//h->harr[r] > h->harr[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(&h->harr[i], &h->harr[smallest]);
        MinHeapify(h, smallest);
    }
}




/////////////////
int main (){
  scanf ("%d %d %d", &R, &C, &N);
  for (int i = 0, i_len = (R); i < i_len; ++i)
    scanf ("%s", F[i]);
  scanf ("%s", S);
  for (int t = 0, t_len = (4); t < t_len; ++t)
    nxt[N][t] = N;
  for (int i = N; i--;){
    for (int t = 0, t_len = (4); t < t_len; ++t)
      nxt[i][t] = nxt[i + 1][t];
    nxt[i][get_dir (S[i])] = i;
  } 
  for (int i = 0, i_len = (R); i < i_len; ++i){
    for (int j = 0, j_len = (C); j < j_len; ++j){
      if (F[i][j] == 'S'){
        Sy = i;
        Sx = j;
      }
      if (F[i][j] == 'T'){
        Ty = i;
        Tx = j;
      }
      dp[i][j] = newPair(INF, INF);
    }
  }
  build_snake();
  dp[Sy][Sx] = newPair(0, N);
  Heap Q = newHeap();
  push(&Q, newState(Sy, Sx, 0, N));
  while (!empty(&Q)){
    State s = top(&Q);
    pop(&Q);
    if(cmpP(dp[s.y][s.x], newPair(s.len, s.pos))<0)
      continue;
    if(s.y == Ty && s.x == Tx)
      break;
    for (int d = 0, d_len = (4); d < d_len; ++d){
      int yy = s.y + dy[d];
      int xx = s.x + dx[d];
      if (in (yy, xx) && F[yy][xx] != '#'){
        int k = nxt[s.pos][d];
        if (k < N){
          pair val = newPair(s.len, k + 1);
          if(cmpP(dp[yy][xx], val)>0){
            dp[yy][xx] = val;
            push(&Q, newState(yy, xx, s.len, k + 1));
          }
        }
      }
    }
    for (int d = 0, d_len = (4); d < d_len; ++d){
      int yy = s.y + dy[d];
      int xx = s.x + dx[d];
      if (in (yy, xx) && F[yy][xx] != '#'){
        int k = nxt[0][d];
        if (k < N){
          pair val = newPair(s.len + 1, k + 1);
          if(cmpP(dp[yy][xx], val)>0){
            dp[yy][xx] = val;
            push(&Q, newState(yy, xx, s.len + 1, k + 1));
          }
        }
      }
    }
    if (s.y + GD < R && s.y + GU >= 0 && s.x + GR < C && s.x + GL >= 0){
      bool ok = true;
      for (int i = GU; i <= GD && ok; i++)
        for (int j = GL; j <= GR && ok; j++){
          if (G[i + BASE][j + BASE] && F[s.y + i][s.x + j] == '#')
            ok = false;
        }
      if (ok){
        pair val = newPair(s.len, N);
        if(cmpP(dp[s.y + Ey][s.x + Ex], val)>0){
          dp[s.y + Ey][s.x + Ex] = val;
          push(&Q, newState(s.y + Ey, s.x + Ex, s.len, N));
        }
      }
    }
  }
  if (dp[Ty][Tx].first == INF)
    puts ("-1");
  else
    printf ("%d\n", dp[Ty][Tx].first);
}


































