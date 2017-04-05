#include <stdio.h>
#include<stdlib.h>
int cmp(const void*pa,const void*pb){
  int*a=(int*)pa;
  int*b=(int*)pb;
  return a[0]-b[0];
}

int main() {
    int n; 
    scanf("%d", &n);
    int*els=malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        scanf("%d", els+i);
    }
    qsort(els, n, sizeof(int), cmp);
    long long answer = 0;
    for (int left = 0; left < n; left += 1) {
        int right = left + 1;
        for (int mid = left + 1; mid < n; mid += 1) {
            while (right < n && els[right] < els[left] + els[mid]) {
                right += 1;    
            }
            answer += right - mid - 1;
        }
    }
    printf("%d\n", answer);
    return 0;
}

