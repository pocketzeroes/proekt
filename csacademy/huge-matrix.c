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


#define MaxN 100100

int freq[MaxN], numDif = 1, maxDif = 1;
vec del[MaxN], add[MaxN];

void incremFreq(int val, int delta) {
    int oldDif = !!freq[0] + !!freq[val];
    freq[val] += delta;
    freq[0] -= delta;
    numDif += !!freq[0] + !!freq[val] - oldDif;
}
int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        int st, fn, val;
        scanf("%d %d %d", &st, &fn, &val);
        add[st].ptr = pushback(add[st].ptr, &add[st].sz, val);
        del[fn].ptr = pushback(del[fn].ptr, &del[fn].sz, val);
    }
    freq[0] = N;
    for (int col = 1; col <= M; col++){
        for(int i=0;i<add[col].sz;i++){int val = add[col].ptr[i];
            incremFreq(val, 1);
        }
        if(numDif > maxDif){
            maxDif = numDif;
        }
        for(int i=0;i<del[col].sz;i++){int val = del[col].ptr[i];
            incremFreq(val, -1);
        }
    }
    printf("%d\n", maxDif);
    return 0;
}























































