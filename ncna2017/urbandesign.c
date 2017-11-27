#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct{
  double x, y;
}point;
typedef struct{
  point p1, p2;
}line;

int intersect(point *p,line l1, line l2)
{
  double A,B,C,D,E,F;
  A = l1.p1.x * l1.p2.y - l1.p1.y * l1.p2.x;
  B = l2.p1.x * l2.p2.y - l2.p1.y * l2.p2.x;
  C = l1.p1.x - l1.p2.x;
  D = l2.p1.x - l2.p2.x;
  E = l1.p1.y - l1.p2.y;
  F = l2.p1.y - l2.p2.y;
  p->x = (A*D - C*B) / (C*F - E*D);
  p->y = (A*F - E*B) / (C*F - D*E);
  if(isnan(p->x) || isinf(p->x) || isnan(p->y) || isinf(p->y))
    return 0;
  return 1;
}
int liesbetween(point p, line l)
{
  double dxc,dyc,dxl,dyl,cross;
  dxc = p.x - l.p1.x;
  dyc = p.y - l.p1.y;
  dxl = l.p2.x - l.p1.x;
  dyl = l.p2.y - l.p1.y;
  if (fabs(dxl) >= fabs(dyl))
    return dxl > 0 ? l.p1.x<=p.x && p.x<=l.p2.x : l.p2.x<=p.x && p.x<=l.p1.x;
  else
    return dyl > 0 ? l.p1.y<=p.y && p.y<=l.p2.y : l.p2.y<=p.y && p.y<=l.p1.y;
}
int main()
{
  line *streets;
  line properties;
  point ip;
  int i, j, Nstr, Ntst, count;
  int fline=1;
  double t1, t2, t3, t4;
  scanf("%d", &Nstr);
  fline++;
  streets = malloc(sizeof(line)*Nstr);
  for(i=0; i<Nstr; i++,fline++)
    scanf("%lf %lf %lf %lf", &(streets[i].p1.x),&(streets[i].p1.y), &(streets[i].p2.x),&(streets[i].p2.y));
  scanf("%d", &Ntst);
  fline++;
  for(i=0; i<Ntst; i++,fline++)
  {
    scanf("%lf %lf %lf %lf", &(properties.p1.x),&(properties.p1.y), &(properties.p2.x),&(properties.p2.y));
    for(j=0,count=0; j<Nstr; j++)
      if(intersect(&ip,properties,streets[j])&&liesbetween(ip,properties))
        count++;
      if(count&1)
        printf("different\n");
      else
        printf("same\n");
  }
  free(streets);
  return 0;
}
