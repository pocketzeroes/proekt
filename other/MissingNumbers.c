#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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


int main(){
    int n, c, d;
    vec v = newVec();
    scanf("%d", &n);
    int last;
    bool skipped = false;
    for(int i=0; i<n; i++){
        scanf("%d", &c);
        if(i == 0){
            for(int j=1; j<c; j++)
                pb(v, j);
        }
        else{
            for(int j=last+1; j<c; j++)
                pb(v, j);
        }
        last = c;
    }
    if(v.sz==0){
        puts("good job");
        return 0;
    }
    for(int z=0; z<v.sz; z++){int i = v.ptr[z];
        printf("%d\n", i);
    }
    return 0;
}
