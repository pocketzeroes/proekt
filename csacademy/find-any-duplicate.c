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
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


int findDuplicate(vec v){
    int N = v.sz;
    int r = N - 1;
    int t = N - 1;
    do {
        r = v.ptr[r] - 1;
        r = v.ptr[r] - 1;
        t = v.ptr[t] - 1;
    } 
    while (r != t);
    t = N - 1;
    while (r != t) {
        r = v.ptr[r] - 1;
        t = v.ptr[t] - 1;
    }
    return t + 1;
}

int main() {
    int N;
    scanf("%d", &N);
    vec v=newVec();
    for (int i = 0; i <= N; ++i){
        int val;
        scanf("%d", &val);
        v.ptr=pushback(v.ptr, &v.sz,val);
    }
    printf("%d\n", findDuplicate(v) );
    return 0;
}



