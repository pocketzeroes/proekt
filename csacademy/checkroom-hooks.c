#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}


enum{ INF = 1001001001};

int n, cur;
double**ans;


void fill(int*arr,int sz, int val){
  for(int i=0;i<sz;i++)
    arr[i]=val;
}

void dfs(int*a){
  int b[n]; fill(b, n, INF);
  {
    int x = 1;
    for(int i = 0; i < (n); ++i) {
      if (a[i]) 
        x = 0;
      b[i] = min(b[i],x);
      ++x;
    }
  }
  {
    int x = 1;
    for(int i = (n)-1; i >= 0; --i) {
      if (a[i]) 
        x = 0;
      b[i] = min(b[i],x);
      ++x;
    }
  }
  int t = 0;
  for(int i = 0; i < (n); ++i) 
    t = max(t,b[i]);
  int si = cur;
  if (t == 1) {
    int m = n-si;
    for(int i = 0; i < (n); ++i) {
      if (b[i] == t) {
        for (int j = si; j < n; ++j) 
          ans[j][i] += 1.0/m;
      }
    }
  } 
  else {
    int m = 0, g = 0;
    for(int i = 0; i < (n); ++i) {
      if (b[i] == t) {
        a[i] = 1;
        ++cur;
        ++i;
        ++m;
        if (b[i] == t) 
          ++g;
      }
    }
    {
      double tt[g+1]; memset(tt,0,sizeof(tt));
      double dp[g+1]; memset(dp,0,sizeof(dp));
      dp[g] = 1;
      double d[m][2]; memset(d, 0,sizeof(d ));
      for(int i = 0; i < (m); ++i) {
        double pd[g+1]; memset(pd,0,sizeof(pd));
        
        memcpy(tt, pd, sizeof(dp));
        memcpy(pd, dp, sizeof(dp));
        memcpy(dp, tt, sizeof(dp));
        
        for(int j = 0; j < (g+1); ++j){
          double p = 1.0/(m-i+j);
          {
            dp[j]    += pd[j]*p*(m-i-j);
            d [i][0] += pd[j]*p*(m-i-j)/(m-g);
          }
          if (j) {
            dp[j-1 ] += pd[j]*p*(j*2);
            d [i][1] += pd[j]*p*(j*2)/g;
          }
        }
      }
      for(int i = 0; i < (n); ++i) {
        if (b[i] == t) {
          if (b[i+1] == t) {
            for(int j = 0; j < (m); ++j) 
              ans[si+j][i] += d[j][1];
          } 
          else {
            for(int j = 0; j < (m); ++j) 
              ans[si+j][i] += d[j][0];
          }
          ++i;
        }
      }
    }
    dfs(a);
    for(int i = 0; i < (n-1); ++i) {
      if (b[i] == t && b[i+1] == t) {
        int l = i-t+1, r = i+t;
        while (l < r) {
          for (int j = si; j < n; ++j) {
            double sum = ans[j][l]+ans[j][r];
            ans[j][l]  = ans[j][r] = sum/2;
          }
          ++l; --r;
        }
      }
    }
  }
}
int main() {
  scanf("%d",&n);
  int*a = (int*) calloc(n, sizeof(int));
  ans = (double**) calloc(n,sizeof(double*));
  for(int i=0;i<n;i++)
    ans[i] = (double*) calloc(n, sizeof(double));
  dfs(a);
  for(int i = 0; i < (n); ++i) {
    for(int j = 0; j < (n); ++j){
      printf("%.10f%c", ans[i][j], j==n-1 ? '\n':' ');
    }
  }
  return 0;
}


































