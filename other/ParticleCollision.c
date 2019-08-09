#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<complex.h>
#define swap(a,b) do{ typeof(a) tmp; tmp = a; a = b; b = tmp; }while(0)
#define newpt __builtin_complex
#define EPS 1e-8

typedef complex double pt;

double norm(pt p){
  double cr = creal(p);
  double ci = cimag(p);
  return cr*cr + ci*ci;
}
pt read(){
    double x, y;
    scanf("%lf %lf", &x, &y);
    return newpt(x, y);
}
double hit(pt a, pt b, pt dir, double r) {
    double A = norm(dir),
           B = -2*creal(dir*conj(b-a)),
           C = norm(b-a) - 4*r*r;
    if (fabs(A) < EPS)
        return -1;
    double disc = B*B - 4*A*C;
    if (disc < -EPS)
        return -1;
    double t = (-B-sqrt(fabs(disc)))/(2*A);
    if (t < -EPS)
        return -1;
    return t;
}
int main() {
    pt p[3], dir;
    double r;
    for(int i=0;i<3;i++){
        p[i] = read();
    }
    dir = read();
    scanf("%lf", &r);
    int adj = 0;
    double t1 = hit(p[0], p[1], dir, r),
           t2 = hit(p[0], p[2], dir, r);
    if(t2 > -0.5 && (t1 < -0.5 || t2 < t1)){
        ++adj;
        swap(p[1], p[2]);
        swap(t1, t2);
    }
    pt dd = p[1] - (p[0] + t1*dir);
    if(t1 < -0.5)
        puts("5");
    else if(hit(p[1], p[2], p[1]-(p[0]+t1*dir), r) < -0.5)
        printf("%d\n", 3+adj);
    else
        printf("%d\n", 1+adj);
    return 0;
}
