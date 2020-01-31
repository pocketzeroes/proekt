#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
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
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
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
//////////////////////////////////////////

vec LIS(int*v, int vsz){
    int p[vsz]; fill(p, vsz, -1);
    int t[vsz]; clr(t);
    int lis=1;
    for(int i=1; i<vsz; i++){
        if(v[i]<=v[t[0]])
            t[0] = i;
        else if(v[i]>v[t[lis - 1]]){
            p[i] = t[lis - 1];
            t[lis++] = i;
        }
        else{
            int l = -1;
            int r = lis - 1;
            while(r - l > 1){
                int m = l + (r - l) / 2;
                if(v[t[m]] >= v[i])
                    r = m;
                else
                    l = m;
            }
            p[i] = t[r - 1];
            t[r] = i;
        }
    }
    vec ans = newVec();
    for(int i=t[lis-1]; i>=0; i=p[i])
       pb(ans, i);
    reverse(ans.ptr, 0, ans.sz-1);
    return ans;
}
int main(){
    int n;
    while(scanf("%d", &n)==1){
        int arr[n];
        for(int i=0; i<n; ++i)
            scanf("%d", &arr[i]);
        vec lis = LIS(arr, n);
        printf("%d\n", lis.sz);
        for(int z=0;z<lis.sz;z++)
            printf("%d ", lis.ptr[z]);
        puts("");
    }
    return 0;
}
