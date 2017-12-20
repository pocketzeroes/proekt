#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int max_element(int*arr,int sz){
  int maxe=arr[0];
  for(int i=1;i<sz;i++)
    if(arr[i]>maxe)
      maxe=arr[i];
  return maxe;
}
int main(){
    int n;
    scanf("%d", &n);
    int a[n];
    for(int i=0; i<n; i++)
      scanf("%d", &a[i]);
    int b[n]; memset(b,0,sizeof(b));
    int cnt = 1;
    b[0]--;
    int max1    = a[0];
    int max1pos = 0;
    int max2    = -2e9;
    for (int i = 1; i < n; i++) {
        if (a[i] > max1) {
            cnt++;
            b[i]--;
        }
        else if (a[i] > max2)
            b[max1pos]++;
        if (a[i] >= max1) {
            max2 = max1;
            max1 = a[i];
            max1pos = i;
        }
        else if (a[i] > max2)
            max2 = a[i];
    }
    printf("%d\n", cnt + max_element(b, n));
    return 0;
}
