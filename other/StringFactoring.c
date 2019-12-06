#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

int*Z;
int zlen;

void Z_algorithm(char*s, int offset){
  int slength = strlen(s);
  if(Z){free(Z);Z=NULL;}
  Z = calloc(slength-offset, sizeof(int)); fill(Z, slength-offset, -1);
  zlen = slength-offset;
  int L=0, R=0, n=slength-offset;
  for(int i=1; i<n; ++i){
    if(i>R){
      L = R = i;
      while(R<n && s[R-L+offset] == s[R+offset])
        R++;
      Z[i] = R - L;
      R--;
    }
    else if(Z[i-L]>=R-i+1){
      L = i;
      while(R<n && s[R-L+offset]==s[R+offset])
        R++;
      Z[i]=R-L;
      R--;
    }
    else
      Z[i] = Z[i - L];
  }
}
int main(){
  char*s = getstr();
  int n = strlen(s);
  int fact[n][n]; dfill(fact, n, n, (int)1e6);
  for(int i=n-1; i>=0; --i){
    Z_algorithm(s, i);
    for(int j=i; j<n; ++j){
      bool m = false;
      int cn = j-i+1;
      for(int L=1; L<=cn; ++L){
        if(cn%L!=0)
          continue;
        m = true;
        for(int cL=L; m&&cL<cn; cL*=2){
          int zcl=0;
          if(cL>=0 && cL<zlen)
            zcl = Z[cL];
          m = m&&(cL+zcl>=fmin(2*cL, cn));
        }
        if(m)
          fact[i][j] = fmin(fact[i][j], fact[i][i + L - 1]);
      }
      for(int k=i+1; k<=j; ++k){
        if(fact[i][j] > fact[i][k-1] + fact[k][j])
           fact[i][j] = fact[i][k-1] + fact[k][j];
      }
      if(fact[i][j] > 1e5)
         fact[i][j] = j-i+1;
    }
  }
  printf("%d\n", fact[0][n-1]);
  return 0;
}
