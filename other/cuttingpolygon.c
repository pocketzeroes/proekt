#include<stdio.h>
#include<assert.h>
#include<math.h>
#include<stdlib.h>

enum{MAX = 1000};
typedef struct {
  double x, y;
}Point;
Point poly[MAX+10],
    ipoint[MAX+10];
Point a,b;
double EPS = 1e-8;
#define SQR(x) ((x)*(x))

double dist2d(Point a, Point b){
  return sqrt(SQR(a.x-b.x) + SQR(a.y-b.y));
}
int pt_in_poly(Point *p, int n, Point a){
  int i, j, c = 0;
  for (i = 0, j = n-1; i < n; j = i++) {
    if (dist2d(p[i],a)+dist2d(p[j],a)-dist2d(p[i],p[j]) < EPS)
      return 1;
    if ((((p[i].y<=a.y) && (a.y<p[j].y)) ||
         ((p[j].y<=a.y) && (a.y<p[i].y))) &&
        (a.x < (p[j].x-p[i].x) * (a.y - p[i].y)
               / (p[j].y-p[i].y) + p[i].x)) c = !c;
  }
  return c;
}
double dist_iline(Point a, Point b, Point p){
  return fabs(((a.y-p.y)*(b.x-a.x)-
               (a.x-p.x)*(b.y-a.y))
              /dist2d(a,b));
}
int isect_iline(Point a, Point b, Point c, Point d, Point *p){
  double r, denom, num1;
  if (dist_iline(c,d,a) < EPS && dist_iline(c,d,b) < EPS)
    return -1;
  num1  = (a.y - c.y) * (d.x - c.x) - (a.x - c.x) * (d.y - c.y);
  denom = (b.x - a.x) * (d.y - c.y) - (b.y - a.y) * (d.x - c.x);
  if (fabs(denom) >= EPS) {
    r = num1 / denom;
    p->x = a.x + r*(b.x - a.x);
    p->y = a.y + r*(b.y - a.y);
    return ((p->x-a.x)*(p->x-b.x) < 0 ||
      (p->y-a.y)*(p->y-b.y) < 0 ||
      fabs((p->x-a.x)*(p->x-b.x)) < EPS) ? 1 : 0;
  }
  if (fabs(num1) >= EPS)
    return 0;
  return -1;
}
int cmp( const void *a, const void *b) {
  const Point *ap = (Point *)a,
              *bp = (Point *)b;
  if (fabs(ap->x-bp->x) < EPS) {
    if (fabs(ap->y-bp->y) < EPS)
      return 0;
    if (ap->y < bp->y)
      return -1;
    return 1;
  }
  if (ap->x < bp->x)
    return -1;
  return 1;
}
void addifnew(Point c, int*cnt){
  for (int i=0; i< *cnt; i++)
    if (dist2d(ipoint[i],c) < EPS)
      return;
  ipoint[(*cnt)++] = c;
}
int main (){
  while (1) {
    int n, m;
    scanf("%d %d",&n, &m);
    if (!n)
      break;
    assert(2 < n && n <= MAX);
    for (int i=0;i<n;i++)
      scanf("%lf %lf", &poly[i].x, &poly[i].y);
    poly[n] = poly[0];
    for (;m;m--) {
      scanf("%lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y);
      int ip = 0;
      Point p;
      for (int i=0;i<n;i++){
        switch (isect_iline(poly[i], poly[i+1],a,b, &p)) {
          case 0: break;
          case 1: addifnew(p, &ip); break;
          case-1: addifnew(poly[i],   &ip);
                  addifnew(poly[i+1], &ip); break;
          default: assert(0);
        }
      }
      qsort(ipoint,ip,sizeof(Point),cmp);
      double dist = 0.0;
      for(int i=0;i+1<ip;i++) {
        Point m;
        m.x = (ipoint[i].x+ipoint[i+1].x)/2;
        m.y = (ipoint[i].y+ipoint[i+1].y)/2;
        if (pt_in_poly(poly, n, m))
          dist += dist2d(ipoint[i],ipoint[i+1]);
      }
      printf("%.3f\n",dist);
    }
  }
  return 0;
}
