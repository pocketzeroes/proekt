#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long double ld;

typedef struct{
    ld x, y, z;
}pt;
pt newpt(ld a, ld b, ld c){
    pt rez;
    rez.x=a;
    rez.y=b;
    rez.z=c;
    return rez;
}
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
ld*pushbackLD(ld*array, int*size, ld value){
  ld*output = resizeArray(array, ld, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  ld*ptr;
  int sz;
}vecld;
vecld newVecLD(){
  vecld rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

pt opAdd(pt a, pt b){
    return newpt(a.x+b.x, a.y+b.y, a.z+b.z);
}
pt opSub(pt a, pt b){
    return newpt(a.x-b.x, a.y-b.y, a.z-b.z);
}
pt opDiv(pt a, ld v){
    return newpt(a.x/v, a.y/v, a.z/v);
}
pt opMult(pt a, ld v){
    return newpt(v*a.x, v*a.y, v*a.z);
}
ld opMul(pt a, pt other){
    return a.x*other.x + a.y*other.y + a.z*other.z;
}
pt opPow(pt a, pt other){
    return newpt(a.y*other.z-a.z*other.y,-a.x*other.z+a.z*other.x,a.x*other.y-a.y*other.x);
}
ld norm(pt a){
    return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

ld get_area(vecpt points){
    pt normal =opPow(opSub(points.ptr[1], points.ptr[0]), opSub(points.ptr[2], points.ptr[0]));
    normal = opDiv(normal, norm(normal));
    pt crozz =(pt){0, 0, 0};
    for(int i = 0; i < points.sz - 1; ++i)
        crozz = opAdd(crozz, opPow(points.ptr[i], points.ptr[i + 1]));
    crozz = opAdd(crozz, opPow(points.ptr[points.sz-1], points.ptr[0]));
    return opMul(normal, crozz) / 2.0;
}
pt get_normal(vecpt points){
    pt nrm = opPow( opSub(points.ptr[1], points.ptr[0]), opSub(points.ptr[2], points.ptr[0]));
    ld mag = norm(nrm);
    return opDiv(nrm, mag);
}
ld get_dist(pt nrm,  pt query){
    pt proj = opMult(nrm, opMul(nrm, query));
    return norm(proj);
}
ld volume() {
    int f;
    scanf("%d", &f);
    ld vol = 0.0L;
    int v;
    ld x, y, z;
    ld cx = 0.0L, 
       cy = 0.0L, 
       cz = 0.0L;
    int total_vert = 0;
    vecld areas  = newVecLD();
    vecpt normals= newVecPt();
    vecpt anchor = newVecPt();
    for(int i=0; i<f; ++i){
        scanf("%d", &v);
        total_vert += v;
        vecpt points = newVecPt();
        for(int j = 0; j < v; ++j){
            scanf("%Lf %Lf %Lf", &x, &y, &z);
            points.ptr = pushbackPt(points.ptr, &points.sz, newpt(x, y, z));
            cx += x;
            cy += y;
            cz += z;
        }
        areas  .ptr = pushbackLD(areas  .ptr, &areas  .sz, get_area(points));
        normals.ptr = pushbackPt(normals.ptr, &normals.sz, get_normal(points));
        anchor .ptr = pushbackPt(anchor .ptr, &anchor .sz, points.ptr[0]);
    }
    cx /= total_vert;
    cy /= total_vert;
    cz /= total_vert;
    pt center =(pt){cx, cy, cz};
    for(int i=0; i<f; ++i)
        vol += areas.ptr[i] * get_dist(normals.ptr[i], opSub(center, anchor.ptr[i])) / 3.0L;
    return vol;
}
int main(){
    int n;
    scanf("%d", &n);
    ld ans = 0.0L;
    for (int i = 0; i < n; ++i)
        ans += volume();
    printf("%.2Lf\n", ans);
    return 0;
}
