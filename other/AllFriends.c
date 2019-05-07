#include<stdio.h>
#include<string.h>
#include<stdlib.h>

enum{ MAXN    =  128};
enum{ SETELTS =    4};
enum{ MAXS    = 1000};
enum{ HSIZE   = 3007};

unsigned amark = 2;

typedef struct{
  unsigned e[SETELTS];
}set;

set graph[MAXN];
set sets[MAXS + 1];



struct hashel{
  unsigned hval;
  unsigned mark;
  set *s;
} htab[HSIZE];

unsigned hval(set *s){
  unsigned i, v = 0;
  for (i = 0; i < SETELTS; i++)
    v ^= s->e[i];
  return v % HSIZE;
}
void hash (set *s){
  unsigned val = hval (s), 
           idx = val;
  while (htab[idx].mark == amark){
    idx++;
    if (idx == HSIZE)
      idx = 0;
  }
  htab[idx].hval = val;
  htab[idx].mark = amark;
  htab[idx].s    = s;
}
int set_eq (set *s1, set *s2){
  unsigned i;
  for (i = 0; i < SETELTS; i++)
    if (s1->e[i] != s2->e[i])
      return 0;
  return 1;
}
int hfind (set *s){
  unsigned val = hval (s), 
           idx = val;
  while (amark <= htab[idx].mark){
    if (htab[idx].hval == val && set_eq (htab[idx].s, s))
      return idx;
    idx++;
    if (idx == HSIZE)
      idx = 0;
  }
  return -1;
}
void unhash (set *s){
  int index = hfind (s);
  if (index == -1)
    abort ();
  htab[index].mark = amark + 1;
}
int present_p (set *s){
  return hfind (s) != -1;
}
void set_new (set *s){
  memset (s, 0, sizeof (set));
}
void set_add (set *s, int elt){
  int eltno, 
      bitno;
  eltno = elt / 32;
  bitno = elt % 32;
  s->e[eltno] |= 1 << bitno;
}
int in_set_p (set *s, int elt){
  int eltno, 
      bitno;
  eltno = elt / 32;
  bitno = elt % 32;
  return (s->e[eltno] >> bitno) & 1;
}
int set_intersect (set *a, set *b, set *c){
  int i, ret = 1, val, new_val;
  for (i = 0; i < SETELTS; i++){
    val = a->e[i];
    new_val = val & b->e[i];
    c->e[i] = new_val;
    ret &= (val == new_val);
  }
  return ret;
}
int max_clique_p (set *s, int n){
  int i;
  set tmp;
  for (i = 0; i < n; i++)
    if (!in_set_p (s, i) && set_intersect (s, &graph[i], &tmp))
      return 0;
  return 1;
}
int gen_cliques(int n){
  int i, k, new_k, elt = n - 1;
  if (n == 1){
    set_new (&sets[0]);
    set_add (&sets[0], 0);
    hash (&sets[0]);
    return 1;
  }
  k = gen_cliques (n - 1);
  if (k > MAXS)
    return k;
  new_k = k;
  for (i = 0; i < k; i++){
    if (set_intersect (&sets[i], &graph[elt], &sets[new_k])){
      unhash (&sets[i]);
      set_add (&sets[i], elt);
      hash (&sets[i]);
    }
    else{
      set_add (&sets[new_k], elt);
      if (!present_p (&sets[new_k]) && max_clique_p (&sets[new_k], n)){
        hash (&sets[new_k]);
        new_k++;
      }
    }
    if (new_k > MAXS)
      return new_k;
  }
  return new_k;
}
int main(){
  int n, m, i, x, y, k;
  while (1){
    if (scanf ("%d%d", &n, &m) != 2)
      return 0;
    for (i = 0; i < n; i++)
      set_new (&graph[i]);
    for (i = 0; i < m; i++){
      scanf ("%d%d", &x, &y);
      x--, y--;
      set_add (&graph[x], y);
      set_add (&graph[y], x);
    }
    k = gen_cliques (n);
    if (k > MAXS)
      printf ("Too many maximal sets of friends.\n");
    else
      printf ("%d\n", k);
    amark+=2;
  }
  return 0;
}
