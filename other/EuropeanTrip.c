#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ N = 3};

typedef struct{
    double x, y;
}pt;
pt p[N];

double dist(pt a, pt b){
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double GetSum(pt*p, int n, pt t){
    double ans = 0;
    while (n--)
        ans += dist(p[n], t);
    return ans;
}
pt gradient(pt*p, int n, pt t){
    pt grad;
    grad.x = 0;
    grad.y = 0;
    while (n--){
        grad.x += (t.x - p[n].x) / dist(p[n], t);
        grad.y += (t.y - p[n].y) / dist(p[n], t);
    }
    return grad;
}
double learning_rate(double lr){
    return 0.99*lr;
}
void SGD(pt*p, int n){
    pt cur;
    cur.x = (p[0].x + p[1].x + p[2].x) / 3;
    cur.y = (p[0].y + p[1].y + p[2].y) / 3;
    int cnt = 0;
    double lr = 0.1;
    while (1){
        ++cnt;
        double pre = GetSum(p, n, cur);
        pt grad = gradient(p, n, cur);
        cur.x =cur.x - grad.x * lr * pre;
        cur.y =cur.y - grad.y * lr * pre;
        lr = learning_rate(lr);
        double now = GetSum(p, n, cur);
        if(fabs(pre-GetSum(p,n,cur))<1e-10)
            break;
    }
    printf("%.9lf %.9lf\n", cur.x, cur.y);
}
int main(){
    int n = 3;
    for(int i=0; i<n; i++)
        scanf("%lf %lf", &p[i].x, &p[i].y);
    SGD(p, n);
    return 0;
}
