#include<stdio.h>

enum{ nmax = 1000000000};
long long F[99];

int main(){
    int runs, run, n, a, b, c, k, m;
    F[1] = F[2] = 1;
    for (m = 3; (F[m] = F[m-1] + F[m-2]) <= nmax; m++);
    scanf("%d", &runs);
    for (run = 0; run < runs; run++){
        scanf("%d", &n);
        for (k = m-1; k > 2; k--){
            c = (n * F[k-1-k%2]) % F[k];
            if (c*F[k-1] < n)
                break;
        }
        a = (n-c*F[k-1]) / F[k];
        b = a+c;
        printf("%d %d\n", a, b);
    }
    return 0;
}
