const int INF = 1e9 + 5;
const int DIRS = 4;
const int DR[] = {-1,  0, +1,  0};
const int DC[] = { 0, +1,  0, -1};
enum{ RC_MAX = 24};
const char PLAYER = 'S', BOX = 'B', TARGET = 'T';
const char EMPTY = '.', WALL = '#';

typedef struct state {
    int player_r, player_c, box_r, box_c, dist;
}state;

state newState(int i1,int i2,int i3,int i4,int i5){
    return(state){i1,i2,i3,i4,i5};
}

#if 1 //queueue
typedef state QueueElementType;
typedef struct Queue
{
  QueueElementType  *Elements;
  int  Front;
  int  Back;
  int  NumElements;
  int  Capacity;
} Queue;
Queue *newQueue();
void   DeleteQueue(Queue *Q);
int    empty(Queue *Q);
int    push(Queue *Q, QueueElementType e);
QueueElementType pop(Queue *Q);
int    isElementInQueue(Queue *Q, QueueElementType e);

Queue *newQueue()
{
  int N=1024;
  Queue *Q;
  if (N < 1)
  {
    printf("\n**Error in newQueue invalid parameter N (%d)\n\n", N);
    return NULL;
  }
  Q = (Queue *)malloc(sizeof(Queue));
  if (Q == NULL)
  {
    printf("\n**Error in newQueue: malloc failed _to allocate\n\n");
    exit(-1);
  }
  Q->Elements = (QueueElementType *)malloc(N * sizeof(QueueElementType));
  if (Q->Elements == NULL)
  {
    printf("\n**Error in newQueue: malloc failed _to allocate\n\n");
    exit(-1);
  }
  Q->Front = 0;
  Q->Back = -1;
  Q->NumElements = 0;
  Q->Capacity = N;
  return Q;
}
void DeleteQueue(Queue *Q)
{
  free(Q->Elements);
  free(Q);
}
int empty(Queue *Q)
{
  return Q->NumElements == 0;
}
int size(Queue *Q)
{
  return Q->NumElements;
}
int push(Queue *Q, QueueElementType e)
{
  if (Q->NumElements == Q->Capacity)
  {
    int N = 2 * Q->Capacity;
    QueueElementType *newE = (QueueElementType *)malloc(N * sizeof(QueueElementType));
    if (newE == NULL)
    {
      printf("\n**Error in push: malloc failed _to allocate\n\n");
      exit(-1);
    }
    int  i = Q->Front;
    int  j = 0;
    int  n;
    for (n = 0; n < Q->NumElements; ++n)
    {
      newE[j] = Q->Elements[i];
      ++j;
      ++i;
      if (i >= Q->Capacity)
        i = 0;
    }
    free(Q->Elements);
    Q->Front = 0;
    Q->Back = j - 1;
    Q->Elements = newE;
    Q->Capacity = N;
  }
  Q->Back++;
  if (Q->Back >= Q->Capacity)
    Q->Back = 0;
  Q->Elements[Q->Back] = e;
  Q->NumElements++;
  return 1;
}
QueueElementType pop(Queue *Q)
{
  if (empty(Q))
  {
    printf("\n**Error in pop: Q is empty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  Q->Front++;
  if (Q->Front >= Q->Capacity)
    Q->Front = 0;
  Q->NumElements--;
  return e;
}
QueueElementType front(Queue *Q)
{
  if (empty(Q))
  {
    printf("\n**Error in pop: Q is empty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  return e;
}
#endif


int R, C;
int PR, PC, BR, BC, TR, TC;
char**grid;
int _dist[RC_MAX][RC_MAX][RC_MAX][RC_MAX];
Queue*q;

bool valid(int r, int c){
    return 0 <= r && r < R && 0 <= c && c < C;
}

#define dist(s) _dist[s.player_r][s.player_c][s.box_r][s.box_c]

void bfs_check(state s, int add){
    s.dist += add;
    if(s.dist < dist(s)){
        dist(s) = s.dist;
        push(q, s);
    }
}
int bfs() {
    memset(_dist, 63, sizeof(_dist));
    q = newQueue();//of state
    bfs_check(newState(PR, PC, BR, BC, 0), 0);
    int best = INF;
    while(!empty(q)) {
        state top = front(q); pop(q);
        if(top.dist > dist(top))
            continue;
        if(top.box_r == TR && top.box_c == TC)
            best = fmin(best, top.dist);
        for(int dir = 0; dir < DIRS; dir++){
            int nr = top.player_r + DR[dir];
            int nc = top.player_c + DC[dir];
            if(!valid(nr, nc) || grid[nr][nc] == WALL)
                continue;
            if(nr == top.box_r && nc == top.box_c){
                int nbr = nr + DR[dir];
                int nbc = nc + DC[dir];
                if(valid(nbr, nbc) && grid[nbr][nbc] != WALL)
                    bfs_check(newState(nr, nc, nbr, nbc, top.dist), 1);
            }
            else
                bfs_check(newState(nr, nc, top.box_r, top.box_c, top.dist), 0);
        }
    }
    return best < INF ? best : -1;
}
int minPushBox(char**g, int gSz, int*g0sz){
    grid = g;
    R = gSz;
    C = gSz==0 ? 0 : g0sz[0];
    for (int r = 0; r < R; r++){
        for (int c = 0; c < C; c++){
            if (grid[r][c] == PLAYER) {
                PR = r;
                PC = c;
                grid[r][c] = EMPTY;
            }
            else if (grid[r][c] == BOX) {
                BR = r;
                BC = c;
                grid[r][c] = EMPTY;
            }
            else if (grid[r][c] == TARGET) {
                TR = r;
                TC = c;
                grid[r][c] = EMPTY;
            }
        }
    }
    return bfs();
}
