#include<stdio.h>
#include<string.h>
enum{N=5105,M=65,P=1000000007};
int Case,m,n,i,j,k,o,x,no,tmp,ret,f[N][M][M][2],p[N];
char a[N],b[N];

static inline void up(int*a, int b){*a = *a+b<P? *a+b : *a+b-P;}
int solve(char*a, int r){
  n=strlen(a);
  for(i=0;i<n;i++)
    a[i]-='0';
  for(p[0]=i=1;i<=n;i++)
    p[i]=10*p[i-1]%m;
  for(i=1;i<=n;i++)
    for(j=0;j<m;j++)
      for(k=0;k<m;k++)
        for(o=0;o<2;o++)
          f[i][j][k][o]=0;
  f[0][0][0][1]=1;
  for(i=0;i<n;i++)
    for(j=0;j<m;j++)
      for(k=0;k<m;k++)
        for(o=0;o<2;o++){
          tmp=f[i][j][k][o];
          if(!tmp)
            continue;
          for(x=0;x<10;x++){
            if(o){
              if(x>a[i])
                break;
              no=x==a[i];
            }
            else
              no=0;
            up(&f[i+1][((j+x*(k-p[n-i-1]))%m+m)%m][(k+x)%m][no],tmp);
          }
        }
  for(ret=j=0;j<m;j++)
    for(k=0;k<=r;k++)
      up(&ret,f[n][0][j][k]);
  return ret;
}
int main(){
  scanf("%d", &Case);
  while(Case--){
    scanf("%s %s %d", a, b, &m);
    printf("%d\n", (solve(b,1)-solve(a,0)+P)%P);
  }
  return 0;
}
