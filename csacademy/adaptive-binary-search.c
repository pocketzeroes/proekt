#include <stdio.h>
int main() {
    int n;
    scanf("%d", &n);
    int st=0,en=n+1;
    int mid,ans;
    while(en-st>1)
    {
        mid=(st+en)/2;
        printf( "Q %d\n" mid); fflush(stdout);
        int y;
        scanf("%d", &y);
        if(!y)
        {
            en=mid;
            ans=mid;
        }
        else
            st=mid;
    }
    printf( "A %d\n" ans); fflush(stdout);
    return 0;
}
