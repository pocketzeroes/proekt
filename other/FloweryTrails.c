#include<stdio.h>
#include<stdlib.h>

#define MAXVERTS 10000

#ifdef LONGVALUE
typedef unsigned long VALUE;
#define FORMATPRINT "%lu\n"
#define READVALUE "%lu"
#define PRINTVALUE "%lu"
#endif
#ifndef LONGVALUE
typedef int VALUE;
#define FORMATPRINT "%d\n"
#define READVALUE "%d"
#define PRINTVALUE "%d"
#endif
typedef struct arco {
  int no_final;
  VALUE valor;
  int multiplicidade;
  struct arco *prox;
} ARCO;
typedef struct no {
  ARCO *adjs;
} NO;
typedef struct graph {
  NO verts[MAXVERTS+1];
  int nvs, narcos;
} GRAFO;

GRAFO *new_graph(int nverts);
void destroy_graph(GRAFO *g);
void insert_new_arc(int i, int j, VALUE valor_ij, GRAFO *g);
void remove_arc(ARCO *arco, int i, GRAFO *g);
ARCO *find_arc(int i, int j, GRAFO *g);

#define NUM_VERTICES(g) ( (g) -> nvs )
#define NUM_ARCOS(g) ( (g) -> narcos )
#define ADJS_NO(i,g) ( (g) -> verts[i].adjs )
#define PROX_ADJ(arco) ((arco) -> prox)
#define ADJ_VALIDO(arco) (((arco) != NULL))
#define EXTREMO_FINAL(arco) ((arco) -> no_final)
#define VALOR_ARCO(arco) ((arco) -> valor)
#define MULT_ARCO(arco) ((arco) -> multiplicidade)

static ARCO* cria_arco(int j, VALUE valor_ij);
static void free_arcs(ARCO *);

