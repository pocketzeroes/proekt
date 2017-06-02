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
/////////
enum{ kMaxN =(int) 1e5+5};

vec beaten_by[kMaxN];

bool Smaller(int a, int b) {
    printf("Q %d %d", a, b);fflush(stdout);
    int x; 
    scanf("%d", &x);
    return x == a;
}
int Solve(int left, int right) {
    if (left == right) {
        return left;
    }
    int mid = (left + right) / 2;
    int a = Solve(left, mid);
    int b = Solve(mid + 1, right);
    if (Smaller(a, b)) {
        beaten_by[a].ptr = pushback(beaten_by[a].ptr, &beaten_by[a].sz ,b);
        return a;
    }
    else {
        beaten_by[b].ptr = pushback(beaten_by[b].ptr, &beaten_by[b].sz ,a);
        return b;
    }
}
int main() {
    int n; 
    scanf("%d", &n);
    int first_min = Solve(1, n);
    int second_min = beaten_by[first_min].ptr[beaten_by[first_min].sz-1];
    beaten_by[first_min].sz--;
    for(int i=0;i<beaten_by[first_min].sz;i++){int itr = beaten_by[first_min].ptr[i];
        if (Smaller(itr, second_min)) {
            second_min = itr;
        }
    }
    printf("A %d", second_min);fflush(stdout);
    return 0;
}

