#include<stdio.h>
#include<assert.h>
#include<math.h>

double sqr(double x) { return x*x; }

typedef struct{
    double x, y, vx, vy, r;
}drop;

drop newdrop(double x, double y, double vx, double vy, double r){
    return(drop){x, y, vx, vy, r};
}
double hit_time(drop dr, drop D){
    double A = sqr(dr.vx - D.vx) + sqr(dr.vy - D.vy);
    double B = (dr.vx-D.vx)*(dr.x-D.x) + (dr.vy-D.vy)*(dr.y-D.y);
    double C = sqr(dr.x-D.x) + sqr(dr.y-D.y) - sqr(dr.r+D.r);
    double disc = B*B-A*C;
    if(A < 1e-15)
        return 1e30;
    if(disc < -1e-15)
        return 1e30;
    double t1 = (-B - sqrt(disc))/A, 
           t2 = (-B + sqrt(disc))/A;
    return t1 > 0 ? t1 : 1e30;
}
void move(drop*dr, double t){
    dr->x += t*dr->vx;
    dr->y += t*dr->vy;
}
void join(drop*dr, drop D){
    double a = sqr(dr->r),
           b = sqr(D.r);
    dr->x  = (a*dr->x  + b*D.x) /(a+b);
    dr->y  = (a*dr->y  + b*D.y) /(a+b);
    dr->vx = (a*dr->vx + b*D.vx)/(a+b);
    dr->vy = (a*dr->vy + b*D.vy)/(a+b);
    dr->r  = sqrt(a+b);
}
int main(){
    int N;
    drop D[200];
    scanf("%d", &N);
    for(int i = 0; i < N; ++i)
        scanf("%lf%lf%lf%lf%lf", &D[i].x, &D[i].y, &D[i].vx, &D[i].vy, &D[i].r);
    double last = 0;
    while(1){
        double t = 1e30;
        int bi = -1, bj = -1;
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < i; ++j) {
                double s = hit_time(D[i], D[j]);
                if(s < t){
                    t  = s;
                    bi = i;
                    bj = j;
                }
            }
        if (t == 1e30)
            break;
        for (int i = 0; i < N; ++i)
            move(&D[i], t);
        join(&D[bj], D[bi]);
        --N;
        last += t;
        for(int i = bi; i < N; ++i)
            D[i] = D[i+1];
    }
    printf("%d %.6lf\n", N, last);
    return 0;
}
