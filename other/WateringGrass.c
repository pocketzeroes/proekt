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
/////////////////////////////////////////////////////

typedef struct{
    double a, b;
    int    index;
}interval;

int cmpI(const void*pa, const void*pb){
    interval*t=(interval*)pa;
    interval*x=(interval*)pb;
    return(t->a < x->a)?-1:1;
}

double A,B,maxx;
int    n, it, best;
vec    cover;
bool   possible;

int main(){
    int    n, l;
    double r, w, x;
    while(scanf("%d %d %lf", &n, &l, &w)==3){
        interval intervals[n];
        for(int i=0; i<n; i++){
            scanf("%lf %lf", &x, &r);
            if(r >= w/2){
                double p = sqrt(r*r -w*w/4);
                intervals[i].a = x - p;
                intervals[i].b = x + p;
                intervals[i].index = i;
            }
            else{
                intervals[i].a = -1;
                intervals[i].b = -1;
                intervals[i].index = i;
            }
        }
        A = 0;
        B = l;
        qsort(intervals, n, sizeof(interval), cmpI);
        it = 0;
        cover.sz=0;
        possible = true;
        while(intervals[it].b < A){
            it++;
            if(it == n){
                possible = false;
                break;
            }
        }
        if(A == B && possible){
            if(intervals[it].a <= A && intervals[it].b >= A)
                pb(cover, intervals[it].index);
            else
                possible = false;
        }
        while(A < B && possible){
            if(it == n){
                possible = false;
                break;
            }
            maxx = -1;
            best = -1;
            while(intervals[it].a <= A){
                if(intervals[it].b - A > maxx){
                    maxx = intervals[it].b - A;
                    best = it;
                }
                it++;
                if(it == n)
                    break;
            }
            if(best == -1){
                possible = false;
                break;
            }
            pb(cover, intervals[best].index);
            A = intervals[best].b;
        }
        if(!possible)
            puts("-1");
        else
            printf("%d\n", cover.sz);
    }
    return 0;
}
