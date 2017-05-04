#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

/////
int cmpInt(const void * a, const void * b)
{
    return (*(int*)a - *(int*)b);
}
int factorial(int n)
{
    int i = 1;
    while (n > 1) i *= n--;
    return i;
}
int* removeIndex(int* nums, int n, int i)
{
    int* res = malloc(sizeof(int) * (n - 1));
    memcpy(res, nums, sizeof(int) * i);
    memcpy(res + i, nums + i + 1, sizeof(int) * (n - i - 1));
    return res;
}
int** permute(int* nums, int numsSize, int* returnSize)
{
    int** res;
    if (numsSize == 1) {
        *returnSize = 1;
        res = malloc(sizeof(int*));
        res[0] = malloc(sizeof(int));
        res[0][0] = nums[0];
    }
    else {
        *returnSize = 0;
        res = malloc(sizeof(int*) * factorial(numsSize));
        int i, j;
        for (i = 0; i < numsSize; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            int* sub = removeIndex(nums, numsSize, i);
            int subSize;
            int** subPermute = permute(sub, numsSize - 1, &subSize);
            for (j = 0; j < subSize; j++, (*returnSize)++) {
                res[*returnSize] = malloc(sizeof(int) * numsSize);
                res[*returnSize][0] = nums[i];
                memcpy(res[*returnSize] + 1, subPermute[j], sizeof(int) * (numsSize - 1));
                free(subPermute[j]);
            }
            free(sub);
            free(subPermute);
        }
    }
    return res;
}
int** permuteUnique(int* nums, int numsSize, int* returnSize)
{
    qsort(nums, numsSize, sizeof(int), cmpInt);
    return permute(nums, numsSize, returnSize);
}

int main(){
    int N;
    scanf("%d", &N);
    vec v=newVec();
    for (int i = 0; i < N; ++i){
        int val;
        scanf("%d", &val);
        v.ptr=pushback(v.ptr, &v.sz, val);
    }
    int retsz;
    int**rv = permuteUnique(v.ptr, v.sz, &retsz);
    for(int i=0;i<retsz;i++){
      for(int j=0;j<N;    j++)
        printf("%d ", rv[i][j]);
      puts("");
    }
    return 0;
}























































