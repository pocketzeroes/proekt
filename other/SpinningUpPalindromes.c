#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ N=50};
enum{inf=10000000};
int n,m,l,r,i,j,k,x,y,t,w;
char s[N];
int a[N],f[N][2][2],ans=inf;

inline void up(int*a, int b){
    if(*a > b)
       *a = b;
}
int main(){
    scanf("%s", s+1);
    n = strlen(s+1);
    for(i=1;i<=n;i++)
        a[i]=s[i]-'0';
    for(i=0;i<=n+5;i++)
        for(j=0;j<2;j++)
            for(k=0;k<2;k++)
                f[i][j][k]=inf;
    f[0][0][0]=f[0][1][0]=0;
    for(l=1,r=n;l<r;l++,r--)for(i=0;i<2;i++)for(j=0;j<2;j++)if(f[l-1][i][j]<inf){
        w=f[l-1][i][j];
        for(x=0;x<10;x++)for(y=0;y<10;y++){
            for(k=0;k<2;k++){
                int A=a[l]+x+k,nA=0;
                if(A>=10)A-=10,nA++;
                if(nA!=i)continue;
                int B=a[r]+y+j,nB=0;
                if(B>=10)B-=10,nB++;
                if(A!=B)continue;
                up(&f[l][k][nB],w+x+y);
            }
        }
    }
    m=n/2;
    if(n%2){
        for(i=0;i<2;i++)for(j=0;j<2;j++)if(f[m][i][j]<inf){
            w=f[m][i][j];
            for(x=0;x<10;x++){
                if((a[m+1]+x+j)/10!=i)continue;
                up(&ans,w+x);
            }
        }
    }else{
        for(i=0;i<2;i++)for(j=0;j<2;j++)if(f[m][i][j]<inf){
            w=f[m][i][j];
            if(i==j)up(&ans,w);
        }
    }
    printf("%d",ans);
    return 0;
}
