#pragma GCC optimize "-O3"
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


#define FOR(i,a,b) for(int i=a;i<(int)(b);i++)

void pi(int i, int N){
    FOR(n,0,N) {
        printf("%c%c", (i&7)+'1', n == N-1 ? '\n' : ' ');
        i >>= 3;
    }
}
int swp(int cur, int i){
    int p1 = (cur >> 3*i) & 7,
        p2 = (cur >> 3*(i+1)) & 7;
    cur &= ~(0b111111 << 3*i);
    cur |= p1 << 3*(i+1);
    cur |= p2 << 3*i;
    return cur;
}
vec sv(int n){
    if(n == 0){
        vec rv = newVec();
        pb(rv, 0);
        return rv;
    }
    bool left = true;
    vec ans = newVec();
    vec svrv = sv(n-1);
    for(int z=0;z<svrv.sz;z++){int x = svrv.ptr[z];
        x = left ? x | n<<3*n : x << 3 | n;
        pb(ans, x);
        for(int i = left ? n-1 : 0; i >= 0 && i < n; left ? i-- : i++){
            x = swp(x, i);
            pb(ans, x);
        }
        left = !left;
    }
    return ans;
}
int main(){
    int N;
    scanf("%d", &N);
    vec svrv = sv(N-1);
    for(int z=0;z<svrv.sz;z++){int x = svrv.ptr[z];
        pi(x, N);
    }
    return 0;
}
