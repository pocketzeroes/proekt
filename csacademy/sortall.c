#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int*pushback(int *array, int *size, int value){
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
int upper_bound(int*a, int n, int x){
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x >= a[mid])
            l = mid + 1;
        else
            h = mid;
    }
    return l;
}
int lower_bound(int*a, int n, int x){
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x <= a[mid]) 
            h = mid;
        else
            l = mid + 1;
    }
    return l;
}
int cmp (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int unique(int *a, int len)
{
	int i, j;
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j]) a[++j] = a[i];
	return j + 1;
}
/////////////////////////////

typedef long long ll;
enum{ N =(int)5e4 + 7};
enum{ M =(int)1e9 + 7};


int x[N];
int a[N];
int n;
int sum = 0;
vec t [N];
int*f1[N];
int*f2[N];
int*f3[N];
int*f4[N];

inline int add(int a, int b){
    a += b;
    if (a >= M) 
        a -= M;
    if (a < 0) 
        a += M;
    return a;
}
inline int mul(int a, int b){
    return (a * (ll) b) % M;
}
void ad(int x, int y){
    for (; x < N; x = (x | (x + 1))){
        t[x].ptr = pushback(t[x].ptr, &t[x].sz, y);
    }
}
void build(){
    for (int i = 0; i < N; i++){
        qsort(t[i].ptr, t[i].sz, sizeof(int), cmp);
        t[i].sz=unique(t[i].ptr, t[i].sz);
        f1[i]=calloc(t[i].sz, sizeof(int));
        f2[i]=calloc(t[i].sz, sizeof(int));
        f3[i]=calloc(t[i].sz, sizeof(int));
        f4[i]=calloc(t[i].sz, sizeof(int));
    }
}
void inc(int X, int y, int T){
    for (int x = X; x < N; x = (x | (x + 1))){
        int ind = lower_bound(t[x].ptr, t[x].sz, y);
        for (; ind < (int) t[x].sz; ind = (ind | (ind + 1))){
            if (T == 0){
                f1[x][ind] = add(f1[x][ind], X);
                f2[x][ind] = add(f2[x][ind], mul(X, y));
                f3[x][ind] = add(f3[x][ind], 1);
                f4[x][ind] = add(f4[x][ind], y);
            }
            else{
                f1[x][ind] = add(f1[x][ind], -X);
                f2[x][ind] = add(f2[x][ind], -mul(X, y));
                f3[x][ind] = add(f3[x][ind], -1);
                f4[x][ind] = add(f4[x][ind], -y);
            }
        }
    }
}
int get3(int x, int y, int id){
    int ans = 0;
    for (; x >= 0; x = (x & (x + 1)) - 1){
        int ind = upper_bound(t[x].ptr, t[x].sz, y);
        ind--;
        for (; ind >= 0; ind = (ind & (ind + 1)) - 1){
            if (id == 1) ans = add(ans, f1[x][ind]);
            if (id == 2) ans = add(ans, f2[x][ind]);
            if (id == 3) ans = add(ans, f3[x][ind]);
            if (id == 4) ans = add(ans, f4[x][ind]);
        }
    }
    return ans;
}
int get5(int x1, int x2, int y1, int y2, int ind){
    return add(add(add(get3(x2, y2, ind), -get3(x1 - 1, y2, ind)), -get3(x2, y1 - 1, ind)), get3(x1 - 1, y1 - 1, ind));
}
int get1(int ind){
    int ans = mul(x[ind], ind);
    ans = add(ans, mul(ind, get5(0, x[ind], 1, ind - 1, 1)));
    ans = add(ans, mul(mul(x[ind], ind), get5(x[ind] + 1, n, 1, ind - 1, 3)));
    ans = add(ans, get5(0, x[ind], ind + 1, n, 2));
    ans = add(ans, mul(x[ind], get5(x[ind] + 1, n, ind + 1, n, 4)));
    return ans;
}
void ch(int ind, int val){
    sum = add(sum, -get1(ind));
    inc(x[ind], ind, 1);
    x[ind] = val;
    inc(x[ind], ind, 0);
    sum = add(sum, get1(ind));
}
int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        ad(i, a[i]);
    }
    for (int i = 1; i <= n; i++)
        ad(0, i);
    build();
    for (int i = 1; i <= n; i++)
        inc(0, i, 0);
    int ans = 0;
    for (int i = 1; i <= n; i++){
        ch(a[i], i);
        ans = add(ans, sum);
    }
    printf("%d\n", ans);
    return 0;
}

