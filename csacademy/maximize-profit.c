#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

double max(double a, double b){return a>b?a:b;}
typedef long long ll;

int cmp(const void*pa, const void*pb){
    ll*a =(ll*)pa;
    ll*b =(ll*)pb;
    return(*a < *b)?-1:1;
}

int main(){
    ll q, k;
    double s;
    scanf("%lf %lld %lld", &s, &q, &k);
    ll v[q];
    for(int i=0; i<q; i++)
        scanf("%lld", &v[i]);
    qsort(v, q, sizeof(ll), cmp);
    for(int i = 0; i < q; i++){
        double x = s+k;
        double y = ((100+v[i])*s)/100.0;
        s = max(x, y);
    }
    printf("%lf\n", s);
    return 0;
}
