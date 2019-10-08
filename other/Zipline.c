#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>


double pow2(double x){
    return pow(x, 2.0);
}
double f(double x, double w, double g, double h){
    return sqrt(pow2(g) + pow2(x)) + sqrt(pow2(h) + pow2(w - x));
}
double df(double x, double w, double g, double h){
    return (x / sqrt(pow2(g) + pow2(x))) + ((x - w) / sqrt(pow2(h) + pow2(w - x)));
}
double binsrch(double w, double g, double h){
    double left = 0;
    double right = w;
    double x, dfx;
    int i = 0;
    while(fabs(left - right) > pow(10.0, -6) / 1.10){
        i++;
        if(i > 1000) 
            break;
        x = (left + right) / 2;
        dfx = df(x, w, g, h);
        if(dfx == 0.0)
            break;
        else if(dfx < 0.0)
            left = x;
        else
            right = x;
    }
    return f(x, w, g, h);
}
double getmin(double w, double g, double h){
    double x = fabs(g - h);
    return sqrt(pow2(x) + pow2(w));
}
int main(){
    int n, w, g, h, r;
    scanf("%d", &n);
    double l[n];
    double L[n];
    for(int i=0; i<n; i++){
        scanf("%d%d%d%d", &w, &g, &h, &r);
        l[i] = getmin((double) w, (double) g, (double) h);
        g = g - r;
        h = h - r;
        L[i] = binsrch((double) w, (double) g, (double) h);
    }
    for(int i=0; i<n; i++)
        printf("%.8lf %.8lf\n", l[i], L[i]);
    return 0;
}
