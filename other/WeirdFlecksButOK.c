#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

inline double min3(double a, double b, double c){ return fmin(a, fmin(b, c)); }

typedef struct{
    double x, y;
}pt;
pt newpt(double x, double y){
    return(pt){x,y};
}
#define pb(zpv, zvv) zpv.ptr = pushbackPt(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pt*pushbackPt(pt*array, int *size, pt value){
   pt*output = resizeArray(array, pt, *size + 1);
   output[(*size)++] = value;
   return output;
}
typedef struct{
	pt*ptr;
	int sz;
}vecpt;
vecpt newVecPt(){
	vecpt rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef struct{
    double x, y, z;
}p3;
p3 newp3(double x, double y, double z){
    return(p3){x,y,z};
}
typedef struct{
    double x, y, r;
}circle;
circle newcircle(double x, double y, double r){
    return(circle){x,y,r};
}

circle calc_circle(vecpt R){
    if(R.sz == 0)
        return newcircle(0, 0, -1);
    else if(R.sz == 1)
        return newcircle(R.ptr[0].x, R.ptr[1].y, 0);
    else if(R.sz == 2)
        return newcircle((R.ptr[0].x+R.ptr[1].x)/2.0, (R.ptr[0].y+R.ptr[1].y)/2.0, hypot(R.ptr[0].x-R.ptr[1].x, R.ptr[0].y-R.ptr[1].y)/2.0);
    else{
        double d = 2.0 * ((R.ptr[0].y - R.ptr[2].y) * (R.ptr[0].x - R.ptr[1].x) - (R.ptr[0].y - R.ptr[1].y) * (R.ptr[0].x - R.ptr[2].x));
        double x = ((R.ptr[0].y - R.ptr[2].y) * (R.ptr[0].y*R.ptr[0].y - R.ptr[1].y*R.ptr[1].y  + R.ptr[0].x*R.ptr[0].x - R.ptr[1].x*R.ptr[1].x)
                   - (R.ptr[0].y - R.ptr[1].y) * (R.ptr[0].y*R.ptr[0].y - R.ptr[2].y*R.ptr[2].y + R.ptr[0].x*R.ptr[0].x - R.ptr[2].x*R.ptr[2].x)) / d;
        double y = ((R.ptr[0].x - R.ptr[2].x) * (R.ptr[0].x*R.ptr[0].x - R.ptr[1].x*R.ptr[1].x + R.ptr[0].y*R.ptr[0].y - R.ptr[1].y*R.ptr[1].y)
                   - (R.ptr[0].x - R.ptr[1].x) * (R.ptr[0].x*R.ptr[0].x - R.ptr[2].x*R.ptr[2].x + R.ptr[0].y*R.ptr[0].y - R.ptr[2].y*R.ptr[2].y)) / -d;
        return newcircle(x, y, hypot(R.ptr[0].x - x, R.ptr[0].y - y));
    }
}
circle _welzl(vecpt*P, int i, vecpt R){
    if(i == P->sz || R.sz >= 3)
        return calc_circle(R);
    circle C = _welzl(P, i+1, R);
    if(hypot(P->ptr[i].x - C.x, P->ptr[i].y-C.y) > C.r){
        pb(R, P->ptr[i]);
        C = _welzl(P, i+1, R);
    }
    return C;
}
circle welzl(vecpt P){
//  random_shuffle(P.begin(), P.end());
    return _welzl(&P, 0, newVecPt());
}
int main(){
    int n;
    scanf("%d", &n);
    p3 P[n];
    for(int i=0; i<n; ++i)
        scanf("%lf %lf %lf", &P[i].x, &P[i].y, &P[i].z);
    vecpt PP1; PP1.sz = n; PP1.ptr = calloc(n, sizeof(pt));
    for(int i=0; i<n; ++i){
        PP1.ptr[i].x = P[i].x;
        PP1.ptr[i].y = P[i].y;
    }
    circle c = welzl(PP1);
    double d1 = c.r*2.;

    vecpt PP2; PP2.sz = n; PP2.ptr = calloc(n, sizeof(pt));
    for(int i=0; i<n; ++i){
        PP2.ptr[i].x = P[i].x;
        PP2.ptr[i].y = P[i].z;
    }
    circle c2 = welzl(PP2);
    double d2 = c2.r*2.;

    vecpt PP3; PP3.sz = n; PP3.ptr = calloc(n, sizeof(pt));
    for(int i=0; i<n; ++i){
        PP3.ptr[i].x = P[i].y;
        PP3.ptr[i].y = P[i].z;
    }
    circle c3 = welzl(PP3);
    double d3 = c3.r*2.;

    printf("%.10lf\n", min3(d1, d2, d3));

    return 0;
}
