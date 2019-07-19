#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ N = 105};
int n , ca;
double a[N] , p[N] , q[N];
double L , R , D;

double F(double x){
    double res = 0;
    for (int i = n + n + 1 ; i >= 0 ; -- i){
        res *= x;
        res += q[i];
    }
    return res;
}
void work(){
    int i , j , k;
    for (i = 0 ; i <= n ; ++ i){
        scanf("%lf" , &a[i]);
    }
    memset(p , 0 , sizeof(p));
    for (i = 0 ; i <= n ; ++ i)
        for (j = 0 ; j <= n ; ++ j)
            p[i + j] += a[i] * a[j];
    memset(q , 0 , sizeof(q));
    for (i = 1 ; i <= n + n + 1 ; ++ i) {
        q[i] = p[i - 1] / i;
    }
    scanf("%lf%lf%lf" , &L , &R , &D);
    double val = M_PI * (F(R) - F(L));
    printf("Case %d: %.2f\n" , ++ ca , val);
    if (val < D) {
        puts("insufficient volume");
        return;
    }
    D /= M_PI;
    double x = L;
    bool flag = 0 , e = 0;
    for (i = 0 ; i < 8 ; ++ i) {
        double w = F(x);
        double l , r , m;
        l = x , r = R;
        while (r - l > 1e-8) {
            m = (l + r) * 0.5;
            if (F(m) > w + D)
                r = m;
            else
                l = m;
        }
        if (F(r) > w + D) {
            if (flag)
                putchar(' ');
            flag = 1;
            printf("%.2f" , r - L);
            x = r;
        }
        else {
            printf("\n");
            e = 1;
            break;
        }
    }
    if (!e)
        putchar('\n');
}
int main(){
    while(~scanf("%d" , &n))
        work();
    return 0;
}
