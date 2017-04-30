#include <stdio.h>
typedef long long ll;

int main()
{
    ll n;
    scanf("%lld", &n);
    ll l=0,r=n;
    while(l+1<r)
    {
        ll m=(l+r)/2;
        printf("Q %d\n", m);
        fflush(stdout);
        int x;
        scanf("%d", &x);
        if(x) l=m;
        else r=m;
    }
    printf("A %d\n", r);
    fflush(stdout);
    return 0;
}
