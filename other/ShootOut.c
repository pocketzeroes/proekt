#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

double prob[1<<13][13][13];  
int nextMiss[14][1<<13][13]; 

int main(){
  int N,n,p[13];  
  double best[13][13];
  for(int n=2;n<=13;n++)
    for(int mask=1;mask<(1<<n);mask++)
      for(int i=0;i<n;i++)
        if ((1<<i)&mask){
          int j=(i+1)%n;
          while (((1<<j)&mask)==0)
            j=(j+1)%n;
          nextMiss[n][mask][i]=j;
        }
  scanf("%d", &N);
  while(N--){
    scanf("%d", &n);
    for(int i=0;i<n;i++)
      scanf("%d", &p[i]);
    for(int i=1;i<(1<<n);i++){
      double avgProb[n][n];
      for(int j=0;j<n;j++)
        if(((1<<j)&i)!=0){
          for(int m=0; m<n; m++)
            avgProb[j][m]=0;
          double bestProb=-1;
          int cnt=0;
          for(int k=0;k<n;k++)
            if (j!=k && (((1<<k)&i)!=0)){
              int next=nextMiss[n][i][j];
              if(next==k)
                next=nextMiss[n][i][k];
              double p=prob[i-(1<<k)][next][j];
              if (p>bestProb+1e-9){
                bestProb=p;
                for(int m=0;m<n;m++)
                  avgProb[j][m]=0;
                cnt=0;
              }
              if (fabs(p-bestProb)<=1e-9){
                for(int m=0;m<n;m++)
                  avgProb[j][m]+=prob[i-(1<<k)][next][m];
                cnt++;
              }
            }
          if(cnt==0)
            avgProb[j][j]=1;
          else
            for(int m=0;m<n;m++)
              avgProb[j][m] /= cnt;
        }
      for(int j=0;j<n;j++){
        if ((1<<j)&i){
          double q=1,qq=1;
          for(int k=0;k<n;k++)
            prob[i][j][k]=0;
          for(int k=0;k<n;k++)
            if ((1<<k)&i)
              qq*=(100-p[k])/100.0;
          int cur=j;
          do{
            for(int m=0;m<n;m++){
              double z=avgProb[cur][m]*q*(p[cur]/100.0);
              prob[i][j][m]+=z*(1-qq/(qq-1));
            }             
            q*=(100-p[cur])/100.0;
            cur=nextMiss[n][i][cur];
          }
          while (cur!=j);
        }
      }
    }
    for(int i=0;i<n;i++){
      if (i>0)
        printf(" ");
      printf("%.10lf", prob[(1<<n)-1][0][i]*100.0);
    }
    puts("");
  }
  return 0;
}
