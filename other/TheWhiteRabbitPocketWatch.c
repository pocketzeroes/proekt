#include<stdio.h>
#include<stdlib.h>

enum{ NODE_SIZE = 200};
enum{ TRIP_SIZE = 500};

struct node{
  int u, v;
};

static struct node node[NODE_SIZE];
static int N, A, R, T;
static int node_size;
static int matrix[TRIP_SIZE][NODE_SIZE];
static int b[TRIP_SIZE];
static int trip_size;
static int inverse[13];
static int weight[NODE_SIZE][NODE_SIZE];

static void swap(int *u, int *v){
  int save;
  save = *u;
  *u = *v;
  *v = save;
}
static int add_node(int u, int v){
  int n;
  if (u > v)
    swap(&u, &v);
  for (n = 0; n < node_size; n++)
    if ((node[n].u == u) && (node[n].v == v))
      return n;
  if ((u == v) || (node_size >= NODE_SIZE))
    abort();
  node[node_size].u = u;
  node[node_size].v = v;
  node_size++;
  return node_size - 1;
}
static void reduce(int n, int inverse){
  int m;
  for (m = 0; m < node_size; m++)
    matrix[n][m] = (matrix[n][m] * inverse) % 13;
  b[n] = (b[n] * inverse) % 13;
}
static void zero(int n, int pn, int pm){
  int m;
  reduce(n, inverse[matrix[n][pm]]);
  for (m = 0; m < node_size; m++)
    matrix[n][m] = (matrix[n][m] - matrix[pn][m] + 13) % 13;
  b[n] = (b[n] - b[pn] + 13) % 13;
}
static void matrix_solve(){
  int size;
  int n, m;
  int pn, pm;
  size = 0;
  for (pm = 0; pm < node_size; pm++) {
    for (pn = size; pn < trip_size; pn++) {
      if (matrix[pn][pm] != 0) {
        for (m = 0; m < node_size; m++)
          swap(&matrix[size][m], &matrix[pn][m]);
        swap(&b[size], &b[pn]);
        reduce(size, inverse[matrix[size][pm]]);
        for (n = size + 1; n < trip_size; n++)
          if (matrix[n][pm] != 0)
            zero(n, size, pm);
        size++;
        break;
      }
    }
  }
  for (pn = size - 1; pn >= 0; pn--) {
    reduce(pn, inverse[matrix[pn][pn]]);
    for (n = 0; n < pn; n++)
      if (matrix[n][pn] != 0)
        zero(n, pn, pn);
  }
}
int main(){
  int n, m;
  int d, p, u, v, w;
  for (n = 1; n < 13; n++)
    for (m = 1; m < 13; m++)
      if ((n * m) % 13 == 1)
        inverse[n] = m;
  scanf("%d %d %d %d", &N, &A, &R, &T);
  for (n = 0; n < T; n++) {
    u = 0;
    scanf("%d %d", &d, &p);
    b[trip_size] = d;
    for (m = 0; m < p; m++) {
      scanf("%d", &v);
      if (u > 0)
        matrix[trip_size][add_node(u, v)]++;
      u = v;
    }
    trip_size++;
  }
  for (n = 0; n < trip_size; n++)
    for (m = 0; m < node_size; m++)
      matrix[n][m] %= 13;
  matrix_solve();
  for (n = 0; n < N; n++)
    for (m = 0; m < N; m++)
      weight[n][m] = 1000000000;
  for (n = 0; n < N; n++)
    weight[n][n] = 0;
  for (n = 0; n < node_size; n++) {
    weight[node[n].u - 1][node[n].v - 1] = b[n];
    weight[node[n].v - 1][node[n].u - 1] = b[n];
  }
  for (w = 0; w < N; w++)
    for (u = 0; u < N; u++)
      for (v = 0; v < N; v++)
        if (weight[u][w] + weight[w][v] < weight[u][v])
          weight[u][v] = weight[u][w] + weight[w][v];
  printf("%d\n", weight[A - 1][R - 1]);
  return 0;
}
