#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXD = 1005 };
enum{ MAXT = 10005};
int d, t, c, r;
double rain[MAXT], M[MAXT][MAXD];
bool   roof[MAXD];

int main(){
    scanf("%d %d %d %d", &d, &t, &c, &r);
    for(int i=0; i<c; i++){
        int s, e, a;
        double p;
        scanf("%d %d %lf %d", &s, &e, &p, &a);
        rain[s] += p*a;
        rain[e] += -p*a;
    }
    for(int i = 1; i <= t; i++)
        rain[i] += rain[i-1];
    for(int i = 0; i < r; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        while(y-- > x)
            roof[y] = true;
    }
    for(int i=0; i<=t; i++)
        M[i][0] = 0;
    for(int i=1; i<=d; i++)
        M[0][i] = 1e100;
    for(int i=1; i<=t; i++){
        for(int j=1; j<=d; j++){
            double walk = roof[j-1] ? M[i-1][j-1] : M[i-1][j-1] + rain[i-1];
            double wait = roof[j] ? M[i-1][j] : M[i-1][j] + rain[i-1];
            M[i][j] = fmin(walk, wait);
        }
    }
    printf("%.7lf\n", M[t][d]);
    return 0;
}
