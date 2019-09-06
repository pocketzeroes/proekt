#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXN 10000
#define EPS 1e-5

typedef struct pnt{
  int x,y;
  struct pnt *prev, *next;
} pnt;
static pnt pnts[MAXN];
static int pnt_by_xy (const void *a, const void *b){
  const pnt *pa = (const pnt *) a;
  const pnt *pb = (const pnt *) b;
  if (pa->x != pb->x)
    return pa->x - pb->x;
  return pa->y - pb->y;
}
static void diff (const pnt *a, const pnt *b, pnt *d){
  d->x = a->x - b->x;
  d->y = a->y - b->y;
}
static int orient2 (const pnt *d21, const pnt *d32){
  long long vp = (long long) d21->x * (long long) d32->y - (long long) d21->y * (long long) d32->x;
  if (vp < 0)
    return -1;
  else if (vp > 0)
    return 1;
  else
    return 0;
}
static int orient (const pnt *p1, const pnt *p2, const pnt *p3){
  pnt d21, d32;
  diff (p2, p1, &d21);
  diff (p3, p2, &d32);
  return orient2 (&d21, &d32);
}
static void convex_hull (int n, pnt p[]){
  pnt *last, *t, *b, *f;
  int i;
  qsort (p, n, sizeof (pnt), pnt_by_xy);
  i = 1;
  while (i < n - 1 && p[i + 1].x == p[0].x)
    i++;
  p[0].next = &p[i];
  p[i].next = &p[0];
  p[0].prev = &p[i];
  p[i].prev = &p[0];
  last = &p[i];
  for (i++; i < n; i++)
    {
      b = last;
      f = b->next;
      while (orient (&p[i], b, f) > 0)
      {
        b = f;
        f = b->next;
      }
      t = last;
      f = t->prev;
      while (orient (&p[i], t, f) < 0)
      {
        t = f;
        f = t->prev;
      }
      if(b==last && t==last)
        b = last->next;
      t->next = &p[i];
      p[i].next = b;
      p[i].prev = t;
      b->prev = &p[i];
      last = &p[i];
    }
}
typedef struct{
  pnt *l, *r, *t, *b;
  pnt dir;
} state;
static void init_leading (pnt *s, state *in){
  int maxx = s->x, miny = s->y, maxy = s->y;
  pnt *a;
  in->l = in->r = in->t = in->b = s;
  in->dir.x = 0;
  in->dir.y = 1;
  for (a = s->next; a != s; a = a->next)
  {
    if (a->x > maxx)
    {
      maxx = a->x;
      in->r = a;
    }
    if (a->y > maxy)
    {
      maxy = a->y;
      in->t = a;
    }
    if (a->y < miny)
    {
      miny = a->y;
      in->b = a;
    }
  }
}
static int hull_length (pnt *s){
  int l = 1;
  pnt *a;
  for (a = s->next; a != s; a = a->next)
    l++;
  return l;
}
static void rot90 (pnt *d)
{
  pnt o = *d;
  d->x = o.y;
  d->y = -o.x;
}
static void rot180 (pnt *d){
  pnt o = *d;
  d->x = -o.x;
  d->y = -o.y;
}
static void rot270 (pnt *d){
  pnt o = *d;
  d->x = -o.y;
  d->y = o.x;
}
static void next_state (const state *a, state *n){
  pnt dir1, dir2, dir3, dir4;
  diff (a->l->next, a->l, &dir1);
  diff (a->r->next, a->r, &dir2);
  rot180 (&dir2);
  diff (a->t->next, a->t, &dir3);
  rot270 (&dir3);
  diff (a->b->next, a->b, &dir4);
  rot90 (&dir4);
  *n = *a;
  if (orient2 (&dir1, &dir2) <= 0 &&
      orient2 (&dir1, &dir3) <= 0 &&
      orient2 (&dir1, &dir4) <= 0)
    {
      n->l = a->l->next;
      n->dir = dir1;
    }
  else if (orient2 (&dir2, &dir3) <= 0 &&
     orient2 (&dir2, &dir4) <= 0)
    {
      n->r = a->r->next;
      n->dir = dir2;
    }
  else if (orient2 (&dir3, &dir4) <= 0)
    {
      n->t = a->t->next;
      n->dir = dir3;
    }
  else
    {
      n->b = a->b->next;
      n->dir = dir4;
    }
}
static double per (const pnt *a, const pnt *b,  double angle){
  pnt d;
  double baang, alfa, len, s, c;
  diff (b, a, &d);
  len = sqrt (d.x * d.x + d.y * d.y);
  if (len < EPS)
    return 0;
  baang = atan2 (d.y, d.x);
  alfa = angle - baang;
  s = sin (alfa);
  c = cos (alfa);
  if (s < -EPS || c < -EPS)
    abort ();
  return len * (s + c);
}
static double perimeter_at_angle (const state *a, double angle){
  return (per (a->l, a->t, angle) + per (a->t, a->r, angle - M_PI /2) + per (a->r, a->b, angle - M_PI) + per (a->b, a->l, angle + M_PI/2));
}
static double value (const state *a){
  double ang = atan2 (a->dir.y, a->dir.x);
  return perimeter_at_angle (a, ang);
}
int main(){
  int i, n, nh;
  state a, nx;
  double best, av;
  while (scanf ("%d", &n) == 1){
    for (i = 0; i < n; i++)
      scanf ("%d%d", &pnts[i].x, &pnts[i].y);
    convex_hull (n, pnts);
    init_leading (&pnts[0], &a);
    nh = hull_length (&pnts[0]);
    best = 2 * (a.r->x - a.l->x + a.t->y - a.b->y);
    next_state (&a, &nx);
    a = nx;
    for (i = 0; i < nh; i++)
    {
      av = value (&a);
      if (av < best)
        best = av;
      next_state (&a, &nx);
      a = nx;
    }
    printf ("%.6f\n", best);
  }
  return 0;
}