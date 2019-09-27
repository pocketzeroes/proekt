#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<float.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define pbpt(zpv, zvv) zpv.ptr = pushbackPt(zpv.ptr, &zpv.sz, zvv)
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
double in_nextDbl(){
  double x;
  scanf("%lf", &x);
  return x;
}

typedef struct Range{
    double start, end;
}Range;
Range NIL={-DBL_MAX, -DBL_MAX};

Range newRange(double start, double end){
    return(Range){start, end};
}
#define pbr(zpv, zvv) zpv.ptr = pushbackR(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Range*pushbackR(Range*array, int *size, Range value){
  Range*output = resizeArray(array, Range, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	Range*ptr;
	int sz;
}vecr;
vecr newVecR(){
	vecr rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int cmpr(const void*pa, const void*pb){
    Range*this =(Range*)pa;
    Range*other=(Range*)pb;
    return(this->start > other->start)?(1):(-1);
}
typedef struct Point{
    double x,y;
}Point;
Point newPoint(double x, double y){
    return(Point){x,y};
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Point*pushbackPt(Point*array, int *size, Point value){
    Point*output = resizeArray(array, Point, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	Point*ptr;
	int sz;
}vecpt;
vecpt newVecPt(){
	vecpt rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

double distance(Point this, Point other){
    double dx = this.x - other.x;
    double dy = this.y - other.y;
    return sqrt(dx*dx + dy*dy);
}
inline bool equals(Point this, Point other){
    return this.x == other.x && this.y == other.y;
}
///////////////////////////////////////////
typedef struct Circle{
    Point  p;
    double r;
}Circle;

Circle newCircle (double x, double y, double r){
    Circle this;
    this.p = newPoint(x, y);
    this.r = r;
    return this;
}
bool intersects(Circle this, Circle other){
    if(distance(other.p, this.p) < this.r + other.r + 1e-8)
        return true;
    return false;
}
Point*intersectionPoints(Circle this, Circle other, int*rsz){
    if(fabs(distance(other.p, this.p) - (this.r + other.r)) < 1e-8){
        Point*intersections = calloc(1,sizeof(Point));
        double dx = this.p.x - other.p.x;
        double dy = this.p.y - other.p.y;
        double combinedr = this.r + other.r;
        double newX = other.p.x + dx * other.r / combinedr;
        double newY = other.p.y + dy * other.r / combinedr;
        intersections[0] = newPoint(newX, newY);
       *rsz=1;
        return intersections;
    }
    Point*intersections = calloc(2, sizeof(Point));
    double x0 = this.p.x;
    double x1 = other.p.x;
    double y0 = this.p.y;
    double y1 = other.p.y;
    double d = distance(this.p, other.p);
    double a = (this.r*this.r - other.r*other.r + d*d)/(2*d);
    double h = sqrt(this.r*this.r - a*a);
    double x2 = x0 + a*(x1 - x0)/d;
    double y2 = y0 + a*(y1 - y0)/d;
    double x3 = x2 + h*(y1 - y0)/d;
    double y3 = y2 - h*(x1 - x0)/d;
    double x4 = x2 - h*(y1 - y0)/d;
    double y4 = y2 + h*(x1 - x0)/d;
    intersections[0] = newPoint(x3, y3);
    intersections[1] = newPoint(x4, y4);
   *rsz=2;
    return intersections;
}
Range lineIntersection(Circle this, Point start, Point end){
    double x1 = start.x;
    double x2 = end.x;
    double x3 = this.p.x;
    double y1 = start.y;
    double y2 = end.y;
    double y3 = this.p.y;
    double dx = x1 - x2;
    double dy = y1 - y2;
    double d = dx*dx + dy*dy;
    double u = ((x3-x1)*(x2-x1) + (y3-y1)*(y2-y1)) / d;
    double x = x1 + u*(x2 - x1);
    double y = y1 + u*(y2 - y1);
    double dist = distance(newPoint(x, y), this.p);
    if(dist > this.r)
        return NIL;
    double length = distance(start, end);
    double adj = this.r*this.r - dist*dist;
    if(adj < 0)
        return NIL;
    double midPoint;
    if((x2 - x1) != 0)
        midPoint = (x - x1) / (x2 - x1);
    else
        midPoint = (y - y1) / (y2 - y1);
    double dFraction = sqrt(adj) / length;
    return newRange(midPoint - dFraction - 1e-8 , midPoint + dFraction + 1e-8);
}

typedef struct Edge{
    int    end;
    double distance;
}Edge;

Edge newEdge(int end, double distance){
    Edge this;
    this.end      = end;
    this.distance = distance;
    return this;
}
#define pbe(zpv, zvv) zpv.ptr = pushbackE(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Edge*pushbackE(Edge*array, int *size, Edge value){
  Edge*output = resizeArray(array, Edge, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	Edge*ptr;
	int sz;
}vece;
vece newVecE(){
	vece rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

inline int getEnd(Edge this){
    return this.end;
}
inline double getDistance(Edge this){
    return this.distance;
}
    


int main(){
    vecpt points=newVecPt();
    double sx=in_nextDbl();
    double sy=in_nextDbl();
    Point start = newPoint(sx, sy);
    double ex=in_nextDbl();
    double ey=in_nextDbl();
    Point end   = newPoint(ex, ey);
    pbpt(points, start);
    pbpt(points, end  );
    int inputCircles = in_nextInt();
    int numCircles = 0;
    Circle circles[inputCircles]; clr(circles);
    for(int i=0; i<inputCircles; ++i){
        double cx=in_nextDbl();
        double cy=in_nextDbl();
        Point circleCenter = newPoint(cx, cy);
        double radius = in_nextDbl();
        bool flag = true;
        for(int j=0; j<numCircles; ++j){
            if(equals(circleCenter, circles[j].p)){
                flag = false;
                if(radius > circles[j].r)
                    circles[j] = newCircle(circleCenter.x, circleCenter.y, radius);
                break;
            }
        }
        if(flag){
            circles[numCircles] = newCircle(circleCenter.x, circleCenter.y, radius);
            ++numCircles;
        }
    }
    for(int i=0; i<numCircles-1; ++i){
        for(int j=i+1; j<numCircles; ++j){
            if(!intersects(circles[i], circles[j]))
                continue;
            int intrsz;
            Point*intersections = intersectionPoints(circles[i], circles[j], &intrsz);
            pbpt(points, intersections[0]);
            if(intrsz > 1)
                pbpt(points, intersections[1]);
        }
    }
    int numPoints = points.sz;
    vece adjList[numPoints]; clr(adjList);

    for(int i=0; i<numPoints-1; ++i){
        Point firstPoint = points.ptr[i];
        for (int j = i+1; j < numPoints; ++j) {
            Point secondPoint = points.ptr[j];
            vecr ranges = newVecR();//of Range
            for(int k=0; k<numCircles; ++k){
                Range range = lineIntersection(circles[k], firstPoint, secondPoint);
                if(range.start == -DBL_MAX&&
                   range.end   == -DBL_MAX  )
                   continue;
                pbr(ranges, range);
            }
            qsort(ranges.ptr, ranges.sz, sizeof(Range), cmpr);
            double currPos = 1e-8;
            for(int z=0; z<ranges.sz; z++){Range range = ranges.ptr[z];
                if(range.start > currPos)
                    break;
                if(range.end < currPos)
                    continue;
                currPos = range.end;
            }
            if(currPos < 1)
                continue;
            double dst = distance(firstPoint, secondPoint);
            pbe(adjList[i], newEdge(j, dst));
            pbe(adjList[j], newEdge(i, dst));
        }
    }
    double dista[numPoints]; clr(dista);
    dista[0] = 0;
    for(int i=1; i<numPoints; ++i)
        dista[i] = 1e30;
    bool processed[numPoints]; clr(processed);
    while(1){
        int toProcess = -1;
        double best = 1e25;
        for(int i=0; i<numPoints; ++i){
            if(!processed[i] && dista[i] < best){
                toProcess = i;
                best = dista[i];
            }
        }
        if(toProcess == -1)
            break;
        processed[toProcess] = true;
        for(int z=0;z<adjList[toProcess].sz;z++){Edge edg = adjList[toProcess].ptr[z];
            dista[getEnd(edg)] = fmin(dista[getEnd(edg)], dista[toProcess] + getDistance(edg));
        }
    }
    if(dista[1] > 1e25)
        puts("impossible");
    else
        printf("%.20lf\n", dista[1]);
    return 0;
}
