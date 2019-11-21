#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long double ld;
#define sqr(x) ((x) * (x))
int x[4];
int y[4];
int z[4];
int a[3];
int b[3];
int c[3];
int d[3];
ld xx, yy, zz;

void equation2(ld a1, ld b1, ld c1, ld a2, ld b2, ld c2){
    xx = (c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1);
    yy = (c1 * a2 - c2 * a1) / (b1 * a2 - b2 * a1);
}
void equation3(ld a1, ld b1, ld c1, ld d1, ld a2, ld b2, ld c2, ld d2, ld a3, ld b3, ld c3, ld d3){
    equation2(a1 * c2 - a2 * c1, b1 * c2 - b2 * c1, d1 * c2 - d2 * c1, a1 * c3 - a3 * c1, b1 * c3 - b3 * c1, d1 * c3 - d3 * c1);
    zz = (d1 - a1 * xx - b1 * yy) / c1;
}
void abcd(int x1, int y1, int z1, int x2, int y2, int z2, int*a, int*b, int*c, int*d){
   *a = 2 * (x2 - x1);
   *b = 2 * (y2 - y1);
   *c = 2 * (z2 - z1);
   *d = sqr(x2) + sqr(y2) + sqr(z2) - sqr(x1) - sqr(y1) - sqr(z1);
}
int main(){
    for(int i=0; i<4; ++i)
        scanf("%d %d %d", &x[i], &y[i], &z[i]);
    for(int i=0; i<3; ++i)
        abcd(x[3], y[3], z[3], x[i], y[i], z[i], &a[i], &b[i], &c[i], &d[i]);
    equation3(a[0], b[0], c[0], d[0], a[1], b[1], c[1], d[1], a[2], b[2], c[2], d[2]);
    if(isnan(xx) || isnan(yy) || isnan(zz))
        equation3(a[0] + 1e-6, b[0] + 1e-6, c[0] + 1e-6, d[0], a[1] - 1e-6, b[1] + 1e-6, c[1] - 1e-6, d[1], a[2] + 1e-6, b[2] - 1e-6, c[2] + 1e-6, d[2]);
    printf("%.8Lf %.8Lf %.8Lf\n", xx, yy, zz);
    return 0;
}
