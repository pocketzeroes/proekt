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



bool next_perm(vec v)
{
    int n = v.sz;
    bool used[n + 2];
    for (int i = 1; i <= n + 1; ++ i)
        used[i] = 1;
    int i = n - 1;
    for (; i >= 0 && used[v.ptr[i] + 1]; -- i)
        used[v.ptr[i]] = 0;
    if (i >= 0)
    {
        used[v.ptr[i]] = 0;
        ++ v.ptr[i];
        used[v.ptr[i]] = 1;
       for (int j = 1; j <= n; ++ j)
       if (!used[j])
       v.ptr[++ i] = j;
       return 1;
    }
    return 0;
}

void allBstPreorders(int N) {
    vec v = newVec();
    for (int i = 1; i <= N; ++ i)
        v.ptr=pushback(v.ptr, &v.sz, i);
    do
    {
        for (int i = 0; i < N; ++ i)
            printf("%d ", v.ptr[i]);
        printf("\n");
    }
    while (next_perm(v));
}
   
int main() {
    int N;
    scanf("%d", &N);
    allBstPreorders(N);
    return 0;
}
