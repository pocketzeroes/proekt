#include<stdio.h>
#include<stdlib.h>

enum{ MAX_DIM     =    32};
enum{ MAX_HEIGHT  =    32};
enum{ HASH_SIZE   =  1007};
enum{ MAX_ANSWERS = 10000};
enum{ NOT_FOUND   =    -1};

struct _node{
  int *key;
  long val;
  struct _node *next;
};

typedef struct _node node;
typedef node *list;

list new_node(int[], long, list);
int equals(int[], int[], size_t);
int all_zeros(int[], size_t);
void sort_ints(int[], size_t);

list hashtable[HASH_SIZE];

long answers[MAX_ANSWERS];
int count = 0;



size_t hashcode(int v[], size_t len) {
  size_t code = 0;
  for (int i=0; i<len; i++)
    code = 31*code + (size_t)v[i];
  return code % HASH_SIZE;
}
long lookup(int key[], size_t len) {
  size_t h = hashcode(key, len);
  list p = hashtable[h];
  while(p != NULL) {
    if(equals(key, p->key, len))
      return p->val;
    p = p->next;
  }
  return NOT_FOUND;
}
int equals(int x[], int y[], size_t len){
  for(int i=0; i<len; i++) {
    if (x[i] != y[i])
      return 0;
  }
  return 1;
}
void insert(int key[], int len,  long val) {
  int h = hashcode(key, len);
  hashtable[h] = new_node(key, val, hashtable[h]);
}
list new_node(int key[], long val, list l) {
  node *p = (node*)malloc(sizeof(node));
  p -> key = key;
  p -> val = val;
  p -> next = l;
  return p;
}
int *new_key(int key[]) {
  int *new = (int*)malloc(MAX_DIM*sizeof(int));
  for (int i=0; i<MAX_DIM; i++)
    new[i] = key[i];
  return new;
}
long memoized(int xs[], int dim) {
  if (all_zeros(xs, dim))
    return 1;
  int *ys = new_key(xs);
  sort_ints(ys, dim);
  long v = lookup(ys, dim);
  if (v == NOT_FOUND) {
    v = 0;
    for (int i=0; i<dim; i++) {
      if(ys[i] == 0)
        continue;
      ys[i] -= 1;
      v += memoized(ys, dim);
      ys[i] += 1;
    }
    insert(ys, dim, v);
  }
  else
    free(ys);
  return v;
}
int all_zeros(int xs[], size_t len) {
  for(int i=0; i<len; i++)  {
    if(xs[i])
      return 0;
  }
  return 1;
}
int compare_ints(const void *p, const void *q){
    int x = *(const int *)p;
    int y = *(const int *)q;
    if (x < y)
      return -1;
    else if (x > y)
      return 1;
    return 0;
}
void sort_ints(int *xs, size_t n){
    qsort(xs, n, sizeof *xs, &compare_ints);
}
void output(long result) {
  answers[count] = result;
  int i = 0;
  while(answers[i] < result)
    i++;
  if (i<count && answers[i] == result)
    return;
  for(int j=count-1; j>=i; j--)
    answers[j+1] = answers[j];
  answers[i] = result;
  count ++;
}
void print_vec(int xs[], size_t len){
  printf("{ ");
  for(int i=0; i<len; i++)
    printf("%d ", xs[i]);
  printf("}\n");
}
void asc_coeffs(int n, int l, int h, int xs[], int len){
  if (n>1) {
    for (int c = l; c<=h; c++) {
      xs[len] = c;
      asc_coeffs(n-1, c, h-c, xs, len+1);
    }
  }
  else if (l<=h) {
    xs[len] = h;
    output(memoized(xs, len+1));
  }
}
int main(){
  int xs[MAX_DIM];
  int n, h;
  if (scanf("%d %d\n", &n, &h) != 2) {
    exit(-1);
  }
  asc_coeffs(n, 0, h-1, xs, 0);
  for(int i= 0; i<count; i++)
    printf("%ld\n", answers[i]);
  return 0;
}
