#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int cmp(const void * a, const void * b){   return ( *(int*)a - *(int*)b );}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int scores[] = {100,75,60,50,45,40,36,32,29,26,24,22,20,18,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
int prefixSum[31];

int computeScore(int r1, int r2){
    int sum = prefixSum[(int)fmin(30, r2)]-prefixSum[(int)fmin(30, r1)];
    int num = r2-r1;
    return (sum + num - 1) / num + 1;
}
int main(){
    for (int i = 1; i <= 30; i++)
        prefixSum[i] = prefixSum[i-1] + scores[i-1];
    int n, m;
    scanf("%d %d", &n, &m);
    int s[m][n-1];
    for(int i = (0); i < (int)(m); ++i){
        for(int j = (0); j < (int)(n-1); ++j)
            scanf("%d", &s[i][j]);
        qsort(s[i], n-1, sizeof(int), cmp);
    }
    int myScore = 0;
    for(int j = (0); j < (int)(fmin(n-1, 4)); ++j)
        myScore += s[0][n-2-j];
    vec required = newVec();
    for(int i=1; i < m; ++i){
        int currentScore = 0;
        for(int j = (0); j < (int)(fmin(n-1, 4)); ++j)
            currentScore += s[i][n-2-j];
        if (currentScore > myScore)
            required.ptr = pushback(required.ptr, &required.sz, 0);
        else {
            currentScore = 0;
            for(int j = (0); j < (int)(fmin(n-1, 3)); ++j)
                currentScore += s[i][n-2-j];
            required.ptr = pushback(required.ptr, &required.sz, 1 + myScore - currentScore);
        }
    }
    qsort(required.ptr, required.sz, sizeof(int), cmp);
    int lo = 0;
    int hi = m;
    while (hi > lo + 1) {
        int mid = (hi + lo) / 2;
        bool dp[mid]; clr(dp);
        for (int i = 0; i < mid; i++){
            int position = mid - i - 1;
            if(required.ptr[i] <= computeScore(position, mid))
                dp[i] = true;
            if(!dp[i])
                continue;
            for(int j = mid - 1; j > i; --j){
                if(required.ptr[j] <= computeScore(mid - j - 1, position))
                    dp[j] = true;
                if(computeScore(mid - j - 1, position) == 1)
                    break;
            }
        }
        if(dp[mid-1])
            lo = mid;
        else
            hi = mid;
    }
    printf("%d\n", 1 + lo);
    return 0;
}
