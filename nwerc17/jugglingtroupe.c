#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

enum{ nmax = 1000000};
char S   [nmax+1];
int Zeros[nmax];

int main(){
    int n, k, nz, excess, tomove, i;
    scanf("%s", S);
    n = strlen(S);
    excess = 0;
    nz = 0;
    for (k = 1; k <= n; k++){
        excess += S[k-1]-'0';
        if (excess == 0){
            Zeros[nz++] = k;
            continue;
        }
        tomove = --excess;
        while (nz > 0 && tomove >= k+1 - Zeros[nz-1]){
            tomove -= k+1 - Zeros[nz-1];
            nz--;
            excess--;
        }
        if (nz > 0)
            Zeros[nz-1] += tomove;
        else if (tomove > 0){
            excess -= tomove/(k+1);
            if (tomove % (k+1))
                Zeros[nz++] = tomove % (k+1);
        }
    }
    i = 0;
    for (k = 1; k <= n; k++){
        if (i < nz && k == Zeros[i]){
            printf("0");
            i++;
        }
        else
            printf("1");
    }
    printf("\n");
    return 0;
}
