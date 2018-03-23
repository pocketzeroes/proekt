#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE (1 << 6)
#define SQUARED_SIZE (SIZE * SIZE)

struct pipe{
  int node;
  int flow;
  int capacity;
};
static char grid        [SIZE ][ SIZE];
static int parent       [SQUARED_SIZE];
static int capacity     [SQUARED_SIZE];
static int queue        [SQUARED_SIZE];
static int visited      [SQUARED_SIZE];
static int queue_head, queue_tail;
static struct pipe *pipe[SQUARED_SIZE];
static int pipe_size    [SQUARED_SIZE];
static struct pipe T    [SQUARED_SIZE];
static int cost_change, cost_move;
static int width, height;
static int T_size;

#define NODE(n, m) (((n) * (width)) + (m))
#define SRC ((width) * (height))
#define DST ((width) * (height) + 1)

static void initialize(void){
  int n;
  for (n = 0; n < SQUARED_SIZE; n++) {
    pipe[n] = NULL;
    pipe_size[n] = 0;
    visited[n] = 0;
  }
}
static void push(int node, int capacity){
  T[T_size].node = node;
  T[T_size].flow = 0;
  T[T_size].capacity = capacity;
  T_size++;
}
static void set(int node){
  pipe[node] = (struct pipe *) malloc(sizeof(struct pipe) * T_size);
  memcpy(pipe[node], T, sizeof(struct pipe) * T_size);
  pipe_size[node] = T_size;
}
static void create_graph(void){
  int n, m;
  for (n = 0; n < height; n++){
    for (m = 0; m < width; m++){
      T_size = 0;
      if (n > 0)
        push(NODE(n - 1, m), cost_change);
      if (m > 0)
        push(NODE(n, m - 1), cost_change);
      if (m < width - 1)
        push(NODE(n, m + 1), cost_change);
      if (n < height - 1)
        push(NODE(n + 1, m), cost_change);
      push(SRC, (grid[n][m] == '#') ? cost_move : 0);
      push(DST, (grid[n][m] == '.') ? cost_move : 0);
      set(NODE(n, m));
    }
  }
  T_size = 0;
  for (n = 0; n < height; n++)
    for (m = 0; m < width; m++)
      push(NODE(n, m), (grid[n][m] == '#') ? cost_move : 0);
  set(SRC);
  T_size = 0;
  for (n = 0; n < height; n++)
    for (m = 0; m < width; m++)
      push(NODE(n, m), (grid[n][m] == '.') ? cost_move : 0);
  set(DST);
}
static void enqueue(int _parent, int node, int _capacity){
  if (_capacity <= 0)
    return;
  if (visited[node] != 0)
    return;
  visited[node] = 1;
  queue[queue_head] = node;
  parent[node] = _parent;
  capacity[node] = _capacity;
  queue_head++;
}
static int min(int x, int y){
  if (x < y)
    return x;
  return y;
}
static int augment(void){
  int n;
  int node, bound;
  queue_head = 0;
  queue_tail = 0;
  memset(visited, 0, sizeof(visited));
  enqueue(SRC, SRC, 1000000000);
  while ((queue_tail < queue_head) && (visited[DST] == 0)) {
    node = queue[queue_tail];
    bound = capacity[node];
    queue_tail++;
    for (n = 0; n < pipe_size[node]; n++)
      enqueue(node, pipe[node][n].node, min(bound, pipe[node][n].capacity - pipe[node][n].flow));
  }
  return visited[DST];
}
static struct pipe *search(int node, int search){
  int n;
  if ((node == SRC) || (node == DST))
    return &pipe[node][search];
  for (n = 0; n < pipe_size[node]; n++)
    if (pipe[node][n].node == search)
      return &pipe[node][n];
  abort();
}
static int update(void){
  int node;
  int bound;
  node = DST;
  bound = capacity[node];
  while (parent[node] != node) {
    search(parent[node], node)->flow += bound;
    search(node, parent[node])->flow -= bound;
    node = parent[node];
  }
  return bound;
}
int main(void){
  int n, sum;
  sum = 0;
  scanf("%d %d %d %d", &height, &width, &cost_change, &cost_move);
  for (n = 0; n < height; n++)
    scanf("%s", grid[n]);
  initialize();
  create_graph();
  while (augment() != 0)
    sum += update();
  printf("%d\n", sum);
  return 0;
}







