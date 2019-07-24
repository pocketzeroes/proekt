#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void rev(int*s, int l, int r){
    while(l<r)
        swap(s, l++, r--);
}
int b_search(int*s,int l,int r,int key){
    int index = -1;
    while(l<=r){
        int mid = l+(r-l)/2;
        if(s[mid]<=key)
            r=mid-1;
        else{
            l=mid+1;
            if(index = -1 || s[index]<=s[mid])
                index = mid;
        }
    }
    return index;
}
bool next_permutation(int*s, int sl){
    int len = sl, i=len-2;
    while(i>=0 && s[i]>=s[i+1])
       --i;
    if(i<0)
        return false;
    else{
        int index=b_search(s, i+1, len-1, s[i]);
        swap(s, i, index);
        rev(s, i+1, len-1);
        return true;
    }
}

double max(double a, double b){return a>b?a:b;}
double min(double a, double b){return a<b?a:b;}

int i, j, t, n, I[11];
double mx, bx, x[11], h[11], r[11], R[11];

double dh(int i, int j){
  return r[i] > R[j] ? h[j] : R[i] <= r[j] ? 0 : max(r[i] > r[j] ? (r[i]-r[j]) * h[j] / (R[j]-r[j]) : 0,
         R[i] < R[j] ? (R[i]-r[j]) * h[j] / (R[j]-r[j]) - h[i] :
         R[i] > r[i] ? h[j] - (R[j]-r[i]) * h[i] / (R[i]-r[i]) : 0);
}
double H(){
  for(mx = i = 0; x[i] = 0, i < n && mx < bx; mx = max(mx, x[i]+h[I[i]]), ++i)
    for(j = 0; x[i] = max(x[i], x[j]+dh(I[i], I[j])), j < i; ++j);
  return mx;
}
int main(){
  for(scanf("%d", &t); scanf("%d", &n), bx = 1e99, t--;){
    for(i = 0; i < n; ++i)
      I[i] = i, scanf("%lf%lf%lf", &h[i], &r[i], &R[i]);
    do
      bx = min(bx, H());
    while(next_permutation(I, n));
    printf("%d\n", (int)bx);
  }
  return 0;
}
