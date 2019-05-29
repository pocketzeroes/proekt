#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned int state_t;

struct queue{
  state_t state;
  int depth;
  struct queue *next;
};

static int target;
static int source[4];
static char data[16][16];
static int width, height;
static int maximum_depth;
static int source_size;

static const int dn[4] = { 0, -1, 0, 1 };
static const int dm[4] = { 1, 0, -1, 0 };

static struct queue *queue_burned[1 << 20];
static struct queue queue[1 << 24];
static int span[256][4];
static int queue_head;
static int queue_tail;

static int state_hash(state_t state){
  state += state >> 17;
  state ^= state << 7;
  state  += state << 23;
  state ^= state >> 5;
  return state & 0x000FFFFF;
}
static state_t get_state(void){
  int n, m;
  state_t state;
  for (n = 0; n < 4; n++)
    source[n] = -1;
  target = -1;
  for (n = 0; n < height; n++) {
    for (m = 0; m < width; m++) {
      if ((data[n][m] >= '1') && (data[n][m] <= '4')) {
        source[data[n][m] - '1'] = (n << 4) | m;
        data[n][m] = '.';
      }
      else if (data[n][m] == 'X') {
        target = (n << 4) | m;
        data[n][m] = '.';
      }
    }
  }
  state = 0;
  source_size = 0;
  for (n = 0; n < 4; n++) {
    if (source[n] < 0)
      continue;
    state |= source[n] << (source_size << 3);
    source_size++;
  }
  return state;
}
static state_t swap(state_t state, int u, int v){
  int x[4];
  int save;
  x[0] = state & 0xFF;
  x[1] = (state >> 8) & 0xFF;
  x[2] = (state >> 16) & 0xFF;
  x[3] = (state >> 24) & 0xFF;
  if (x[u] > x[v]) {
    save = x[u];
    x[u] = x[v];
    x[v] = save;
  }
  state = x[0] | (x[1] << 8) | (x[2] << 16) | (x[3] << 24);
  return state;
}
static void enqueue(state_t state, int depth){
  int hash;
  struct queue *search;
  if (source_size >= 4) {
    state = swap(state, 2, 3);
    state = swap(state, 1, 3);
  }
  if (source_size >= 3) {
    state = swap(state, 1, 2);
  }
  hash = state_hash(state);
  for (search = queue_burned[hash]; search != NULL; search = search->next)
    if (search->state == state)
      return;
  queue[queue_head].state = state;
  queue[queue_head].depth = depth;
  queue[queue_head].next = queue_burned[hash];
  queue_burned[hash] = &queue[queue_head];
  queue_head++;
}
static void dequeue(state_t *state, int *depth){
  *state = queue[queue_tail].state;
  *depth = queue[queue_tail].depth;
  queue_tail++;
}
static int used(int n, int m){
  if ((n < 0) || (n >= height))
    return 1;
  if ((m < 0) || (m >= width))
    return 1;
  return (data[n][m] != '.');
}
static void compute_span(void){
  int d;
  int p, m;
  int dy, dx;
  for (p = 0; p < 256; p++) {
    for (m = 0; m < 4; m++) {
      dy = p >> 4;
      dx = p & 15;
      for (d = 1; d < 16; d++) {
        if (used(dy + dn[m], dx + dm[m]) != 0)
          break;
        dy += dn[m];
        dx += dm[m];
      }
      span[p][m] = d - 1;
    }
  }
}
static int ricochet(int sx, int sy, int m, int dx, int dy, int d){
  int k;
  if (dm[m] == 0)
    if (sx != dx)
      return d;
  if (dn[m] == 0)
    if (sy != dy)
      return d;
  if (dm[m] != 0) {
    k = dx - sx;
    if (dm[m] < 0)
      k = -k;
    if ((k >= 0) && (k <= d))
      return k - 1;
    return d;
  }
  if (dn[m] != 0) {
    k = dy - sy;
    if (dn[m] < 0)
      k = -k;
    if ((k >= 0) && (k <= d))
      return k - 1;
    return d;
  }
  return d;
}
static int search(void){
  int d, p;
  int n, m;
  int depth;
  int dy, dx;
  state_t state;
  int minimum;
  int rxy;
  int r;
  state = get_state();
  compute_span();
  if (source[0] < 0)
    return -1;
  if (target < 0)
    return -1;
  queue_head = 0;
  queue_tail = 0;
  enqueue(state, 0);
  while (queue_head > queue_tail) {
    dequeue(&state, &depth);
    if (depth > maximum_depth)
      break;
    if ((state & 0xFF) == target)
      return depth;
    for (n = 0; n < source_size; n++) {
      p = (state >> (n << 3)) & 0xFF;
      for (m = 0; m < 4; m++) {
        minimum = span[p][m];
        for (r = 0; r < source_size; r++) {
          if (r == n)
            continue;
          rxy = (state >> (r << 3)) & 0xFF;
          d = ricochet(p & 15, p >> 4, m, rxy & 15, rxy >> 4, span[p][m]);
          if (d < minimum)
            minimum = d;
        }
        dy = (p >> 4) + minimum * dn[m];
        dx = (p & 15) + minimum * dm[m];
        enqueue((state & ~(255 << (n << 3))) | (((dy << 4) | dx) << (n << 3)), depth + 1);
      }
    }
  }
  return -1;
}
int main(void){
  int n, m;
  int moves;
  scanf("%*d %d %d %d", &width, &height, &maximum_depth);
  for (n = 0; n < height; n++)
    for (m = 0; m < width; m++)
      scanf(" %c", &data[n][m]);
  moves = search();
  if (moves <= 0)
    printf("NO SOLUTION\n");
  else
    printf("%d\n", moves);
  return 0;
}
