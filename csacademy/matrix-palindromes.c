#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

#define MAX_INT   2147483647
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
char buff[100000];
int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    char* a[n];
    for (int i = 0; i < n; i++) {
        scanf("%s", &buff);
        a[i] = strdup(buff);
    }
    int costSz = ((m + 1) / 2);
    vec cost = newVec();
    for(int i=0; i<costSz; i++)
        cost.ptr = pushback(cost.ptr, &cost.sz, 0);
    int res = 0;
    for (int i = 0; i < (n + 1) / 2; i++){
        for (int j = 0; j < (m + 1) / 2; j++){
            int ii = n - 1 - i;
            int jj = m - 1 - j;
            bool o1 = false, o2 = false;
            if (a[i][j] != a[i][jj]){
                o1 = true;
                res++;
            }
            if (i != ii && a[ii][j] != a[ii][jj]){
                o2 = true;
                res++;
            }
            if (i != ii){
                if(a[i][j] == a[ii][j] || a[i][j] == a[ii][jj] || a[i][jj] == a[ii][j] || a[i][jj] == a[ii][jj])
                    ;
                else{
                    if (o1 || o2 || j == jj)
                        cost.ptr[j]++;
                    else
                        cost.ptr[j] += 2;
                }
            }
        }
    }
    if (m % 2 == 1){
        int cost1 = cost.ptr[cost.sz - 1];
        cost.sz--;
        qsort(cost.ptr, cost.sz, sizeof(int), cmp);
        int s1 = 0;
        if (k == m)
            s1 = MAX_INT;
        else {
            for(int i = 0; i < (k + 1) / 2; i++)
                s1 += cost.ptr[i];
        }
        int s2 = cost1;
        for(int i = 0; i < k / 2; i++)
            s2 += cost.ptr[i];
        res += min(s1, s2);
    }
    else{
        qsort(cost.ptr, cost.sz, sizeof(int), cmp);
        for (int i = 0; i < (k + 1) / 2; i++)
            res += cost.ptr[i];
    }
    printf("%d\n", res);
    return 0;
}






