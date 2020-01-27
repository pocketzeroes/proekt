#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void * a, const void * b){return ( *(int*)a - *(int*)b );}
int gcd(int a, int b){while(b != 0){int temp = a % b; a = b; b = temp;}return a;}

int main(){
  int nums[1000];
  while(1){
    int n;
    int rv = scanf("%d", &n);
    if(rv != 1)
      return 0;
    for(int i=0; i<n; i++)
      scanf("%d", &nums[i]);
    int res = 0;
    qsort(nums, n, sizeof(int), cmp);
    for(int i=n-1; i>=0; i--){
      bool bien = true;
      int numero = nums[i];
      for(int j=n-1; j>=0; j--)
        if(j != i && gcd(numero, nums[j]) != 1){
          bien = false;
          break;
        }
      if(bien){
        res = numero;
        break;
      }
    }
    printf("%d\n", res);
  }
  return 0;
}