GRAFO *new_graph(int nverts){
  if (nverts > MAXVERTS) {
    fprintf(stderr,"Erro: %d > MAXVERTS\n",nverts);
    exit(EXIT_FAILURE);
  }
  GRAFO *g = (GRAFO *) malloc(sizeof(GRAFO));
  if (g == NULL) {
    fprintf(stderr,"Erro: falta memoria\n");
    exit(EXIT_FAILURE);
  }
  NUM_VERTICES(g) = nverts;
  NUM_ARCOS(g) = 0;
  while (nverts) {
    ADJS_NO(nverts,g) = NULL;
    nverts--;
  }
  return g;
}
void destroy_graph(GRAFO *g)
{
  int i;
  if (g != NULL) {
    for (i=1; i<= NUM_VERTICES(g); i++)
      free_arcs(ADJS_NO(i,g));
    free(g);
  }
}
void insert_new_arc(int i, int j, VALUE valor_ij, GRAFO *g)
{
  ARCO *arco = find_arc(i,j,g);
  if (arco == NULL) {
    arco = cria_arco(j,valor_ij);
    PROX_ADJ(arco) = ADJS_NO(i,g);
    ADJS_NO(i,g) = arco;
    NUM_ARCOS(g)++;
  }
  else {
    if (VALOR_ARCO(arco) > valor_ij) {
      VALOR_ARCO(arco) = valor_ij;
      MULT_ARCO(arco) = 1;
    } else if (VALOR_ARCO(arco) == valor_ij)
      MULT_ARCO(arco)++;
  }
}
void remove_arc(ARCO *arco, int i, GRAFO *g)
{
  if (arco != NULL) {
    ARCO *aux = ADJS_NO(i,g), *prev = NULL;
    while (aux != arco && ADJ_VALIDO(aux)) {
      prev = aux;
      aux = PROX_ADJ(aux);
    }
    if (aux == arco) {
      if (prev == NULL) {
  ADJS_NO(i,g)  = PROX_ADJ(arco);
      } else PROX_ADJ(prev) = PROX_ADJ(arco);
      free(arco);
      NUM_ARCOS(g)--;
    }
  }
}
ARCO *find_arc(int i, int j, GRAFO *g){
  ARCO *adj = ADJS_NO(i,g);
  while(adj != NULL && EXTREMO_FINAL(adj) != j)
    adj = PROX_ADJ(adj);
  return adj;
}
static ARCO *cria_arco(int j, VALUE valor)
{
  ARCO *arco = (ARCO *) malloc(sizeof(ARCO));
  if (arco == NULL) {
    fprintf(stderr,"ERROR: cannot create arc\n");
    exit(EXIT_FAILURE);
  }
  EXTREMO_FINAL(arco) = j;
  VALOR_ARCO(arco) = valor;
  PROX_ADJ(arco) = NULL;
  MULT_ARCO(arco) = 1;
  return arco;
}
static void free_arcs(ARCO *arco)
{
  if (arco == NULL) return;
  free_arcs(PROX_ADJ(arco));
  free(arco);
}
typedef struct qnode {
  int vert;
  VALUE vertkey;
} QNODE;
typedef struct heapMin {
  int sizeMax, size;
  QNODE *a;
  int *pos_a;
} HEAPMIN;
HEAPMIN *build_heap_min(VALUE v[], int n);
void insert(int v, VALUE key, HEAPMIN *q);
int extractMin(HEAPMIN *q);
void decreaseKey(int v, VALUE newkey, HEAPMIN *q);
void write_heap(HEAPMIN *q);
void destroy_heap(HEAPMIN *q);
#define POSINVALIDA 0
#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)
#define PARENT(i) ((i)/2)
static void heapify(int i,HEAPMIN *q);
static void swap(int i,int j,HEAPMIN *q);
static int compare(int i, int j, HEAPMIN *q);
static int pos_valida(int i,HEAPMIN *q);
static int compare(int i, int j, HEAPMIN *q){
  if (q -> a[i].vertkey < q -> a[j].vertkey)
    return -1;
  if (q -> a[i].vertkey == q -> a[j].vertkey)
    return 0;
  return 1;
}
static int pos_valida(int i, HEAPMIN *q) {
  return (i >= 1 && i <= q -> size);
}
int extractMin(HEAPMIN *q) {
  int vertv = q -> a[1].vert;
  swap(1,q->size,q);
  q -> pos_a[vertv] = POSINVALIDA;
  q -> size--;
  heapify(1,q);
  return vertv;
}
void decreaseKey(int vertv, VALUE newkey, HEAPMIN *q){
  int i = q -> pos_a[vertv];
  q -> a[i].vertkey = newkey;
  while(i > 1 && compare(i,PARENT(i),q) < 0){
    swap(i,PARENT(i),q);
    i = PARENT(i);
  }
}
static void heapify(int i,HEAPMIN *q) {
  int l, r, smallest;
  l = LEFT(i);
  if (l > q -> size) l = i;
  r = RIGHT(i);
  if (r > q -> size) r = i;
  smallest = i;
  if (compare(l,smallest,q) < 0)
    smallest = l;
  if (compare(r,smallest,q) < 0)
    smallest = r;
  if (i != smallest) {
    swap(i,smallest,q);
    heapify(smallest,q);
  }
}
static void swap(int i,int j,HEAPMIN *q){
  QNODE aux;
  q -> pos_a[q -> a[i].vert] = j;
  q -> pos_a[q -> a[j].vert] = i;
  aux = q -> a[i];
  q -> a[i] = q -> a[j];
  q -> a[j] = aux;
}
HEAPMIN *build_heap_min(VALUE vec[], int n){
  HEAPMIN *q = (HEAPMIN *)malloc(sizeof(HEAPMIN));
  int i;
  q -> a = (QNODE *) malloc(sizeof(QNODE)*(n+1));
  q -> pos_a = (int *) malloc(sizeof(int)*(n+1));
  q -> sizeMax = n;
  q -> size = n;
  for (i=1; i<= n; i++) {
    q -> a[i].vert = i;
    q -> a[i].vertkey = vec[i];
    q -> pos_a[i] = i;
  }
  for (i=n/2; i>=1; i--)
    heapify(i,q);
  return q;
}
void insert(int vertv, VALUE key, HEAPMIN *q)
{
  if (q -> sizeMax == q -> size) {
    fprintf(stderr,"Heap is full\n");
    exit(EXIT_FAILURE);
  }
  q -> size++;
  q -> a[q->size].vert = vertv;
  q -> pos_a[vertv] = q -> size;
  decreaseKey(vertv,key,q);
}
void write_heap(HEAPMIN *q){
  int i;
  printf("Max size: %d\n", q -> sizeMax);
  printf("Current size: %d\n", q -> size);
  printf("(Vert,Key)\n---------\n");
  for(i=1; i <= q -> size; i++){
    printf("(%d,", q->a[i].vert);
    printf(PRINTVALUE, q->a[i].vertkey);
    printf("\n");
  }
  printf("-------\n(Vert,PosVert)\n---------\n");
  for(i=1; i <= q -> sizeMax; i++)
    if (pos_valida(q -> pos_a[i],q))
      printf("(%d,%d)\n",i,q->pos_a[i]);
}
void destroy_heap(HEAPMIN *q){
  if (q != NULL) {
    free(q -> a);
    free(q -> pos_a);
    free(q);
  }
}

