#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>


#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}

int main(){
    int n;
    scanf("%d", &n);

    int*aux=NULL;int auxSz=0;
    long long fib[70];
    fib[1]=fib[2]=1;
    for(int i=3;i<70;i++)
        fib[i]=fib[i-1]+fib[i-2];
    for(int i=69;i>0;i--)
        if(fib[i]<=n)
            n-=fib[i], aux=pushback(aux, &auxSz, fib[i]);
    int p=auxSz-1;
    for(int i=0;i<p;i++,p--)
        swap(aux, i, p);

    for (int i = 0; i < auxSz; ++ i){
        printf("%d ", aux[i]);
    }
    puts("");
    return 0;
}
