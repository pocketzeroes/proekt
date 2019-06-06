#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}

int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int unique(int*a, int len){
	int i, j;
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j])
            a[++j] = a[i];
	return j + 1;
}

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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
//////////////////////////////
enum{ infty = 1000000000};
enum{ maxn  =        300};
int A[maxn],
    B[maxn],
    H[maxn];
int sol[2*maxn+2][2*maxn+2];

int main(){
    int TT;
    scanf("%d", &TT);
    while(TT--){
        int n;
        scanf("%d", &n);
        vec ends = newVec();
        for(int i=0; i<n; i++){
            scanf("%d %d %d", &A[i], &B[i], &H[i]);
            ends.ptr = pushback(ends.ptr, &ends.sz, A[i]);
            ends.ptr = pushback(ends.ptr, &ends.sz, B[i]);
        }
        ends.ptr = pushback(ends.ptr, &ends.sz, -infty);
        ends.ptr = pushback(ends.ptr, &ends.sz, +infty);
        qsort(ends.ptr, ends.sz, sizeof(int), cmp);
        ends.sz = unique(ends.ptr, ends.sz);
        int k = ends.sz;
        for(int d = 1; d < k; d++){
            for(int i = 0; i + d < k; i++){
                int j = i+d;              
                int highest = -1;
                for(int q = 0; q < n; q++)
                    if ((A[q] > ends.ptr[i]) && (B[q] < ends.ptr[j]) && (highest == -1 || H[q] > H[highest]))
                        highest = q;
                if (highest == -1)
                    sol[i][j] = 0;
                else{
                    sol[i][j] = infty;                          
                    int hleft = 0;
                    while (ends.ptr[hleft] != A[highest])           
                        hleft++;
                    int hright = 0;
                    while (ends.ptr[hright] != B[highest])          
                        hright++;                               
                    for(int q = hleft; q <= hright; q++)        
                        sol[i][j] = min(sol[i][j], H[highest] + sol[i][q] + sol[q][j]);   
                }
            }
        }
        printf("%d\n", sol[0][k-1]);
    }
    return 0;
}
