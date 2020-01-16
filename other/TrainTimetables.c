#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}

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


#define REP(i,n) for (int i = 0; i < (n); i++)
#define REPD(i,n) for (int i = (n) - 1; i >= 0; i--)

int t;

int stime(){
    int h, m;
    scanf("%d:%d", &h, &m);
    return 60 * h + m;
}
int reduce(vec*arr, vec*dep){
    qsort(arr->ptr, arr->sz, sizeof(int), cmp);
    qsort(dep->ptr, dep->sz, sizeof(int), cmp);
    int n = arr->sz,
        m = dep->sz;
    bool used[n]; clr(used);
    int res = 0;
    REPD(j, m){
        REPD(i, n)
            if(!used[i] && arr->ptr[i] + t <= dep->ptr[j]){
                res++;
                used[i] = true;
                break;
            }
    }
    return res;
}
int main(){
    int zzz;
    scanf("%d", &zzz);
    REP(zz, zzz){
        int na, nb;
        scanf("%d %d %d", &t, &na, &nb);
        vec depa = newVec();
        vec depb = newVec();
        vec arra = newVec();
        vec arrb = newVec();
        REP(i, na){
            pb(depa, stime());
            pb(arrb, stime());
        }
        REP(i, nb){
            pb(depb, stime());
            pb(arra, stime());
        }
        printf("Case #%d: %d %d\n", zz+1, na - reduce(&arra, &depa), nb - reduce(&arrb, &depb));
    }
    return 0;
}
