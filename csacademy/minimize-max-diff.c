#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

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

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    int initial_elements[n];
    for (int i = 0; i < n; i += 1) {
        scanf("%d", &initial_elements[i]);
    }
    int elements_size=n-1;
    int elements[elements_size];
    for (int i = 0; i + 1 < n; i += 1) {
        elements[i] = initial_elements[i + 1] - initial_elements[i];
    }
    int num_selected = n - 1 - k;
    int answer = 1e9;
    int left = 0;
    vec stack=newVec();
    for (int i = 0; i < elements_size; i += 1) {
        if (stack.sz && stack.ptr[left] + num_selected == i) {
            left += 1;
        }
        while ( stack.sz > left && elements[stack.ptr[stack.sz-1]] <= elements[i]) {
            stack.sz--;
        }
        stack.ptr=pushback(stack.ptr, &stack.sz ,i);
        int now = elements[stack.ptr[left]];
        if (i + 1 >= num_selected) {
            answer = min(now, answer);
        }
    }
    printf("%d\n", answer);
    return 0;
}








