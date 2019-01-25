#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
double min(double a, double b){return a<b?a:b;}
double max(double a, double b){return a>b?a:b;}



typedef struct{
    double x, y;
}point;

point newpoint(double x, double y){
    point rez;
    rez.x = x;
    rez.y = y;
    return rez;
}
double cross(point a, point b){
    return b.y*a.x - b.x*a.y;
}
void rotate(point*array, int n, int size){
    point*tmp_array = calloc(n, sizeof(point));
    memcpy(tmp_array, array, n*sizeof(point));
    memmove(array, array + n, (size - n)*sizeof(point));
    memmove(array + size - n, tmp_array, n*sizeof(point));
    free(tmp_array);
}


int N;
point  P   [200000];
double Psum[200000];

point interp(point A, point B, double x){
    return newpoint(x, A.y + (B.y-A.y)*(x-A.x)/(B.x-A.x));
}
double split_area(double x){
    int begin = N-1, end = 0;
    while (P[begin].x < x)
        --begin;
    while (P[end].x < x)
        ++end;
    point I1 = interp(P[end-1], P[end], x), 
          I2 = interp(P[begin], P[begin+1], x);
    double A = cross(P[end-1], I1) + cross(I1, I2) + cross(I2, P[begin+1]) + Psum[N] - Psum[begin+1] + Psum[end-1];
    return A;
}
double find_split(double A, double lo, double hi){
    while (hi-lo > 1e-6){
        double m = (lo+hi)/2;
        if(split_area(m) > A)
            hi = m;
        else
            lo = m;
    }
    return lo;
}
int main(){
    double C, x_lo = 1e30, x_hi = -1e30;
    scanf("%lf %d", &C, &N);
    for (int i = 0; i < N; ++i){
        scanf("%lf %lf", &P[i].x, &P[i].y);
        x_lo = min(x_lo, P[i].x);
        x_hi = max(x_hi, P[i].x);
    }
    for(int i=0; i<N; ++i){
        if(P[i].x == x_lo){
            rotate(P, i, N);
            break;
        }
    }
    P[N] = P[0];
    Psum[0] = 0;
    for(int i=0; i<N; ++i)
        Psum[i+1] = Psum[i] + cross(P[i], P[i+1]);
    double A = split_area(x_hi);
    int M = floor(A/C/2);
    printf("%d\n", M);
    for(int i=1; i<M; ++i)
        printf("%.9lf\n", find_split(A*i/M, x_lo, x_hi));
    return 0;
}
