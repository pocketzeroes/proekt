#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}

int n;
int*perm=NULL;int permSz=0;

void read() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int val;
        scanf("%d", &val);
        perm=pushback(perm,&permSz,val);
    }
}
int main() {
    read();
    int i;
    for (i = n - 2; i >= 0; --i) {
        if (perm[i] > perm[i + 1]) {
            break;
        }
    }
    if (i == -1) {
        puts("-1");
        return 0;
    }
    int swapPos = i + 1;
    while (swapPos + 1 < n && perm[swapPos + 1] < perm[i]) {
        ++swapPos;
    }
    swap(perm, i, swapPos);
    int left = i + 1, right = n - 1;
    while (left < right){
        swap(perm, left, right);
        left ++;
        right--;
    }
    for (int i = 0; i < n; ++i) {
        printf("%d ", perm[i]);
    }
}
