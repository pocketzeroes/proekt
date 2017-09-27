#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
enum{ N =(int) 1e5 + 10};
int x[N];

int lower_bound(int*a, int n, int x) {
  int l = 0;
  int h = n;
  while (l < h) {
    int mid = (l + h) / 2;
    if (x <= a[mid]) 
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}
int main(){
  int n, k;
  scanf("%d %d", &n, &k);
  for(int i = 0; i < n; i++){
    int a, b;
    scanf("%d %d", &a, &b);
    x[b] = a;
  }
  int ans = 0;
  int y[n]; memset(y, 0, sizeof(y));
  for(int i = 1; i <= n; i++){
    int it = lower_bound(y, n, x[i]);
    it--;
    y[it] = x[i];
  }
  for(int i = 0; i < n; i++)
    if(y[i] == 0) 
      ans++;
  printf("%d\n", n - ans);
  return 0;
}
