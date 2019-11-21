#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void swap(int*nums, int i, int j){
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
bool is_sorted(int*a, int n){
  for(int i=1; i<n; i++)
    if(a[i-1] > a[i])
      return 0;
  return 1;
}
int main(){
  int n;
  scanf("%d", &n);
  int a[n];
  for(int z=0;z<n;z++)
    scanf("%d", &a[z]);
  int i=0;
  while(i+1 < n && a[i+1] >= a[i])
    i++;
  while(i > 0 && a[i-1] == a[i])
    i--;
  int j = i;
  while(j+1 < n && a[j+1] <= a[j])
    j++;
  j++;
  reverse(a, i, j-1);
  if(is_sorted(a, n))
    printf("%d %d\n", i+1, j);
  else
    puts("impossible");
  return 0;
}
