#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
double in_nextDouble(){
  double x;
  scanf("%lf", &x);
  return x;
}

double TWOPI = M_PI+M_PI;

typedef struct{
  double first;
  double second;
}pair;
pair newPair(double a, double b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

vecp ranges;
vecp temp  ;

void addRange(double lo, double hi){
    temp.sz=0;
    for(int z=0;z<ranges.sz;z++){pair range = ranges.ptr[z];
        if(hi>=range.first && range.second>=lo){
            lo = min( lo, range.first);
            hi = max( hi, range.second);
        }
        else
            temp.ptr = pushbackP(temp.ptr, &temp.sz, range);
    }
    vecp swap = ranges;
    ranges = temp;
    temp = swap;
    ranges.ptr = pushbackP(ranges.ptr, &ranges.sz, newPair(lo, hi));
}
double normalize(double a){
    while( a<0 ) a += TWOPI;
    while( a>=TWOPI ) a -= TWOPI;
    return a;
}
double getangle(double x1, double y1, double x2, double y2, double r){
    double px = x2;
    double qx = x1-x2;
    double py = y2;
    double qy = y1-y2;
    double a = qx*qx + qy*qy;
    double b = 2.0*(px*qx + py*qy);
    double c = px*px + py*py - r*r;
    double t = (-b + sqrt( b*b-4.0*a*c ))/(2.0*a);
    double x = px + qx*t;
    double y = py + qy*t;
    return normalize( atan2( y, x ) );
}
int main(){
    for(int c=1;;++c){
        int n = in_nextInt();
        double pr = in_nextDouble();
        double rx = in_nextDouble();
        double ry = in_nextDouble();
        double rr = in_nextDouble();
        if( n==0 )
            break;
        ranges.sz=0;
        for( int i=0; i<n; i++ ){
            double ox = in_nextDouble();
            double oy = in_nextDouble();
            double or = in_nextDouble();
            double dor = hypot( oy-ry, ox-rx );
            double aro = atan2( oy-ry, ox-rx );
            double aor = normalize( M_PI + aro );
            double theta = acos( (or+rr) / dor );
            double txo = ox + or*cos( aor + theta );
            double tyo = oy + or*sin( aor + theta );
            double txr = rx + rr*cos( aro + theta );
            double tyr = ry + rr*sin( aro + theta );
            double start = getangle( txo, tyo, txr, tyr, pr );
            txo = ox + or*cos( aor - theta );
            tyo = oy + or*sin( aor - theta );
            txr = rx + rr*cos( aro - theta );
            tyr = ry + rr*sin( aro - theta );
            double finish = getangle( txo, tyo, txr, tyr, pr );
            if( start<finish )
                addRange( start, finish );
            else{
                addRange( start, TWOPI );
                addRange( 0.0, finish );
            }
        }
        double visible = TWOPI;
        for(int z=0;z<ranges.sz;z++){pair range = ranges.ptr[z];
            visible -= (range.second-range.first);
        }
        printf("%.4f\n", visible/TWOPI );
    }
    return 0;
}
