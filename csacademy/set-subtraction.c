#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#include<stdbool.h>
#include<stdint.h>

int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int ts, kk=1;
int n;
int a [2005];
int vs[2005];

int main(){
    int t,i,j,k;
    scanf("%d",&n);
    for(i=0;i<2*n;i++)
        scanf("%d",&a[i]);
    qsort(a, n+n, sizeof(int), cmp);
    for(i=n+n-2;i>-1;i--){
        if( a[n+n-1]==a[i] )
            continue;
        int x=a[n+n-1]-a[i];
        kk++;
        vs[n+n-1]=kk;
        vs[i]=kk;
        k=i;
        for(j=n+n-1;j>-1;j--){
            if( vs[j]==kk )
                continue;
            for(;k>-1;k--){
                if( a[j]-a[k]>x ){
                    k=-1;
                    break;
                }
                if(vs[k]==kk)
                    continue;
                if( a[j]-a[k]==x )
                    break;
            }
            if(k==-1)
                break;
            vs[k]=kk;
        }
        if(j==-1){
            kk++;
            printf("%d\n%d",x,a[n+n-1]);
            kk++;
            vs[n+n-1]=kk;
            vs[i]=kk;
            k=i;
            for(j=n+n-1;j>-1;j--){
                if( vs[j]==kk )
                    continue;
                printf(" %d",a[j]);
                for(;k>-1;k--){
                    if( a[j]-a[k]>x ){
                        k=-1;
                        break;
                    }
                    if(vs[k]==kk)
                        continue;
                    if( a[j]-a[k]==x )
                        break;
                }
                if(k==-1)
                    break;
                vs[k]=kk;
            }
            puts("");
            return 0;
        }
    }
    puts("-1");
    return 0;
}




















































