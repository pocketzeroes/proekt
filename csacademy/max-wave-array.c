#include <stdio.h>

int cmp(const void*pa,const void*pb){
  int*a=(int*)pa;
  int*b=(int*)pb;
  return a[0]<b[0];
}
void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
int main() {
    int n; 
    scanf("%d", &n);
    int elements[n];
    for(int i=0;i<n;i++){
      scanf("%d", &elements[i]);
    }
    qsort(elements, n,sizeof(int),cmp);
    for (int i = 1; i + 1 < n; i += 2) {
        swap(elements, i, i + 1);
    }
    for(int i=0;i<n;i++){
        int itr = elements[i];
        printf("%d ", itr);
    }
    return 0;
}
