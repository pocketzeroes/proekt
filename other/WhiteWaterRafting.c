#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

double a[200][3],
       b[200][3], ans;
int n, m;

double sqr(double x){
    return x*x;
}
void count(double x1, double y1, double x2, double y2, double x, double y){
    double a1, b1, c1;
    if (fabs(x1-x2) < 1e-6){
        a1 = 1; b1 = 0;
        c1 = -x1;
    }
    else{
        a1 = (y2-y1)/(x2-x1);
        b1 = -1;
        c1 = y1-a1*x1;;
    }
    double len = sqrt(sqr(x1-x2)+sqr(y1-y2));
    double dis = fabs(a1*x+b1*y+c1)/sqrt(a1*a1+b1*b1);  
    if (dis*dis+len*len < sqr(x1-x)+sqr(y1-y))
        dis = sqrt(sqr(x2-x)+sqr(y2-y));
    else if (dis*dis+len*len < sqr(x2-x)+sqr(y2-y))
        dis = sqrt(sqr(x1-x)+sqr(y1-y));
    if (dis < ans)
        ans = dis;
}
int main(){
    int tt;
    scanf("%d", &tt);
    for(int cases = 1; cases <= tt; cases++){
        scanf("%d", &n);
        for(int i = 1; i <= n; i++)
            scanf("%lf %lf", &a[i][1], &a[i][2]);
        a[0][1] = a[n][1];
        a[0][2] = a[n][2];
        scanf("%d", &m);
        for(int i = 1; i <= m; i++)
            scanf("%lf %lf", &b[i][1], &b[i][2]);
        b[0][1] = b[m][1];
        b[0][2] = b[m][2];
        ans = 1e9;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                count(a[i-1][1], a[i-1][2], a[i][1], a[i][2], b[j][1], b[j][2]);
            }
        }
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                count(b[i-1][1], b[i-1][2], b[i][1], b[i][2], a[j][1], a[j][2]);
            }
        }
        ans = ans/2;
        printf("%.10lf\n", ans);
    }
    return 0;
}
