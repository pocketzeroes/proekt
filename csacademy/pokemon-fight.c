#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

int cmp(const void*pa,const void*pb){
  int*a=(int*)pa;
  int*b=(int*)pb;
  return a[0]-b[0];
}
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n];
    int b[m];
    for (int i = 0; i < n; i += 1) 
        scanf("%d", &a[i]);
    for (int j = 0; j < m; j += 1) 
        scanf("%d", &b[j]);
    qsort(a,n,sizeof(int),cmp);
    qsort(b,m,sizeof(int),cmp);
    bool selected[n];
    memset(selected,0,sizeof(selected));
    int indexA = 0;
    bool ok = true; 
    for (int i = 0; i < m; i += 1) {
        while (indexA < n && a[indexA] <= b[i]) 
            indexA += 1;
        if (indexA == n) {
            ok = false;
            break;
        }
        selected[indexA] = true;
        indexA += 1;
    }
    if (ok == false) {
        puts("-1");
        return 0;
    }
    long long sum = 0;
    for (int i = 0; i < n; i += 1) 
        if (selected[i] == false) 
            sum += a[i];
    printf("%lld", sum);
    return 0;
}
