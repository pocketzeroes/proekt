#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdbool.h>
#include<limits.h>

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
typedef long long ll;
#define repeat(cnt,l) for(int cnt=0;(cnt)<(l);++(cnt))


ll N, M, K;
ll aa[100010];
ll reci;
vec ans;
int main(){
    scanf("%lld %lld", &N, &M);
    for(int i=0;i<N;i++)
        scanf("%lld", &aa[i]);
    repeat(i, M){
        ll t, x;
        scanf("%lld", &t);
        if (t == 1){
            scanf("%lld", &x);
            --x;
            aa[x] -= 1;
            if(aa[x] < 0){
                ans.ptr = pushback(ans.ptr, &ans.sz, x);
                --reci;
                aa[x] = 0;
            }
        }
        else
            reci++;
    }
    for(int z=0;z<ans.sz;z++){int a = ans.ptr[z];
        printf("%d\n", a+1);
    }
    while(reci > 0){
        puts("1");
        --reci;
    }
    return 0;
}



