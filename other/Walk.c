#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ typeof(a) tp; tp = a; a = b; b = tp; }while(0)
void Fill(double*arr, int sz, double val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
typedef struct{
    double x, y;
}pt;

enum{ MaxN = 3000 + 100};
const double eps = 1e-8;
pt*poly[MaxN];
int sizes[MaxN];
int h[MaxN];
int n, intersect_cnt[MaxN];
double left_most[MaxN];


int mycmp(const void*pa, const void*pb){
    int*a=(int*)pa;
    int*b=(int*)pb;
    return(left_most[*a] < left_most[*b])?-1:1;
}
void init(){
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &h[i]);
        int pn;
        scanf("%d", &pn);
        poly[i] =(pt*)calloc(pn+1, sizeof(pt));
        sizes[i] = pn+1;
        for(int j = 0; j < pn; ++j){
            scanf("%lf%lf", &poly[i][j].x, &poly[i][j].y);
        }
        poly[i][pn] = poly[i][0];
    }
}
void work(){
    memset(intersect_cnt, 0, sizeof(intersect_cnt));
    Fill(left_most, n, 1e100);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j + 1 < sizes[i]; ++j){
            double x1 = poly[i][j].x, 
                   y1 = poly[i][j].y, 
                   x2 = poly[i][j + 1].x, 
                   y2 = poly[i][j + 1].y;
            if (fabs(y1 - y2) < eps) 
                continue;
            if (y1 > y2){
                swap(x1, x2);
                swap(y1, y2);
            }
            double y = 0.0;
            if (!(y1 < y + eps && y + eps < y2)) 
                continue;
            double x = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
            if (x < 0.0 || x > 100000.0) 
                continue;
            ++intersect_cnt[i];
            left_most[i] = fmin(left_most[i], x);
        }
    }
    int seq[MaxN];
    for (int i = 0; i < n; ++i) 
        seq[i] = i;
    qsort(seq, n, sizeof(int), mycmp);
    int pre_h = -1;
    int up_cnt = 0, down_cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (intersect_cnt[seq[i]] % 2 == 0) 
            continue;
        if (pre_h == h[seq[i]]) 
            continue;
        if (pre_h != -1)
            if (pre_h < h[seq[i]]) 
                up_cnt += h[seq[i]] - pre_h;
            else
                down_cnt += pre_h - h[seq[i]];
        pre_h = h[seq[i]];
    }
    printf("%d %d\n", up_cnt, down_cnt);
}
int main(){
    int t=1;
    for(; t > 0; --t){
        init();
        work();
    }
    return 0;
}