#define LMAX 1000
typedef struct list {
  int node;
  ARCO *arco;
  struct list *nxt;
} LISTNODE;
VALUE adapt_dijkstra(int source,int target,GRAFO *g);
VALUE flowers(int target,int source,LISTNODE *precs[],GRAFO *g);
int main(){
  int p, t, i, j, ne;
  VALUE fij;
  GRAFO *g;
  scanf("%d%d",&p,&t);
  g = new_graph(p);
  for(ne = 0; ne < t; ne++) {
    scanf("%d%d",&i,&j);
    scanf(READVALUE,&fij);
    if (i != j) {
      insert_new_arc(i+1,j+1,fij,g);
      insert_new_arc(j+1,i+1,fij,g);
    }
  }
  printf(FORMATPRINT,adapt_dijkstra(1,p,g));
  return 0;
}
void remove_precs(LISTNODE *prec);
LISTNODE *cria_prec_node(int v,ARCO *arcovw, LISTNODE *next) {
  LISTNODE *prec = malloc(sizeof(LISTNODE));
  if (prec == NULL) exit(1);
  prec -> node = v;
  prec -> arco = arcovw;
  prec -> nxt = next;
  return prec;
}
void remove_precs(LISTNODE *prec) {
  LISTNODE *aux;
  while (prec != NULL) {
    aux = prec -> nxt;
    free(prec);
    prec = aux;
  }
}
VALUE adapt_dijkstra(int source,int target,GRAFO *g) {
  VALUE dist[target+1];
  int i, v, w;
  VALUE infty = LMAX*(1+NUM_ARCOS(g)/2);
  HEAPMIN *heap;
  ARCO *adj;
  LISTNODE **precs = malloc((target+1)*sizeof(LISTNODE *));
  for(i=0;i <= target; i++) {
    dist[i] = infty;
    precs[i] = NULL;
  }
  dist[source]=0;
  heap = build_heap_min(dist, target);
  while((v = extractMin(heap))!= target) {
    adj = ADJS_NO(v,g);
    while(adj != NULL) {
      w = EXTREMO_FINAL(adj);
      if (dist[w] > dist[v]+VALOR_ARCO(adj)) {
  dist[w] = dist[v]+VALOR_ARCO(adj);
  if (precs[w] != NULL) remove_precs(precs[w]);
        precs[w] = cria_prec_node(v,adj,NULL);
        decreaseKey(w,dist[w],heap);
      } else if (dist[w] == dist[v]+VALOR_ARCO(adj))
        precs[w] = cria_prec_node(v,adj,precs[w]);
      adj = PROX_ADJ(adj);
    }
  }
  return 2*flowers(target,source,precs,g);
}
VALUE dfs_visit(int v,int source,int visited[],LISTNODE *precs[],GRAFO *g)
{
  VALUE total;
  int w;
  LISTNODE *precsv;
  ARCO *arco;
  visited[v] = 1;
  if (v == source) return 0;
  total = 0;
  precsv = precs[v];
  while (precsv != NULL)  {
    w = precsv -> node;
    arco = precsv -> arco;
    total += (VALOR_ARCO(arco)*MULT_ARCO(arco));
    if (!visited[w])
      total += dfs_visit(w,source,visited,precs,g);
    precsv = precsv -> nxt;
  }
  return total;
}
VALUE flowers(int target,int source,LISTNODE *precs[], GRAFO *g) {
  int i,visited[target+1];
  for(i=1; i <target+1; i++) visited[i] = 0;
  return dfs_visit(target,source,visited,precs,g);
}
