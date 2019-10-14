#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAX_N = 10000};
enum{ MAX_T = 1000000};

typedef struct hearing{
    int s,a,b;
}hearing;

hearing sched[MAX_N];

double opt[2+MAX_T]; 
double sum[2+MAX_T]; 

int main(){
    int n;
    scanf("%d", &n);
    for(int j=0; j < n; j++){
        int s,a,b;
        scanf("%d%d%d", &sched[j].s, &sched[j].a, &sched[j].b);
    }
    int h = n-1;
    sum[MAX_T+1] = opt[MAX_T+1] = 0;
    for(int t=MAX_T; t >= 1; t--){
        opt[t] = opt[t+1];     
        while(h >= 0 && sched[h].s == t){
            int a = sched[h].a,
                b = sched[h].b;
            double rest = (sum[(int)fmin(t+a,MAX_T+1)] - sum[(int)fmin(t+b+1,MAX_T+1)])/(b-a+1);
            double possible = 1 + rest;
            opt[t] = fmax(opt[t], possible);
            h--;
        }
        sum[t] = opt[t] + sum[t+1];
    }
    printf("%.9lf\n", opt[1]);
    return 0;
}
