#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
ll ar[1000010], sm[1000010], ase[1000010];
int main(){
    ll i,j,n,m,a,b,c,d,e,f,g=0;
    scanf("%lld %lld", &n, &m);
    for(int i=0;i<=n-1;i++)
        scanf("%lld", &ar[i]), g+=ar[i];
    a=0; b=0; c=ar[0];
    i=j=0; j++;
    while(i<n){
        c = ar[i]+sm[i];
        j = i+1;
        while(j<n){
            if(g-c<=m){
                g=ar[i];
                ase[i]=1;
                break;
            }
            if(ar[j]-c>m){
                sm[j]=c;
                i=j-1;
                break;
            }
            else
                c+=ar[j];
            j++;
            if(g-c<=m){
                g=ar[i];
                ase[i]=1;
                break;
            }
        }
        if(g-c<=m&&ase[i]==0){
            g=ar[i];
            ase[i]=1;
        }
        i++;
    }
    for(int i=0;i<=n-1;i++)
        if(ase[i]==1)
            printf("%d ", i+1);
    return 0;
}


