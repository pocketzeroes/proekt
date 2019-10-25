#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  double first;
  int    second;
}pdi;
pdi newpdi(double a, int b){
  return(pdi){a, b};
}
int cmpPdi(const void*pa, const void*pb){
  pdi*a=(pdi*)pa;
  pdi*b=(pdi*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
#define pb(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pdi*pushbackP(pdi*array, int *size, pdi value){
  pdi*output = resizeArray(array, pdi, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pdi*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
////////////////////
typedef long long ll;
double eps = 1e-8;

typedef struct pt{
    double x, y;
}pt;
pt newpt(double x, double y){
    return(pt){x,y};
}

int dcmp(double x){
    if(fabs(x) < eps)
        return 0;
    else
        return x < 0 ? -1 : 1;
}
pt opAdd(pt A, pt B){
    return newpt(A.x + B.x, A.y + B.y);
}
pt opSub(pt A, pt B){
    return newpt(A.x - B.x, A.y - B.y);
}
pt opMul(pt A, double p){
    return newpt(A.x * p, A.y * p);
}
pt opDiv(pt A, double p){
    return newpt(A.x / p, A.y / p);
}

double Dot(pt A, pt B){
    return A.x * B.x + A.y * B.y;
}
double Length(pt A){
    return sqrt(Dot(A, A));
}
double Angle(pt A, pt B){
    return acos(Dot(A, B) / Length(A) / Length(B));
}
double Cross(pt A, pt B){
    return A.x * B.y - A.y * B.x;
}
double Area2(pt A, pt B, pt C){
    return Cross(opSub(B, A), opSub(C, A));
}
////////////////////////////----------------------------------------------------
int n, m;
pt* poly [110];
int sizes[110];


double PolygonArea(pt*p, int psz){
    int n = psz;
    double area = 0;
    for(int i=1; i<n-1; i++)
        area += Cross(opSub(p[i], p[0]), opSub(p[i+1], p[0]));
    return fabs(area/2.);
}
double Seg(pt O, pt A, pt B){
    if(dcmp(B.x - A.x) == 0)
        return (O.y - A.y) / (B.y - A.y);
    return (O.x - A.x) / (B.x - A.x);
}
double MultiPolyArea(int n){
    double res = 0.;
    vecp s = newVecP();
    for(int i=0; i<n; i++){
        int sz = sizes[i];
        for(int j=0; j<sz; j++){
            s.sz=0;
            pb(s, newpdi(0, 0));
            pb(s, newpdi(1, 0));
            pt a = poly[i][j], 
               b = poly[i][(j+1)%sz];
            for(int k = 0; k < n; k++){
                if(i != k){
                    int sz2 = sizes[k];
                    for(int z = 0; z < sz2; z++){
                        pt c = poly[k][z], 
                           d = poly[k][(z+1)%sz2];
                        int c1 = dcmp(Cross(opSub(b, a), opSub(c, a)));
                        int c2 = dcmp(Cross(opSub(b, a), opSub(d, a)));
                        if(c1 == 0 && c2 == 0){
                            if(dcmp(Cross(opSub(b, a), opSub(d, c)))){
                                pb(s, newpdi(Seg(c, a, b), 1));
                                pb(s, newpdi(Seg(c, a, b), -1));
                            }
                        }
                        else{
                            double s1 = Cross(opSub(d, c), opSub(a, c)),
                                   s2 = Cross(opSub(d, c), opSub(b, c));
                            if(c1 >= 0 && c2 < 0)
                                pb(s, newpdi(s1/(s1-s2), 1));
                            else if(c1 < 0 && c2 >= 0)
                                pb(s, newpdi(s1/(s1-s2), -1));
                        }
                    }
                }
            }
            qsort(s.ptr, s.sz, sizeof(pdi), cmpPdi);
            double pre = fmin(fmax(s.ptr[0].first, 0.0), 1.0), now, sum=0;
            int cov = s.ptr[0].second;
            for(int j = 1; j < s.sz; j++){
                now = fmin(fmax(s.ptr[j].first, 0.0), 1.0);
                if(!cov)
                    sum += now - pre;
                cov += s.ptr[j].second;
                pre = now;
            }
            res += Cross(a, b) * sum;
        }
    }
    return fabs(res / 2);
}
int main(){
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%d", &m);
        poly [i] = calloc(m, sizeof(pt));
        sizes[i] = m;
        for(int j=0; j<m; j++)
            scanf("%lf %lf", &poly[i][j].x, &poly[i][j].y);
    }
    double ans1 = 0,
           ans2 = MultiPolyArea(n);
    for(int i=0; i<n; i++)
        ans1 += PolygonArea(poly[i], sizes[i]);
    printf("%.12f %.12f\n", ans1, ans2);
    return 0;
}
