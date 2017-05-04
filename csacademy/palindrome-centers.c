#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
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



vec GetOdd(int*manaher, int sz){
    vec result = newVec();
    for (int i = 0; i < sz; i+=2)
        result.ptr=pushback(result.ptr,&result.sz,manaher[i]);
    return result;
}
int main(){
    int n;
    scanf("%d", &n);
    int right[n];
    for(int i=0;i<n;i++)
        scanf("%d", &right[i]);
    int centerSz=2*n;
    int centered[centerSz];
    memset(centered,0,sizeof(centered));
    for (int i = 0; i < n; i++){
        int len = right[i];
        int r = i * 2 + 1;
        centered[r - len + 1] = max(centered[r - len + 1], len);
    }
    int id = 0;
    for (int i = 1; i < 2 * n; ++i) {
        if (id + centered[id] > i)
            centered[i] = max(centered[i], min(centered[2 * id - i], id + centered[id] - i));
        else
            centered[i] = max(centered[i], 1);
        if(i + centered[i] > id + centered[id])
            id = i;
    }
    vec a = GetOdd(centered+1, centerSz-1);
    for(int i=0;i<a.sz;i++)
        printf("%d ", a.ptr[i]);
    puts("");
    return 0;
}





















































