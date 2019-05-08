#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
double *pushbackD(double *array, int *size, double value) {
    double *output = resizeArray(array, double, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
  double*ptr;
  int sz;
}vecd;
vecd newVecD() {
  vecd rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
int cmpDbl(const void*pa, const void*pb){
  double*a =(double*)pa;
  double*b =(double*)pb;
  return(*a < *b)?-1:1;
}

char GRID   = 'G';
char CIRCLE = 'C';

typedef struct{
    double x, y;
    char type;
}intersection;

vecd areas;


double calcSlice(intersection*i1, intersection*i2, double r){
    double dx = i1->x - i2->x;
    double dy = i1->y - i2->y;
    double secant = sqrt(dx*dx + dy*dy);
    double ans = r*r*asin(secant/(2*r)) - secant*sqrt(r*r-secant*secant/4)/2;
    return ans;
}
bool checkInside(double x, double y, double r){
    return (x*x+y*y <= r*r);
}
void calcInOutIntersection (double xa, double ya, double xb, double yb, double r, intersection*a, int*nInt){
    if (ya == yb) {
        double x = sqrt(r*r - ya*ya);
        if (x > xa && x > xb)
            x = -x;
        a[*nInt].x = x;
        a[*nInt].y = ya;
        a[*nInt].type = CIRCLE;
       (*nInt)++;
    }
    else {
        double y = sqrt(r*r - xa*xa);
        if (y > ya && y > yb)
            y = -y;
        a[*nInt].x = xa;
        a[*nInt].y = y;
        a[*nInt].type = CIRCLE;
       (*nInt)++;
    }
}
void calcOutOutIntersection(double xa, double ya, double xb, double yb, double r, intersection*a, int*nInt){
    if (xa == xb) {    
        if (xa <= -r || xa >= r)
            return;     
        double yhigh = sqrt(r*r - xa*xa);
        double ylow = -yhigh;
        if (ya < yb) {
            if (ya < ylow && ylow < yb) {
                a[*nInt].x = xa;
                a[*nInt].y = ylow;
                a[*nInt].type = CIRCLE;
                (*nInt)++;
            }
            if (ya < yhigh && yhigh < yb) {
                a[*nInt].x = xa;
                a[*nInt].y = yhigh;
                a[*nInt].type = CIRCLE;
                (*nInt)++;
            }
        }
        else {
            if (yb < yhigh && yhigh < ya) {
                a[*nInt].x = xa;
                a[*nInt].y = yhigh;
                a[*nInt].type = CIRCLE;
                (*nInt)++;
            }
            if (yb < ylow && ylow < ya) {
                a[*nInt].x = xa;
                a[*nInt].y = ylow;
                a[*nInt].type = CIRCLE;
                (*nInt)++;
            }
        }
    }
    else {    
        if (ya <= -r || ya >= r)
            return;          
        double xhigh = sqrt(r*r - ya*ya);
        double xlow = -xhigh;
        if (xa < xb) {
            if (xa < xlow && xlow < xb) {
                a[*nInt].x = xlow;
                a[*nInt].y = ya;
                a[*nInt].type = CIRCLE;
                (*nInt)++;
            }
            if (xa < xhigh && xhigh < xb) {
                a[*nInt].x = xhigh;
                a[*nInt].y = ya;
                a[*nInt].type = CIRCLE;
                (*nInt)++;
            }
        }
        else {
            if (xb < xhigh && xhigh < xa) {
                a[*nInt].x = xhigh;
                a[*nInt].y = ya;
                a[*nInt].type = CIRCLE;
                (*nInt)++;
            }
            if (xb < xlow && xlow < xa) {
                a[*nInt].x = xlow;
                a[*nInt].y = ya;
                a[*nInt].type = CIRCLE;
                (*nInt)++;
            }
        }
    }
}
double calcArea1(intersection*a, int nInt, double r, double x1, double y1, double x2, double y2){
    double area = 0.0;
    a[nInt] = a[0];
    for(int i=0; i<nInt; i++) {
        area += (a[i+1].x - a[i].x)*(a[i+1].y + a[i].y)/2;
        if (a[i].type == CIRCLE && a[i+1].type == CIRCLE){
            if (a[i].x != a[i+1].x && a[i].y != a[i+1].y){
                area += calcSlice(&a[i], &a[i+1], r);
            }
            else if (a[i].x == a[i+1].x && (a[i].x != x1 && a[i].x != x2)) {
                area += calcSlice(&a[i], &a[i+1], r);
            }
            else if (a[i].y == a[i+1].y && (a[i].y != y1 && a[i].y != y2)) {
                area += calcSlice(&a[i], &a[i+1], r);
            }
        }
    }
    return area;
}
double calcArea2(intersection*a, int nInt, double r, double x1, double y1, double x2, double y2){
    double area = calcArea1(a, nInt, r, x1, y1, x2, y2);
    a[nInt] = a[0];
    if (x1 <= -r && x2 >= r)
        return area;
    else if (y1 <= -r && y2 >= r)
        return area;
    for(int i=0; i<nInt; i++) {
        if ((a[i+1].x - a[i].x)*a[i].y - (a[i+1].y - a[i].y)*a[i].x < 0.0) { 
            area += r*r*M_PI - 2*calcSlice(&a[i], &a[i+1], r);
            break;
        }
    }
    return area;
}
double calcArea(double x1, double y1, double x2, double y2, double r){
    intersection ints[9];
    int nInt = 0;
    double xvals[4] = {x1, x1, x2, x2};
    double yvals[4] = {y1, y2, y2, y1};
    double xa = xvals[3];
    double ya = yvals[3];
    bool insidea = checkInside(xa, ya, r);
    int ngrid = 0, ncircle;
    for(int i=0; i<4; i++) {
        double xb = xvals[i];
        double yb = yvals[i];
        bool insideb = checkInside(xb, yb, r);
        if (insideb) {
            if (!insidea)
                calcInOutIntersection(xa, ya, xb, yb, r, ints, &nInt);
            ints[nInt].x = xb;
            ints[nInt].y = yb;
            ints[nInt].type = GRID;
            ngrid++;
            nInt++;
        }
        else if (insidea) {
            calcInOutIntersection(xa, ya, xb, yb, r, ints, &nInt);
        }
        else {
            calcOutOutIntersection(xa, ya, xb, yb, r, ints, &nInt);
        }
        xa = xb;
        ya = yb;
        insidea = insideb;
    }
    if (ngrid > 0)
        return calcArea1(ints, nInt, r, x1, y1, x2, y2);
    else if (nInt == 0) {
        if (x1*x2 < 0 && y1*y2 < 0)
            return r*r*M_PI;
        else
            return 0.0;
    }
    else if (nInt ==  2) {
        double area = calcSlice(&ints[0], &ints[1], r);
        if (x1*x2 < 0 && y1*y2 < 0)
            return r*r*M_PI - area;   
        else
            return area;
    }
    else if (nInt == 4)
        return calcArea2(ints, nInt, r, x1, y1, x2, y2);
    else 
        return calcArea1(ints, nInt, r, x1, y1, x2, y2);
}
int main(){
    int r, delx, dely, startx, starty;
    double percent;
    scanf("%d %d %d %d %d %lf", &r, &delx, &dely, &startx, &starty, &percent);
    int xlow = startx - ((startx + r)/delx)*delx;
    if (xlow > -r)
        xlow -= delx;
    int ylow = starty - ((starty + r)/dely)*dely;
    if (ylow > -r)
        ylow -= dely;
    int xhigh = startx + ((r-startx)/delx)*delx;
    if (xhigh < r)
        xhigh += delx;
    int yhigh = starty + ((r-starty)/dely)*dely;
    if (yhigh < r)
        yhigh += dely;
    for(int x = xlow; x < xhigh; x += delx) {
        for(int y = ylow; y < yhigh; y += dely) {
            double area = calcArea(x, y, x+delx, y+dely, r);
            if(area > 0.0)
               areas.ptr = pushbackD(areas.ptr, &areas.sz, area);
        }
    }
    qsort(areas.ptr, areas.sz, sizeof(double), cmpDbl);
    double cutoff = percent*areas.ptr[areas.sz-1];
    double sum = 0;
    double smallCount = 0;
    for(int z=0;z<areas.sz;z++){double area = areas.ptr[z];
        if (area < cutoff)
            smallCount++;
        sum += area;
    }
    if (fabs(sum - r*r*M_PI)/(r*r*M_PI) > 0.0001)
        puts("ERROR: sum of all pieces < pizza area");
    printf("%.0lf\n", smallCount);
    return 0;
}
