#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<complex.h>
#define newpt __builtin_complex
char buff[1000000];
char*getstr(){
  if(scanf("%s", &buff)!=1)
    return NULL;
  return strdup(buff);
}


typedef complex double pt;


int    n,m;
double price;
char*  name[100];
bool   bad [100];
pt     P   [100];
int    M   [100][100];
double F[1<<15][51][2];

double f(int mask, int cur, int b){
#define ret F[mask][cur][b]
  if(ret==-1) {
    ret = 1e17;
    if(mask==0) {
      if(cur==m-1) ret=0;
      return ret;
    }
    for(int i=(0),_b=((n)-1);i<=_b;i++){
      if((mask&1<<i) && M[cur][i]!=-1){
        for(int j=(0),_b=((m)-1);j<=_b;j++){
          int tmp = mask^(1<<i);
          double val;
          if(j==cur)
            ret = fmin(ret, f(tmp,j,b||bad[i])+M[cur][i]);
          else if(bad[i] || b)
            ret = fmin(ret, f(tmp,j,0)+M[cur][i]+(cabs(P[cur])+cabs(P[j]))*price);
          else
            ret = fmin(ret, f(tmp,j,0)+M[cur][i]+cabs(P[j]-P[cur])*price);
        }
      }
    }
  }
  return ret;
  #undef ret
}
int main(){
  int T;
  scanf("%d", &T);
  for(int C=1; C<=T; C++){
    scanf("%d %d %lf", &n, &m, &price);
//    printf("=== C = %d; n = %d; m = %d; p = %llf\n", C, n, m, price);
    for(int i=0; i<n; i++){
      name[i]=getstr();
      bad[i]=0;
      if(name[i][strlen(name[i])-1]=='!'){
        bad[i]=1;
        name[i][strlen(name[i])-1]='\0';
      }
//    puts("name==="); puts(name[i]);
    }
    memset(M, -1, sizeof(M));
    for(int i=0; i<m; i++){
      double cr, ci;
      scanf("%lf %lf", &cr, &ci);
      P[i] = newpt(cr, ci);
      while(1){
        char*t=getstr();
        int k = strchr(t, ':')-t;
        int p = atoi(t+k+1);
        t[k]='\0';
        for(int j=0,_b=((n)-1); j<=_b; j++){
          if(strcmp(t, name[j])==0){
            M[i][j] = p;
            break;
          }
        }
        char c = getchar(); ungetc(c, stdin);
        if(c==' ')continue;
        else if(c=='\n')break;
      }
    }
    P[m++] = newpt(0., 0.);
    for(int i=0,_b=((1<<n)-1); i<=_b; i++)
      for(int j=0,_b=((m)-1); j<=_b; j++)
        for(int k=0,_b=((2)-1); k<=_b; k++)
          F[i][j][k] = -1;
    double sol = 1e17;
    for(int i=0,_b=((m)-1); i<=_b; i++)
      sol = fmin(sol, f((1<<n)-1,i,0)+cabs(P[i])*price);
    printf("Case #%d: %.7f\n", C, sol);
  }
  return 0;
}
