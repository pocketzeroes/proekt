#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
#define rep(i, a, b) for(int i = a; i < (b); ++i)

int n,m;
double*A;
double*B;
double*C;
double*Y;
double*X1;
double*X2;
double eps = 0.0000000001;

double F(double a, double b, double c, double x){
    return a*x*x*x/3.0 + b*x*x/2.0 + c*x;
}
double integrate(double y, double a, double b, double c, double x1, double x2){
    double i1 = x1;
    double i2 = x1;
    if(fabs(a) < eps){
        if(fabs(b) > eps){
            i1 = (y-c)/b;
        }
    }
    else{
        double p = b/a;
        double q = (c-y)/a;
        double D = (p*p)/4.0 - q;
        if(fabs(D) < eps){
            i1 = -p/2.0;
        }
        else{
            if(D > 0){
                i1 =  sqrt(D) - p/2.0;
                i2 = -sqrt(D) - p/2.0;
            }
        }
    }
    i1 = fmax(i1, x1);
    i2 = fmax(i2, x1);
    i1 = fmin(i1, x2);
    i2 = fmin(i2, x2);
    if(i1 > i2)
        swap(i1,i2);
    double res = 0.0;
    res += fabs(F(a,b,c-y,i1) - F(a,b,c-y,x1));
    res += fabs(F(a,b,c-y,i2) - F(a,b,c-y,i1));
    res += fabs(F(a,b,c-y,x2) - F(a,b,c-y,i2));
    return res;
}
int main(){
    scanf("%d", &n);
    X1 = calloc(n, sizeof(double));
    Y  = calloc(n, sizeof(double));
    rep(c1,0,n){
        int x, y;
        scanf("%d %d", &x, &y);
        X1[c1] = x;
        Y [c1] = y;
    }
    scanf("%d", &m);
    X2=calloc(m, sizeof(double));
    A =calloc(m, sizeof(double));
    B =calloc(m, sizeof(double));
    C =calloc(m, sizeof(double));
    rep(c1,0,m){
        int x, a, b, c;
        scanf("%d %d %d %d", &x, &a, &b, &c);
        X2[c1]=x;
        A [c1]=a;
        B [c1]=b;
        C [c1]=c;
    }
    int l = 0;
    int r = 0;
    double prev = 0.0;
    double ans  = 0.0;
    double a = A[0];
    double b = B[0];
    double c = C[0];
    double y = Y[0];
    while(l < n && r < m){
        if(X1[l] < X2[r]){
            double x = X1[l];
            ans += integrate(y,a,b,c,prev,x);
            l++;
            if(l < n)
                y = Y[l];
            prev = x;
        }
        else{
            double x = X2[r];
            ans += integrate(y,a,b,c,prev,x);
            r++;
            if(r < m){
                a = A[r];
                b = B[r];
                c = C[r];
            }
            prev = x;
        }
    }
    printf("%.18lf\n", ans);
    return 0;
}
