#include<stdio.h>
#define N 100000
int x[N+1];
long long w[N+1];
long long maxim(long long a,long long b){
    return (a<b) ? b : a;
}
int main(){
    int n,in,k,i,p;
    scanf ("%d%d%d",&n,&in,&k);
    p=0;
    for(i=1;i<=n;i++){
        scanf ("%d%lld",&x[i],&w[i]);
        if (x[i]<in) p++;
        w[i]+=w[i-1];
    }
    int j=p+1;
    long long max=0;
    for(i=1;i<=p;i++){
        long long aux=0;
        if (in-x[i]<=k){
            aux=w[p]-w[i-1];
            if ((in-x[i])*2<=k){
                int c=in+k-(in-x[i])*2;
                for(;j<=n &&x[j]<=c;j++) ;
                j--;
                aux+=(w[j]-w[p]);
            }
        }
        max=maxim(max,aux);
    }
    p++;
    j=p-1;
    for(i=n;i>=p;i--){
        long long aux=0;
        if (x[i]-in<=k){
            aux=w[i]-w[p-1];
            if ((x[i]-in)*2<=k){
                int c=in-(k-(x[i]-in)*2);
                for(;j>0 &&x[j]>=c;j--) ;
                j++;
                aux+=(w[p-1]-w[j-1]);
            }
        }
        max=maxim(max,aux);
    }
    printf ("%lld",max);
    return 0;
}
