#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


int cmp(const void*pa,const void*pb){
  int*a=(int*)pa;
  int*b=(int*)pb;
  return a[0]-b[0];
}
int main() {
int max_element(int*arr,int sz){
    int maxe=arr[0];
    for(int i=1;i<sz;i++)
        if(arr[i]>maxe)
            maxe=arr[i];
    return maxe;
}
    int n; 
    scanf("%d",&n);
    int elements[n];
    int best    [n];
    memset(best,0,sizeof(best));
    for (int i = 0; i < n; i += 1) {
        scanf("%d", &elements[i]);
    }
    qsort(elements, n,sizeof(int),cmp);
    for (int i = 0; i < n; i += 1) {
        int current_best = 0;
        for (int j = 0; j < i; j += 1) {
            if (elements[i] % elements[j] == 0 && current_best < best[j]) {
                current_best = best[j];
            }
        }
        best[i] = current_best + 1;
    }
    printf("%d", max_element(best, n));
    return 0;
}
