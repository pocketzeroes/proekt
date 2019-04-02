#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
}
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
int cmpR(const void *b, const void *a){//rev
   return ( *(int*)a - *(int*)b );
}
int gcd(int u, int v){
  return v != 0?gcd(v, u%v):u;
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
void erase(int*v, int vsz, int pos){
    for(int i=pos; i < vsz-1; i++)
        v[i] = v[i+1];
}
//////////////////////////

int*bot ; int botSz;
int*ebot; int ebotSz;
int*has ; int hasSz;
vec w;
int T;


int N(int x){
    return w.ptr[x] + 1;
}
int dispose(int x){
    int ret = has[x];
    printf("transfer %d 0\n", N(x));
    has[x] = 0;
    T -= ret;
    return ret;
}
int transfer(int from, int to){
    int cantransfer = min(has[from], bot[to] - has[to]);
    printf("transfer %d %d\n", N(from), N(to));
    has[from] -= cantransfer;
    has[to  ] += cantransfer;
    return cantransfer;
}
int fill(int x){
    printf("fill %d\n", N(x) );
    has[x] = bot[x];
    return bot[x];
}
void discard(int x){
    printf("discard %d\n", N(x) );
    has[x] = 0;
}
int fillBottle(int x){
    if(x == botSz - 1)
        return fill(x);
    discard(x + 1);
    fillBottle(x + 1);
    while (true && T){
        transfer(x + 1, x);
        if (has[x] && has[x] <= T)
            return dispose(x);
        if (has[x] == ebot[x])
            return ebot[x];
        if (has[x] == bot[x])
            discard(x);
        if (!has[x + 1])
            fillBottle(x + 1);
    }
    return 0;
}
int cmpI(const void*pa, const void*pb){
    int*a=(int*)pa;
    int*b=(int*)pb;
    return(bot[*a] > bot[*b])?-1:1;
}
int main(){
    int N;
    scanf("%d", &N);
    hasSz=ebotSz=botSz = N;
    int idx[N];
    for(int i=0;i<N;i++)
        idx[i]=i;
    bot =calloc(N, sizeof(int));
    ebot=calloc(N, sizeof(int));
    has =calloc(N, sizeof(int));
    for(int i = 0; i<N; ++i)
      scanf("%d", &bot[i]);
    qsort(idx, N, sizeof(int), cmpI);
    qsort(bot, N, sizeof(int), cmpR);//rev
    ebot[N - 1] = bot[N - 1];
    w.ptr = pushback(w.ptr, &w.sz, idx[N-1]);
    for(int i = N - 2; i >= 0; --i){
        ebot[i] = gcd(bot[i], ebot[i + 1]);
        if (ebot[i] == ebot[i + 1]){
            erase(bot , botSz , i);  botSz--;
            erase(ebot, ebotSz, i); ebotSz--;
            erase(has , hasSz , i);  hasSz--;
            --N;
        }
        else{
            w.ptr = pushback(w.ptr, &w.sz, idx[i]);
        }
    }
    reverse(bot, 0, botSz-1);
    ebot[N - 1] = bot[N - 1];
    w.ptr = pushback(w.ptr, &w.sz, idx[N-1]);
    for(int i = N - 2; i >= 0; --i){
        ebot[i] = gcd(bot[i], ebot[i + 1]);
    }
    scanf("%d", &T);
    if(T % ebot[0])
        puts("impossible");
    else{
        while(T){
            fillBottle(0);
            dispose(0);
        }
    }
    return 0;
}
