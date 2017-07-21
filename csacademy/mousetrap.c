#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
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
int cmp (const void *b, const void *a)
{
   return ( *(int*)a - *(int*)b );
}

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



int  n, t, m;
vec  g   [1000055];
bool crit[1000055];
int  have[1000055];
vec  wtf [1000055];
vec  vvv;


int dfs(int v, int par){
    int res = 0;
    int high = 0, second = 0;
    for(int i=0;i<g[v].sz;i++){int u = g[v].ptr[i];
        if (u != par && !crit[u]) {
            res++;
            int val = dfs(u, v);
            if (val > high) {
                second = high;
                high = val;
            }
            else if (val > second) {
                second = val;
            }
        }
    }
    return res + second;
}
bool fin(int v, int par, int t, vec*vvv){
    vvv->ptr = pushback(vvv->ptr, &vvv->sz ,v);
    if (v == t) {
        return true;
    }
    for(int i=0;i<g[v].sz;i++){int u = g[v].ptr[i];
        if (u != par) {
            if (fin(u, v, t, vvv)){
                return true;
            }
        }
    }
    vvv->sz--;
    return false;
}
bool trial(int x) {
    vec diu=newVec();
    int ac = 0;
    for (int i = 0; i < vvv.sz - 1; i++){
        int cnt = 0;
        for(int z=0;z<wtf[vvv.ptr[i]].sz;z++){int u = wtf[vvv.ptr[i]].ptr[z];
            if (u >= x - ac) {
                cnt++;
                diu.ptr = pushback(diu.ptr, &diu.sz ,i);
            }
        }
        ac += cnt;
    }
    reverse(diu.ptr, 0, diu.sz-1);
    for (int i = 0; i < vvv.sz - 1; i++){
        if(diu.sz!=0)
            diu.sz--;
        if(diu.sz!=0 && diu.ptr[diu.sz-1] == i) 
            return true;
    }
    return false;
}
int main() {
    scanf("%d %d %d", &n, &t, &m);
    if (n == 1) {
        puts("0");
        return 0;
    }
    for (int i = 0; i + 1 < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--, y--;
        g[x].ptr = pushback(g[x].ptr, &g[x].sz ,y);
        g[y].ptr = pushback(g[y].ptr, &g[y].sz ,x);
    }
    t--, m--;
    fin(m, -1, t, &vvv);
    for(int i=0;i<vvv.sz;i++){int u = vvv.ptr[i];
        crit[u] = true;
    }
    int sum = 0;
    for (int i = 0; i < vvv.sz - 1; i++){
        for(int z=0;z<g[vvv.ptr[i]].sz;z++){int u = g[vvv.ptr[i]].ptr[z];
            if (!crit[u]){
                have[vvv.ptr[i]]++;
            }
        }
        sum += have[vvv.ptr[i]];
    }
    int temp = sum;
    for (int i = 0; i < vvv.sz - 1; i++){
        for(int z=0;z<g[vvv.ptr[i]].sz;z++){int u = g[vvv.ptr[i]].ptr[z];
            if (!crit[u]){
                int val = dfs(u, vvv.ptr[i]) + sum;
                wtf[vvv.ptr[i]].ptr = pushback(wtf[vvv.ptr[i]].ptr, &wtf[vvv.ptr[i]].sz ,val);
            }
        }
        qsort(wtf[vvv.ptr[i]].ptr, wtf[vvv.ptr[i]].sz,sizeof(int), cmp);// reverse
        sum -= have[vvv.ptr[i]];
    }
    int lb = temp, ub = 3 * n;
    while (ub - lb > 1) {
        int mid = (ub + lb) >> 1;
        if (trial(mid))
            lb = mid;
        else
            ub = mid;
    }
    printf("%d\n", lb);
    return 0;
}





























































