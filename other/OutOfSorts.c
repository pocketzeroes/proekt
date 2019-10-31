#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int*arr;

int Bsearch(int a[], int x, int low, int high){
    if (low > high)
        return -1;
    int mid = (low+high)/2;
    if (a[mid] == x)
        return mid;
    else if (a[mid] > x)
        return Bsearch(a, x, low, mid-1);
    else
        return Bsearch(a, x, mid+1, high);
}
int main(){
    long n, m, a, c, x;
    scanf("%ld %ld %ld %ld %ld", &n, &m, &a, &c, &x);
    arr = calloc(n, sizeof(int));
    for(int i=0; i<n; i++){
        arr[i] = (a*x + c)%m;
        x = arr[i];
    }
    int foundCount = 0;
    for(int i=0; i<n; i++){
        int loc = Bsearch(arr, arr[i], 0, n-1);
        if (loc != -1){
            foundCount++;
            if(loc != i)
                fprintf(stderr, "duplicate in array\n");
        }
    }
    printf("%d\n", foundCount);
    return 0;
}
