#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdbool.h>
#include<limits.h>


int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}
void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
}
void random_shuffle(int*gCopy, int gSize) {
    for (int i = 0;i < gSize;i++){
        int pos = rand()%(gSize-i);
        swap(gCopy, i+pos, i);
    }
}
int min_element(int*arr,int sz){
    int mine=arr[0];
    for(int i=1;i<sz;i++)
        if(arr[i]<mine)
            mine=arr[i];
    return mine;
}

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

bool match(int idx, vec v){
    return idx >= 0 && idx < v.sz;
}

int mex(vec v){
   srand(time(NULL));
   random_shuffle(v.ptr, v.sz);
   if(min_element(v.ptr, v.sz) != 0) {
       return 0;
   }
   int strip = 0;
   for (int i = 0; i < v.sz; i++) {
        if (! match(v.ptr[i], v)) {
            strip++;
            continue;
        }
        v.ptr[i - strip] = v.ptr[i];
   } 
   for (int i = 0; i < v.sz - strip; i++) {
       while (v.ptr[i] < v.sz - strip && v.ptr[i] != i && v.ptr[v.ptr[i]] != v.ptr[i]){
           swap(v.ptr, i, v.ptr[i]);
       }
   }
   int mex = 0;
   int pointer = 0;
   while (pointer < v.sz - strip) {
       while (pointer < v.sz - strip && v.ptr[pointer] < mex) {
           pointer++;
       }
       if (pointer != v.sz - strip && v.ptr[pointer] != mex) {
          return mex;
       }
       mex++;
   } 
   return mex - 1;
}
int main() {
    int N;
    scanf("%d", &N);
    vec v=newVec();
    for (int i = 0; i < N; ++i) {
        int val;
        scanf("%d", &val);
        v.ptr=pushback(v.ptr, &v.sz, val);
    }
    printf("%d\n", mex(v) );
    return 0;
}






































