#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

vec dg;
vec num;
ll res[20][2];

ll dp(int id, bool isLess){
    if(id == num.sz) 
        return isLess;
    if(res[id][isLess] != -1) 
        return res[id][isLess];
    ll w = 0;
    for(int z=0;z<dg.sz;z++){int d = dg.ptr[z];
        if(!isLess && d > num.ptr[id]) 
            break;
        w += dp(id+1, isLess || d < num.ptr[id]);
    }
    return res[id][isLess] = w;
}
int main(){
    memset(res, -1, sizeof(res));
    for(int i=0; i<10; i++){
        int t;
        scanf("%d", &t);
        if(!t)
            dg.ptr = pushback(dg.ptr, &dg.sz, i);
    }
    ll n;
    scanf("%lld", &n);
    while(n){
        num.ptr = pushback(num.ptr, &num.sz, n%10);
        n /= 10;
    }
    reverse(num.ptr, 0, num.sz-1);
    ll anw = dp(0, 0);
    bool hasZ = dg.sz && dg.ptr[0] == 0;
    if(!hasZ){
        for(int i=1; i < num.sz; i++) 
            anw += dp(i, 1);
    }
    printf("%lld\n", anw);
    return 0;
}
