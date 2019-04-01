#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
double min(double a, double b){return a<b?a:b;}

double search(double x, double y, double lo, double hi){
    if(hi - lo < 10e-7)
        return lo;
    double p = lo + (hi-lo)/3.  ;
    double a = p*(x-p*2.)*(y-p*2.);
    double q = lo + (hi-lo)*2./3.;
    double b = q*(x-q*2.)*(y-q*2.);
    if(a > b)
        return search(x, y, lo, q);
    else
        return search(x, y, p, hi);
}
signed main(){
    signed n;
    scanf("%d", &n);
    double x, y;
    double a;
    for(int i=0; i<n; i++){
        scanf("%lf %lf", &x, &y);
        a = search(x, y, 0., min(x,y)/2.);
        printf("%lf\n", a*(x-2.*a)*(y-2.*a));
    }
    return 0;
}
