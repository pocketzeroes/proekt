#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define MAX 1000000007LL;
int min(int a,int b){return a<b?a:b;}
void swap(int*nums, int i, int j) {
  int t   = nums[i];
  nums[i] = nums[j];
  nums[j] = t;
}
void reverse(int*nums, int start, int end){
  while( start < end) {
    swap(nums, start, end);
    start++;
    end  --;
  }
}
int main() {
  int T;
  scanf("%d", &T);
  while(T--){
    int n;
    scanf("%d", &n);
    int a[n], ans = MAX;
    for(int i=0; i<n; i++) 
      scanf("%d", &a[i]);
    for(int k=0; k<2; k++){
      int b[n], sum=0;
      for(int i=0; i<n; i++) 
        b[i] = a[i];
      for(int i=1; i<n; i++){
        if(b[i]==n/2){
          swap(b, 0, i);
          sum++;
          break;
        }
      }
      for(int i=(n-1)-1; i>=0; i--){
        if(b[i]==n/2+1){
          swap(b, n-1, i);
          sum++;
          break;
        }
      }
      int x=0;
      for(int i=1; i<n-1; i+=2){
        if(b[i]<=n/2) 
          x++;
      }
      ans = min(ans,sum+x);
      reverse(a, 0, n-1);
    }
    printf("%d\n", ans);
  }
}























