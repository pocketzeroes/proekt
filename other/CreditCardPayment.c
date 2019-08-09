#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

const double eps = 1e-8;
const double max_b = 50000;
enum{ max_payments = 1200};

int main(){
    int tn;
    for(scanf("%d", &tn); tn--;){
        double r, b, m;
        scanf("%lf %lf %lf", &r, &b, &m);
        int minnum = 0;
        double pb = max_b + 1;
        while (b > 0 && minnum++ <= max_payments && b < pb){
            pb = b;
            b *= (1 + r / 100.0);
            b = (int)(b * 100 + 0.5 + eps) / 100.0;
            b -= m;
        }
        if (minnum > max_payments || b >= pb)
            puts("impossible");
        else
            printf("%d\n", minnum);
    }
    return 0;
}
