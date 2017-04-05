#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>

typedef long long ll;

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

enum{     MAX_N   =  100000};
const int MIN_VAL = -10000;
const int MAX_VAL =  10000;
int n, k;
int v   [MAX_N];
bool vis[MAX_N];
ll  ans;

int cmp(const void*pa,const void*pb){
  int*a=(int*)pa;
  int*b=(int*)pb;
  return a[0]-b[0];
}

int main() {
    scanf("%d %d", &n, &k);
    assert(1 <= n && n <= MAX_N);
    assert(1 <= k && k <= n    );
    for (int i = 0; i < n; ++i) {
        scanf("%d", &v[i]);
        assert(MIN_VAL <= v[i] && v[i] <= MAX_VAL);
    }
    for (int i = 0; i < n; ++i) {
        if (vis[i]) 
            continue;
        int j = i;
        int*vals=NULL;int valsSz=0;
        while (!vis[j]) {
            vals=pushback(vals,&valsSz,v[j]);
            vis[j] = true;
            j = (j + k) % n;
        }
        qsort(vals, valsSz, sizeof(int), cmp);
        int median = vals[valsSz / 2];
        for(int i=0;i<valsSz;i++){
            int it=vals[i];
            ans += labs(it - median);
        }
        free(vals);
    }
    printf("%lld", ans);
}










