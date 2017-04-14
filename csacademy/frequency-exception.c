#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int cmp(const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int n,v[1001],sav,mx,nrdif,nr,sav2;
int main() {
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&v[i]);
    }
    qsort(v+1, n, sizeof(int), cmp);
    int i = 2;
    nr = 1;
    while (v[i]==v[i-1])
    {
        i++;
        nr++;
    }
    sav = nr;
    nr = 1;
    for (i++;i<=n;i++)
    {
        if( v[i]==v[i-1])
            nr++;
        else
        {
            if (nr!=sav)
            {
                nrdif++;
                sav2 = v[i-1];
            }
            nr = 1;
        }
    }
    if (nr!=sav)
    {
        nrdif++;
        sav2 = v[i-1];
    }
    if (nrdif==1)
        printf("%d\n", sav2);
    else
        printf("%d\n", v[1]);
    return 0;
}



