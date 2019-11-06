#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAX_N = 10};
enum{ MAX_L = 99};
#define EPS 0.0001
typedef struct{
    double x,y;
}pt;
pt newpt(double a, double b){
    return(pt){a,b};
}

typedef struct{
    int len;
    pt a, b;
}Seg;

Seg newSeg(int len, pt a, pt b){
    return(Seg){len,a,b};
}

#define pbs(zpv, zvv) zpv.ptr = pushbackS(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Seg*pushbackS(Seg*array, int *size, Seg value){
  Seg*output = resizeArray(array, Seg, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	Seg*ptr;
	int sz;
}vecs;
vecs newVecS(){
	vecs rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


typedef struct{
    double span, minx;
}Outcome;
vecs tower;     // of Seg
int n;
int length[MAX_N];
bool avail[MAX_N];
Outcome best;
void extend();


double computeTolerance(){
    double small = MAX_L * MAX_N;
    for(int j=2; j<tower.sz; j++)
        small = fmin(small, tower.ptr[j].b.x);
    return small;
}
void trySolution(){
    int t = tower.sz;
    pt*p = &tower.ptr[t-1].b;
    if(p->x > best.span)
        best = (Outcome){p->x, computeTolerance()};
    if(p->x > -EPS)
        extend();
}
void tryGeometry(bool orient){
    int t = tower.sz;
    Seg*base = &tower.ptr[t-3];
    int first  = (orient ? t-2 : t-1);
    int second = (orient ? t-1 : t-2);
    tower.ptr[first].a  = base->a;
    tower.ptr[second].a = base->b;
    double d = base->len;
    double R = tower.ptr[first ].len;
    double r = tower.ptr[second].len;
    double major = (d*d - r*r + R*R)/(2*d);
    double minor = 0.5*sqrt((-d+r-R)*(-d-r+R)*(-d+r+R)*(d+r+R))/d;
    double dx = base->b.x - base->a.x;
    double dy = base->b.y - base->a.y;
    pt p = newpt(base->a.x + dx*major/base->len, base->a.y + dy*major/base->len);
    pt q = newpt(dy*minor/base->len, -dx*minor/base->len);
    pt u = newpt(p.x+q.x, p.y+q.y);
    tower.ptr[first].b = tower.ptr[second].b = u;
    trySolution();
    pt v=newpt(p.x-q.x, p.y-q.y);
    tower.ptr[first].b = tower.ptr[second].b = v;
    trySolution();
}
void extend(){
    for(int j=0; j<n; j++){
        if(avail[j]){
            avail[j] = false;
            pbs(tower, newSeg(length[j], newpt(0,0), newpt(0,0)));
            int t = tower.sz;
            if(t % 2 == 0)
                extend();
            else{
                Seg a = tower.ptr[t-1];
                Seg b = tower.ptr[t-2]; 
                Seg c = tower.ptr[t-3];
                int m = fmax(a.len, fmax(b.len, c.len));
                if(a.len+b.len+c.len > 2*m){
                    tryGeometry(true);
                    if(t > 3)
                        tryGeometry(false);
                }
            }
            tower.sz--;
            avail[j] = true;
        }
    }
}
int main(){
    scanf("%d", &n);
    for(int j=0; j<n; j++){
        scanf("%d", &length[j]);
        avail[j] = true;
    }
    for(int j=0; j<n; j++){
        avail[j] = false;
        pbs(tower, newSeg(length[j], newpt(0,0), newpt(0, (double)(length[j]))));
        extend();
        tower.sz--;
        avail[j] = true;
    }
    if(best.minx <= EPS)
       best.span = -best.span;
    printf("%lf\n", best.span);
    return 0;
}
