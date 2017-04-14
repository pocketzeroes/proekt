#include <stdio.h>
#include <math.h>
enum{ kMod =(int)1e9+7};
int Pow(int a, int p) {
    int res = 1;
    while (p) {
        if (p & 1) {
            res = (1LL * res * a) % kMod;
        }
        a = (1LL * a * a) % kMod;
        p /= 2;
    }
    return res;
} 
int main() {
    int n, i, x = 0, y = 0, nr, dif = 0, c = 0;
    scanf("%d",&n);
    for(i = 1; i <= n; i++)
    {
        x = x * 10 + 9;
        dif = dif * 10 + 1;
    }
    int t = dif;
    while(dif != x + t)
    {
        printf("Q %d\n", dif); fflush(stdout);
        scanf("%d",&nr);
        while(nr)
        {
            y = y + Pow(10, c) * (dif % 10);
            nr--;
            c++;
        }
        dif += t;
    }
    while(c != n)
    {
        y *= 10;
        c++;
    }
    printf("A %d\n", y); fflush(stdout);
    return 0;
}
