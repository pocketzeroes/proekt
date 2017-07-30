#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#define MAX_N 100000

int abs(int x){
    return (x<0? -x:x);
}
int main(){
    int i,j;
    int n,ind1[MAX_N],ind2[MAX_N],A[MAX_N],x,N,M;
    while(1){
        scanf("%d",&n);
        if(n==0) 
            break;
        N = M = 0;
        for( i=0;i<n;++i){
            scanf("%d",&x);
            if(x<0){
                ind1[N] = i;
                A[i] = -x;
                ++N;
            }
            else{
                ind2[M] = i;
                A[i] = x;
                ++M;
            }
        }
        long long ans = 0;
        for( i=0,j=0;i<N;++i){
            while(A[ind1[i]]>0){
                x = min(A[ind1[i]],A[ind2[j]]);
                A[ind1[i]] -= x; A[ind2[j]] -= x;
                ans += (long long)x*abs(ind1[i]-ind2[j]);
                if(A[ind2[j]]==0) 
                    ++j;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
