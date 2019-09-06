#include<stdio.h>
#include<string.h>
#include<stdlib.h>

enum{ MAXN = 100000};

int n;
int val[MAXN+2];

int int_cmp(const void *e1,const void *e2){
  int i1 = *((const int *)e1);
  int i2 = *((const int *)e2);
  return i1-i2;
}
int main(){
  int i,tmp;
  while(1){
    n=-1;
    scanf("%d ", &n);
    if(n<=0) break;
    for(i=0;i<n;i++) scanf("%d ", &val[i]);
    qsort(val, n, sizeof(val[0]), int_cmp);
    printf("%d-A", val[0]); 
    tmp=0;
    for(i=n-1;i>=1;i--)
    {
      tmp = 1-tmp;
      printf(" %d-%c", val[i], 'A'+tmp);
    }
    printf("\n");
  }
  return 0;
}

