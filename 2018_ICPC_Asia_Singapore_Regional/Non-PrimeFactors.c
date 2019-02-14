#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MX =(int) 2e6 + 5};
int cnt [MX];
int flag[MX];

int main(){
  for(int i = 2 ; i < MX ; i++){
    if(!flag[i]){
      for(int j = i ; j < MX ; j += i)
        flag[j] = 1;
    }
    else{
      for(int j = i ; j < MX ; j += i)
        cnt[j]++;
    }
  }
  int q;
  scanf("%d", &q);
  for(int i=0; i < q; i++){
    int x;
    scanf("%d", &x);
    printf("%d\n", cnt[x] + 1);
  }
  return 0;
}
