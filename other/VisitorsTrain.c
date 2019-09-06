#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define pb(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
#define pbd(zpv, zvv) zpv.ptr = pushbackD(zpv.ptr, &zpv.sz, zvv)
typedef struct{
    int x, y;
}pt;
pt newpt(int x, int y){
    return(pt){x,y};
}
pt opSub(pt t, pt v){
    return newpt(t.x-v.x, t.y-v.y);
}
double size(pt p){
    return sqrt((double)p.x*p.x + (double)p.y*p.y);
}

inline int cross(pt v1, pt v2){
    return v1.x*v2.y - v1.y*v2.x;
}
inline int direction(pt v1, pt v2, pt point){
    return cross(opSub(v2,v1), opSub(point,v1));
}
enum{MAXN = 100};
int N;
pt track[2], rects[MAXN][4];
typedef struct{
  double first;
  double second;
}pair;
pair newpair(double a, double b){
  return(pair){a,b};
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
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
vecp intervals;
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

//////////////////////////////////
bool intersection(pt A, pt B, pt C, pt D, double*t1, double*t2){
    double det = (D.y-C.y) * (B.x-A.x) - (B.y-A.y) * (D.x-C.x);
    if (!det)
        return false;
   *t1 = ((D.y-C.y) * (C.x-A.x) + (D.x-C.x) * (A.y-C.y)) / det;
   *t2 = ((B.y-A.y) * (C.x-A.x) + (B.x-A.x) * (A.y-C.y)) / det;
    return true;
}
bool is_base_completely_visible(pt point, pt base[4], pt rect[4]){
    pt D1 = rect[0], D2 = rect[0];
    for (int i = 0; i < 4; ++i) {
        if (direction(point, D1, rect[i]) < 0)
            D1 = rect[i];
        if (direction(point, D2, rect[i]) > 0)
            D2 = rect[i];
    }
    for (int i = 0; i < 4; ++i)
        if (direction(point, D1, base[i]) > 0 && direction(point, D2, base[i]) < 0 && direction(D1, D2, base[i]) < 0)
            return false;
    for (int i = 0; i < 4; ++i) {
        double t1, t2, s1, s2;
        if (intersection(point, D1, base[i], base[(i+1)%4], &t1, &t2) &&
            intersection(point, D2, base[i], base[(i+1)%4], &s1, &s2) &&
            t1 >= 1 && s1 >= 1 && 0 <= t2 && t2 <= 1 && 0 <= s2 && s2 <= 1)
            return false;
    }
    return true;
}
bool is_whole_track_blocked(){
    for (int i = 1; i < N; ++i)
        if (!is_base_completely_visible(track[0], rects[0], rects[i]) &&
            !is_base_completely_visible(track[1], rects[0], rects[i]))
            return true;
    return false;
}
bool is_track_completely_visible(pt point, pt track[2], pt rect[4]){
    pt D1 = rect[0], D2 = rect[0];
    for (int i = 0; i < 4; ++i) {
        if (direction(point, D1, rect[i]) < 0)
            D1 = rect[i];
        if (direction(point, D2, rect[i]) > 0)
            D2 = rect[i];
    }
    for (int i = 0; i < 2; ++i)
        if (direction(point, D1, track[i]) > 0 && direction(point, D2, track[i]) < 0 && direction(D1, D2, track[i]) < 0)
            return false;
    double t1, t2, s1, s2;
    if (intersection(point, D1, track[0], track[1], &t1, &t2) &&
        intersection(point, D2, track[0], track[1], &s1, &s2) &&
        t1 >= 1 && s1 >= 1)
        return false;
    return true;
}
void create_interval(pt base[4], pt rect[4]){
    vecd intersections=newVecD();
    for(int i = 0; i < 4; ++i){
        if(is_track_completely_visible(base[i], track, rect))
            continue;
        for(int j = 0; j < 4; ++j){
            double t1, t2;
            if (intersection(track[0], track[1], base[i], rect[j], &t1, &t2) && t2 >= 1.0)
                pbd(intersections, t1);
        }
    }
    qsort(intersections.ptr, intersections.sz, sizeof(double), cmpDbl);
    if(intersections.sz && intersections.ptr[0] <= 1.0 && intersections.ptr[intersections.sz-1] >= 0.0)
        pb(intervals, newpair(intersections.ptr[0], intersections.ptr[intersections.sz-1]));
}
int main(){
    int tc;
    scanf("%d", &tc);
    for(int z=0; z<tc; z++){
        scanf("%d", &N);
        if(!N)
            break;
        for(int i = 0; i < 2; ++i)
            scanf("%d%d", &track[i].x, &track[i].y);
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < 4; ++j)
                scanf("%d%d", &rects[i][j].x, &rects[i][j].y);
        if(is_whole_track_blocked()){
            printf("0.00\n");
            continue;
        }
        intervals.sz=0;
        for (int i = 1; i < N; ++i)
            create_interval(rects[0], rects[i]);
        qsort(intervals.ptr, intervals.sz, sizeof(pair), cmpP);
        double length = 0.0, last = 0.0;
        for (int i = 0; i < intervals.sz; ++i){
            if(intervals.ptr[i].first > 1.0)
                break;
            length += fmax(intervals.ptr[i].first - last, 0.0);
            last = fmax(last, intervals.ptr[i].second);
        }
        length += fmax(1.0 - last, 0.0);
        printf("%lf\n", length * size(opSub(track[1], track[0])));
    }
    return 0;
}

