#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ typeof(a) tmp; tmp = a; a = b; b = tmp; }while(0)

double**newmat(int x, int y){
  double**rv = calloc(x, sizeof(double*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(double));
  return rv;
}

const double eps = 1e-7;

bool zero(double a){
    return (a<eps) && (a>-eps);
}
double*solve(double**a, int m, int n){
    int cur=0;
    for (int i=0;i<n;++i){
        for (int j=cur;j<m;++j)
            if (!zero(a[j][i])){
                if (j!=cur)
                    swap(a[j], a[cur]);
                for (int sat=0;sat<m;++sat){
                    if (sat==cur)
                        continue;
                    double num=a[sat][i]/a[cur][i];
                    for (int sot=0;sot<=n;++sot)
                        a[sat][sot]-=a[cur][sot]*num;
                }
                cur++;
                break;
            }
    }
    for (int j=cur;j<m;++j)
        if (!zero(a[j][n]))
            return NULL;
    double*ans = calloc(n, sizeof(double));
    for (int i=0,sat=0;i<n;++i){
        ans[i] = 0;
        if (sat<m && !zero(a[sat][i])){
            ans[i] = a[sat][n] / a[sat][i];
            sat++;
        }
    }
    return ans;
}
int main(){
    int tn;
    for(scanf("%d", &tn); tn--;){
        int n;
        scanf("%d", &n);
        double f[n];
        for(int i = 0; i < n; i++)
            scanf("%lf", &f[i]);
        double next = -1;
        bool found = false;
        for(int d = 1; d <= 3 && !found; d++){
            double**c = newmat(n-d, d+1);//of double
            for(int i = d; i < n; i++)
                for(int j = 0; j <= d; j++)
                    c[i - d][d - j] = f[i - j];
            double*a = solve(c, n-d, d);
            if(a){
                next = 0;
                for (int i = 0; i < d; i++)
                    next += a[i] * f[n - d + i];
                found = true;
            }
        }
        printf("%d\n", (int)round(next));
    }
    return 0;
}
