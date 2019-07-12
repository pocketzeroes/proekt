#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ INF  = 1000000000  };
enum{ BASE = 1000000007  };
enum{ MAX  = 100007      };
enum{ MAX2 = 7777        };
enum{ MAXE = 100000      };
enum{ ADD  = 1000000     };
enum{ MOD  = 1008691207  };
enum{ CNT  = 800         };

double L[MAX];
double R[MAX];
double S[4][MAX];

int main(){
    int n;
    scanf("%d", &n);
    for(int i=(0);i<(n);i++)
        scanf("%lf%lf", &L[i], &R[i]);
    double res = 0;
    for(int i=(0);i<(n);i++)
        res += (i - (n - 1 - i)) * (R[i] + L[i]) / 2;
    for(int i=(0);i<(4);i++)
        S[i][0] = 0;
    for(int i=(0);i<(n);i++){
        if (R[i] > L[i]){
            S[0][i + 1] = S[0][i] + R[i] * R[i] * R[i] / (R[i] - L[i]);
            S[1][i + 1] = S[1][i] - 3 * R[i] * R[i] / (R[i] - L[i]);
            S[2][i + 1] = S[2][i] + 3 * R[i] / (R[i] - L[i]);
            S[3][i + 1] = S[3][i] - 1 / (R[i] - L[i]);
        }
        else{
            for(int j=(0);j<(4);j++)
                S[j][i + 1] = S[j][i];
        }
    }
    int ptr = 0;
    for(int i=(0);i<(n);i++){
        while (ptr < n && R[ptr] < L[i])
            ++ptr;
        if (R[i] == L[i])
            continue;
        double a3 = S[3][i] - S[3][ptr];
        double a2 = S[2][i] - S[2][ptr];
        double a1 = S[1][i] - S[1][ptr];
        double a0 = S[0][i] - S[0][ptr];
        res += 1. / (3 * (R[i] - L[i])) * (a3 * L[i] * L[i] * L[i] + a2 * L[i] * L[i] + a1 * L[i] + a0);
    }
    res /= 1.0 * n * n;
    printf("%.10f\n" , res);
    return 0;
}
