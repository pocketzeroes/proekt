#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

bool is_Mandelbrot(double x, double y, int r){
    double z_r, z_i, zr_copy;
    bool   ans;
    ans = true;
    z_r = 0.0;
    z_i = 0.0;
    while(ans && r--){
        zr_copy = z_r;
        z_r = z_r * z_r - z_i * z_i + x;
        z_i = 2.0 * zr_copy * z_i + y;
        if (z_r * z_r + z_i * z_i > 4.0)
            ans = false;
    }
    return ans;
}
int main(){
    double x, y;
    int    r, i;
    i = 0;
    while(scanf("%lf %lf %d", &x, &y, &r)==3){
        printf("Case %d: ", ++i);
        puts(is_Mandelbrot(x, y, r)?"IN":"OUT");
    }
    return 0;
}
