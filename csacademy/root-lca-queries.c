#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
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
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef long long ll;
enum{maxn = 100010};
vec w[maxn];
int dfn[maxn], pfn[maxn], idx, p[maxn], a[maxn];


void work(int x, int fa){
    dfn[x] = idx++;
    p[x] = fa;
    int isz = w[x].sz;
    for(int i = 0; i < isz; i++){
        int u = w[x].ptr[i];
        if (u == fa) 
            continue;
        work(u, x);
    }
    pfn[x] = idx++;
}
int main(){
    int n, q, x, y, z;
    scanf("%d%d", &n, &q);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        w[x].ptr = pushback(w[x].ptr, &w[x].sz, y);
        w[y].ptr = pushback(w[y].ptr, &w[y].sz, x);
    }
    idx = 0;
    work(1, 0);
    for (int i = 1; i <= n; i++) {
        a[i] = (pfn[i] - dfn[i] + 1) / 2;
    }
    while (q--) {
        scanf("%d%d%d", &x, &y, &z);
        int isz = w[z].sz;
        int s1 = -1, s2 = -1;
        for (int i = 0; i < isz; i++) {
            int u = w[z].ptr[i];
            if (u == p[z]) 
                continue;
            if (dfn[u] <= dfn[x] && pfn[u] >= dfn[x]) {
                s1 = u;
            }
            if (dfn[u] <= dfn[y] && pfn[u] >= dfn[y]) {
                s2 = u;
            }
        }
        if ((s1 == -1 && s2 == -1) || s1 == s2) {
            puts("0");
        }
        else {
            if (s1 != -1 && s2 != -1) {
                printf("%d\n", n - a[s1] - a[s2]);
            }
            else if (s1 != -1) {
                printf("%d\n", a[z] - a[s1]);
            }
            else {
                printf("%d\n", a[z] - a[s2]);
            }
        }

    }
}

