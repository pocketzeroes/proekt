/*
test 16 not ok
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdint.h>
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

  
int32_t cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}  

int n1, n2;

vec first ;
vec second;
vec ans;
    
void read(){
    scanf("%d %d", &n1, &n2);
    for (int i = 0; i < n1; ++i) {
        int val;
        scanf("%d", &val);
        first.ptr=pushback(first.ptr, &first.sz, val);
    }
    for (int i = 0; i < n2; ++i) {
        int val;
        scanf("%d", &val);
        second.ptr=pushback(second.ptr, &second.sz, val);
    }
}
void arrayIntersection(vec f, vec s){
    int i = 0, j = 0;
    while (i < f.sz && j < s.sz){
        if      (f.ptr[i] > s.ptr[j]) j++;
        else if (f.ptr[i] < s.ptr[j]) i++;
        else {
            ans.ptr=pushback(ans.ptr, &ans.sz, f.ptr[i]);
            i++; j++;
        }
    }
}
int32_t main() {
    read();
    qsort(first.ptr,  first.sz,  sizeof(int), cmp);
    qsort(second.ptr, second.sz, sizeof(int), cmp);
    arrayIntersection(first, second);
    printf("%d\n", ans.sz);
    for(int i=0;i<ans.sz;i++)
        printf("%d ", ans.ptr[i]);
    puts("");
}

































