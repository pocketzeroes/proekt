#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int query(int index) {
    printf("Q %d\n", index);
    fflush(stdout);
    int value;
    scanf("%d", &value);
    return value;
}
int solve(int n) 
{
    if(n==1) return 0;
    int fi=query(1);
    int lo=2,hi=n,mid,ans=0;
    while(lo<=hi)
    {
        mid=(lo+hi)/2;
        int val=query(mid);
        if(val<fi)
        {
            ans=mid;
            hi=mid-1;
        }
        else lo=mid+1;
    }
    if(ans) ans--;
    return ans;
}
int main() {
    int N;
    scanf("%d", &N);
    printf("A %d\n", solve(N));
    fflush(stdout);
    return 0;
}
