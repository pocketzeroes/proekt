#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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


typedef struct{
    int x, y;
}pt;
int dist(pt p1, pt p2){
    int d1 = (p1.x-p2.x);
    int d2 = (p1.y-p2.y);
    return d1*d1+d2*d2;
}
bool colinear(pt p1, pt p2, pt p3){
    int a = p1.x * (p2.y - p3.y) +
            p2.x * (p3.y - p1.y) +
            p3.x * (p1.y - p2.y);
    return(a == 0);
}
void solve(){
    pt p1, p2, p3;
    scanf("%d%d", &p1.x, &p1.y);
    scanf("%d%d", &p2.x, &p2.y);
    scanf("%d%d", &p3.x, &p3.y);
    if(colinear(p1, p2, p3)){
        puts("not a triangle");
        return;
    }
    vec d=newVec();
    pb(d, dist(p1,p2));
    pb(d, dist(p3,p2));
    pb(d, dist(p1,p3));
    qsort(d.ptr, d.sz, sizeof(int), cmp);
    bool isoceles = false;
    if(d.ptr[0] == d.ptr[1] || d.ptr[1] == d.ptr[2])
        isoceles = true;
    if(isoceles)
        printf("isosceles ");
    else
        printf("scalene ");

    if(d.ptr[0] + d.ptr[1] == d.ptr[2])
        printf("right ");
    if(d.ptr[0] + d.ptr[1] > d.ptr[2])
        printf("acute ");
    if(d.ptr[0] + d.ptr[1] < d.ptr[2])
        printf("obtuse ");
    puts("triangle");
}
int main(){
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
