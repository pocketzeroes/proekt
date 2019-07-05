#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int nd, done[200];
int i,j,k;
struct pp {
   double a, b, c;
} p[100];
double x,y,xx,yy,a,b,c;
int np, i,j,j;
char hc[20];
double xa, xb, ya, yb, area, triarea;
int nx;


void linepoints(double x1, double y1, double x2, double y2, double *a, double *b, double *c){
  *a = y2 - y1;
  *b = x1 - x2;
  *c = *a * x1 + *b * y1;
}
void bi(double x1, double y1, double x2, double y2, double *a, double *b, double *c){
  *a = 2*(x2-x1);
  *b = 2*(y2-y1);
  *c = x2*x2 + y2*y2 - x1*x1 - y1*y1;
}
int isct(double a, double b, double c, double aa, double bb, double cc, double *x, double *y){
  double det = a*bb - b*aa;
  if (fabs(det) < 1e-10) 
    return 0;
  *x = (-b*cc + c*bb)/det;
  *y = (a*cc - c*aa)/det;
  return 1;
}
int main(){
  linepoints(0, 0, 0,10,&a,&b,&c);  p[np].a = a; p[np].b = b; p[np++].c = c;
  linepoints(0,10,10,10,&a,&b,&c);  p[np].a = a; p[np].b = b; p[np++].c = c;
  linepoints(10,10,10,0,&a,&b,&c);  p[np].a = a; p[np].b = b; p[np++].c = c;
  linepoints(10, 0, 0,0,&a,&b,&c);  p[np].a = a; p[np].b = b; p[np++].c = c;
  while (3 == scanf("%lf%lf %s",&xx,&yy,hc)){
    if (strcmp(hc,"Colder")) bi(x,y,xx,yy,&p[np].a,&p[np].b,&p[np].c),np++;
    if (strcmp(hc,"Hotter")) bi(xx,yy,x,y,&p[np].a,&p[np].b,&p[np].c),np++;
    area = 0;
    nd = 0;
    for (i=0;i<np;i++){
      nx = 0;
      for (j=0;j<np;j++) {
        if (isct(p[i].a,p[i].b,p[i].c,p[j].a,p[j].b,p[j].c,&x,&y)){
          int isin = 1;
          for (k=0;k<np;k++) {
            if (p[k].a*x + p[k].b*y - p[k].c < -.000001) 
              isin = 0;
          }
          if (isin){
            if (!nx){
              nx++;
              xa = x;
              ya = y;
            } 
            else if (nx<2 && (fabs(x-xa)>.000001 || fabs(y-ya)>.000001)){
              nx++;
              xb = x;
              yb = y;
            }
          }
        }
      }
      if (nx == 2){
        for (j=0;j<nd;j++){
          if (fabs(p[i].a*p[done[j]].b - p[i].b*p[done[j]].a) < .000001 && 
              fabs(p[i].a*p[done[j]].c - p[i].c*p[done[j]].a) < .000001 &&
              fabs(p[i].b*p[done[j]].c - p[i].c*p[done[j]].b) < .000001)
                break;
        }
        if (j == nd){
          done[nd++] = i;
          triarea = -p[i].c / hypot(p[i].a,p[i].b) * hypot(xa-xb,ya-yb) / 2;
          area += triarea;
        }
      }
    }
    if (nd < 3 || area < .000001)
      area = 0;
    printf("%0.10lf\n", area);
    x = xx;
    y = yy;
  }
  return 0;
}
