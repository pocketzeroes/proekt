#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<complex.h>
#include<float.h>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define newpt(x, y) __builtin_complex((double)(x), (double)(y))
typedef double complex pt;


double INF = DBL_MAX;
double EPS = 1E-9;
int N;

double**newmat(double x, double y){
  double**rv =(double**)calloc(x, sizeof(double*));
  for(int i=0;i<x;i++)
    rv[i] =(double*)calloc(y, sizeof(double));
  return rv;
}
#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)


























inline pt mirror(pt p, pt p1, pt p2){
    if(cabs(p - p1) < EPS || cabs(p - p2) < EPS)
        return p;
    double theta = carg((p2 - p1) / (p - p1));
    return p1 + (p - p1) * newpt(cos(2 * theta), sin(2 * theta));
}
inline double dot(pt p, pt q){
    return creal(conj(p) * q);
}
inline double cross(pt p, pt q){
    return cimag(conj(p)*q);
}
bool isCrossed(pt As, pt Ae, pt Bs, pt Be){
    pt A = Ae - As,
       B = Be - Bs,
       S = Bs - As;
    double f = cross(A, B);
    if (fabs(f) < EPS){
        Bs = (Bs - As) / A;
        Be = (Be - As) / A;
        if(fabs(cimag(Bs)) > EPS)
            return false;
        if(creal(Bs) < -EPS && creal(Be) < -EPS)
            return false;
        if(1 + EPS < creal(Bs) && 1 + EPS < creal(Be))
            return false;
        return true;
    }
    double p = cross(S, B) / f;
    double q = cross(S, A) / f;
    if(p < -EPS || 1 + EPS < p)
        return false;
    if(q < -EPS || 1 + EPS < q)
        return false;
    return true;
}
double pointLineDistance(pt p, pt p1, pt p2){
    p  = p  - p1;
    p2 = p2 - p1;
    pt pe = p2 / cabs(p2);
    p /= pe;
    p2 /= pe;
    if(creal(p2) < 0){
        p2 = newpt(creal(-p2), cimag(p2));
        p  = newpt(creal(-p ), cimag(p ));
    }
    if(creal(p) < 0)
        return cabs(p);
    else if (0 <= creal(p) && creal(p) <= creal(p2))
        return fabs(cimag(p));
    else
        return cabs(p - p2);
}
double calcDist(int start, int goal, pt*ps){
    assert(goal - start >= 2);
    int qssz = goal-start+1; int z=0;
    pt*qs = (pt*)calloc(qssz, sizeof(pt));
    for(int i=start; i<=goal; ++i)
        qs[z++] = ps[i];
    for(int i=1; i+1<qssz; ++i){
        for(int k=i+2; k<qssz; ++k)
            qs[k] = mirror(qs[k], qs[i], qs[i + 1]);
    }
    double r = cabs(qs[qssz-1] - qs[0]);
    for(int i=1; i+2<qssz; ++i){
        if(!isCrossed(qs[0], qs[qssz-1], qs[i], qs[i+1]))
            return INF;
    }
    return r;
}
double f(int start, int goal, pt*ps, double**dist){
    if(dist[start][goal] >= 0)
        return dist[start][goal];
    if(goal - start <= 2)
        return dist[start][goal] = cabs(ps[goal] - ps[start]);
    double result = calcDist(start, goal, ps);
    for(int k = start + 1; k < goal; ++k)
        result = min(result, f(start, k, ps, dist) + f(k, goal, ps, dist));
    return dist[start][goal] = result;
}
double solve(pt*pp, double px, double py){
    int idx = -1;
    double d = INF;
    for(int i=0; i<N; ++i){
        double dd = pointLineDistance(newpt(px, py), pp[i], pp[i+1]);
        if(dd < d){
            idx = i;
            d   = dd;
        }
    }
    double result = INF;
    for(int k=-1; k<=1; ++k){
        int ps_sz=N+3; int z=0;
        pt*ps =(pt*)calloc(ps_sz, sizeof(pt));
        ps[z++] = newpt(px, py);
        for(int i=0; i<N; ++i)
            ps[z++] = pp[(i+idx+k+N)%N];
        ps[z++] = pp[(k+idx+N)%N];
        ps[z++] = newpt(px, py);
        double**dist = newmat(ps_sz, ps_sz); dfill(dist, ps_sz, ps_sz, -1.);
        double r = f(0, ps_sz-1, ps, dist);
        result = min(result, r);
    }
    return result;
}
int main(){
    int caseNo = 0;
    for(int px, py; scanf("%d %d %d", &N, &px, &py)==3;){
        pt ps[N];
        for(int i = 0; i < N; ++i){
            int x, y;
            scanf("%d %d", &x, &y);
            ps[i] = newpt(x, y);
        }
        double r = solve(ps, px, py);
        printf("Case %d: %.2f\n", ++caseNo, r);
    }
    return 0;
}
