#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void*a, const void*b){ return ( *(int*)a - *(int*)b );}
void swap(int*nums, int i, int j){ int t   = nums[i]; nums[i] = nums[j]; nums[j] = t;}
int N, P;
int A[99];
 
int main(){
    scanf("%d %d", &N, &P);
    for (int i=0;i<N;i++)
        scanf("%d", A+i);
    swap(A, 0, P);
    qsort(A+1, N-1, sizeof(int), cmp);
    int sum = 0, cnt = 0, ans = 0;
    for(int i=0;i<N;i++){
        sum += A[i];
        if(sum > 300)
            break;
        cnt++;
        ans += sum;
    }
    printf("%d %d\n", cnt, ans);
}
