#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

double max(double a,double b){return a>b?a:b;}

int cmp (const void *pa, const void *pb){
    double*a=(double*)pa;
    double*b=(double*)pb;
    return *a < *b ? -1 : 1;
}

int main() {
    int i, j;
    int f, r;
    int fv[10], rv[10];
    double drive[100];
    while(scanf("%d",&f), f){
        scanf("%d", &r);
        for(i = 0; i < f; i++)
            scanf("%d", &fv[i]);
        for(i = 0; i < r; i++)
            scanf("%d", &rv[i]);
        int k = 0;
        for(i = 0; i < r; i++){
            for(j = 0; j < f; j++){
                drive[k] = (double) rv[i] / (double) fv[j];
                k++;
            }
        }
        qsort(drive, k, sizeof(double), cmp);
        double maxS = -1.;
        for(i = 0; i < k - 1; i++)
            maxS = max(maxS, drive[i + 1] / drive[i]);
        printf("%.2lf\n", maxS);
    }
    return 0;
}
