#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
/////////////////
enum{ maxn  = 150000 };
enum{ maxk  = 9      };
enum{ infty =(int)2e9};
pair A[maxn];
int  B[maxk+1][maxn+1];


int main(){
  int TT;
  scanf("%d", &TT);
  while(TT--){
    int n, k;
    scanf("%d %d", &n, &k);
    for(int i=0; i<n; i++)
      scanf("%d %d", &A[i].first, &A[i].second);
    qsort(A, n, sizeof(pair), cmpP);
    B[0][n] = -infty;
    for(int i=n-1; i>=0; i--)
      B[0][i] = max(B[0][i+1], A[i].first-A[i].second);
    for(int q=1; q<=k; q++){
      B[q][n] = -infty;
      for(int i=n-1; i>=0; i--){
        int u = min(A[i].first-A[i].second, B[q-1][i+1]-A[i].second);
        B[q][i] = max(u,B[q][i+1]);
        if(i+q>n)
          B[q][i] = -infty;
      }
    }
    printf("%d\n", max(B[k][0],0));
  }
  return 0;
}
