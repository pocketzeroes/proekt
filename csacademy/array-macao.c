#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
int max_element(int*arr, int sz){
  int maxe=arr[0];
  for(int i=1;i<sz;i++)
    if(arr[i]>maxe)
      maxe=arr[i];
  return maxe;
}

enum{ MXN =(int)1e5+5};
char*a[MXN];
char*b[MXN];
char buff[100000];

int main(){
  int n;
  scanf("%d", &n);
  for(int i=0; i<n; ++i){
    scanf("%s", &buff);
    a[i] = strdup(buff);
  }
  for(int i = 0; i < n; ++i){
    scanf("%s", &buff);
    b[i] = strdup(buff);
  }
  int dpa[10] = {0};
  int dpb[10] = {0};
  for(int i=0;a[0][i];i++){char c = a[0][i];
    dpa[c - '0'] = 1;
  }
  for(int i=1; i<n; ++i){
    int mxa = 1;
    int mxb = 0;
    for(int q=0;a[i][q];q++){char c = a[i][q];
      mxa = max(mxa, dpb[c - '0'] + 1);
    }
    for(int q=0;b[i][q];q++){char c = b[i][q];
      if(dpa[c - '0'])
        mxb = max(mxb, dpa[c - '0'] + 1);
    }
    for(int q=0;a[i][q];q++){char c = a[i][q];
      dpa[c - '0'] = max(dpa[c - '0'], mxa);
    }
    for(int q=0;b[i][q];q++){char c = b[i][q];
      dpb[c - '0'] = max(dpb[c - '0'], mxb);
    }
  }
  printf("%d\n", max(max_element(dpa, 10), max_element(dpb, 10)) );
  return 0;
}
