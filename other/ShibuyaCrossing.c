#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int max_element(int*arr, int sz){
  int maxe=arr[0];
  for(int i=1;i<sz;i++)
    if(arr[i]>maxe)
      maxe=arr[i];
  return maxe;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int pos[n];
    for(int i=0; i<n; ++i)
        pos[i] = i;
    for(int i=0; i<m; ++i){
        int a, b;
        scanf("%d %d", &a, &b);
        a--, b--;
        if(a > b)
            swap(a, b);
        pos[a]++;
        pos[b]--;
    }
    int best[n]; fill(best, n, 1);
    for(int i=1; i<n; ++i)
        for(int j=0; j<i; ++j)
            if (pos[j] > pos[i])
                best[i] = fmax(best[i], best[j]+1);
    printf("%d\n", max_element(best, n) );
    return 0;
}
