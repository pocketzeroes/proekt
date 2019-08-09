#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int n;
double a[10], b[10], c[10], mu[10], x[10], t;

bool ok(double xx){
    double tt = 0;
    for (int i = 0; i < n; ++i){
        x[i] = fmax(0.0, (xx-b[i])/(2*a[i]));
        tt += x[i];
    }
    return tt <= t;
}
int main(){
    scanf("%d %lf", &n, &t);
    for(int i = 0; i < n; ++i)
        scanf("%lf%lf%lf", &a[i], &b[i], &c[i]);
    double lo = -1000, 
           hi =  1000;
    while(!ok(hi)) hi *= 2;
    while (ok(lo)) lo *= 2; 
    while (lo + 1e-12 < hi) {
        double mid = (lo+hi)*0.5;
        if (!ok(mid)) lo = mid;
        else hi = mid;
    }
    double val = 0;
    for (int i = 0; i < n; ++i)
        val += a[i]*x[i]*x[i] + b[i]*x[i] + c[i];
    printf("%.10lf\n", val/(double)n);
    return 0;
}
