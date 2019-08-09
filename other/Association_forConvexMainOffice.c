#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define copyVec(best, vis) do{ \
                if(best.ptr)free(best.ptr); \
                best.sz = vis.sz;\
                best.ptr = calloc(vis.sz, sizeof(pt)); \
                for(int i=0; i<vis.sz; i++) \
                    best.ptr[i] = vis.ptr[i]; \
}while(0)

enum{ MAXN = 500000};
typedef long long ll;

int N;
int stk[MAXN], scnt;

typedef struct{
    int x, y;
}pt;
pt A[MAXN];
void swap(pt*nums, int i, int j) {
   pt t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(pt*nums, int start, int end){
    while( start < end){
        swap(nums, start, end);
        start++;
        end  --;
    }
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pt*pushbackPt(pt*array, int *size, pt value){
    pt*output = resizeArray(array, pt, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	pt*ptr;
	int sz;
}vecpt;
vecpt newVecPt(){
	vecpt rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
///////////////////////////

int ccw6(int ax, int ay, int bx, int by, int cx, int cy){
    ll k = (ll)(bx - ax) * (cy - ay) - (ll)(cx - ax) * (by - ay);
    if (k > 0)
        return 1;
    if (k)
        return -1;
    return 0;
}
int ccw(pt a, pt b, pt c){
    return ccw6(a.x, a.y, b.x, b.y, c.x, c.y);
}
int gcd(int a, int b){
    return b ? gcd(b, a%b) : a;
}
int cmpPt1(const void*pa, const void*pb){
    pt*a=(pt*)pa;
    pt*b=(pt*)pb;
    return(a->x+a->y < b->x+b->y)?-1:1;
}
int cmpPt2(const void*pa, const void*pb){
    pt*a=(pt*)pa;
    pt*b=(pt*)pb;
    return((ll)a->y*b->x < (ll)b->y*a->x)?-1:1;
}
int cmpPt3(const void*pa, const void*pb){
    pt*aa=(pt*)pa;
    pt*bb=(pt*)pb;
    pt a=*aa;
    pt b=*bb;
    int k = ccw(A[1], a, b);
    if (k)
        return(k > 0)?-1:1;
    return(llabs(a.x-A[1].x)+llabs(a.y-A[1].y) < llabs(b.x-A[1].x)+llabs(b.y-A[1].y))?-1:1;
}
int main(){
    vecpt frac = newVecPt();
    for (int i=2;i<999;i++){
        for (int j=1;j<i;j++){
            if (gcd(i, j) == 1)
                frac.ptr = pushbackPt(frac.ptr, &frac.sz, (pt){i, j});
        }
    }
    qsort(frac.ptr, frac.sz, sizeof(pt), cmpPt1);
    int sum = 0;
    vecpt lst = newVecPt();
    for(int q=0;q<frac.sz;q++){pt z = frac.ptr[q];
        sum += z.x + z.y;
        if(sum > 20000000)
            break;
        lst.ptr = pushbackPt(lst.ptr, &lst.sz, z);
    }
    qsort(lst.ptr, lst.sz, sizeof(pt), cmpPt2);
    vecpt lst2 = newVecPt();
    copyVec(lst2, lst);
    reverse(lst2.ptr, 0, lst2.sz-1);
    int x = 20000000, y = 0;
    for(int q=0;q<lst .sz;q++){pt z=lst .ptr[q]; A[++N] =(pt){x, y}; x += z.x, y += z.y;}
    for(int q=0;q<lst2.sz;q++){pt z=lst2.ptr[q]; A[++N] =(pt){x, y}; x += z.y, y += z.x;}
    for(int q=0;q<lst .sz;q++){pt z=lst .ptr[q]; A[++N] =(pt){x, y}; x -= z.y, y += z.x;}
    for(int q=0;q<lst2.sz;q++){pt z=lst2.ptr[q]; A[++N] =(pt){x, y}; x -= z.x, y += z.y;}
    for(int q=0;q<lst .sz;q++){pt z=lst .ptr[q]; A[++N] =(pt){x, y}; x -= z.x, y -= z.y;}
    for(int q=0;q<lst2.sz;q++){pt z=lst2.ptr[q]; A[++N] =(pt){x, y}; x -= z.y, y -= z.x;}
    for(int q=0;q<lst .sz;q++){pt z=lst .ptr[q]; A[++N] =(pt){x, y}; x += z.y, y -= z.x;}
    for(int q=0;q<lst2.sz;q++){pt z=lst2.ptr[q]; A[++N] =(pt){x, y}; x += z.x, y -= z.y;}
    for(int i=2; i<=N; i++)
        if (A[1].y > A[i].y || A[1].y == A[i].y && A[1].x > A[i].x)
            swap(A, 1, i);
    qsort(A+2, N+1-2, sizeof(pt), cmpPt3);
    stk[scnt=1] = 1;
    for (int i=2;i<=N;i++){
        while (scnt > 1 && ccw(A[stk[scnt-1]], A[stk[scnt]], A[i]) <= 0) 
            scnt--;
        stk[++scnt] = i;
    }
    if (N != scnt) 
        return 0;
    scanf("%d", &N);
    for (int i=1;i<=N;i++)
        printf("%d %d\n", A[i].x, A[i].y);
    return 0;
}
