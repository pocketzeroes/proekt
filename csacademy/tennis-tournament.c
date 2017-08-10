#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

enum{ Nmax =(int) 1e6 + 5};
typedef long long ll;
bool used[Nmax];
int n, k, m, i;

int main()
{
    scanf("%d %d %d", &n, &k, &m);
    if(k - (1<<m) + 1 < 1 || (k == (1<<n) && m < n))
    {
        puts("-1");
        return 0;
    }
    for(i=0; i<(1<<m); ++i)
        printf("%d ", k - i), used[k-i] = 1;
    for(i=(1<<n); i; --i) 
        if(!used[i]) 
            printf("%d ", i);
    return 0;
}
