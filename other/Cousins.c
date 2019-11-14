#include<stdio.h>
#include<string.h>

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

char x[200],y[200];
int  b[200][200];
int nx,ny,i,j,k,m,n;

int main(){
  while (2 == scanf("%s%s",x,y) && x[0] != '0'){
    memset(b,0,sizeof(b));
    nx = strlen(x); 
    ny = strlen(y);
    for (i=0;i<nx;i++) {
      for (j=0;j<ny;j++) {
        if (x[i] == y[j])
          b[i+1][j+1] = b[i][j]+1;
        else
          b[i+1][j+1] = max(b[i][j+1], b[i+1][j]);
      }
    }
    k = min(nx,ny);
    m = b[nx][ny];
    n = max(nx,ny) - m;
    for (i=0;n;i++) {
      n -= min(n,(n+m)/2);
      m += min(n+m,k-m);
    }
    printf("%d\n",i>1?i:1);
  }
  if (strcmp(x,"0") || strcmp(y,"0"))
    printf("bad input\n");
  return 0;
}
