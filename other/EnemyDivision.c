#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
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
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    vec g[n]; memset(g, 0, sizeof(g));
    for(int i=0; i<m; ++i){
        int a, b;
        scanf("%d %d", &a, &b);
        a--, b--;
        g[a].ptr = pushback(g[a].ptr, &g[a].sz, b);
        g[b].ptr = pushback(g[b].ptr, &g[b].sz, a);
    }
    int  col[n]; fill(col, n, 2);
    int enem[n]; memset(enem, 0, sizeof(enem));
    for(int i=0; i<(n); ++i){
        int cnt[3]={0};
        for(int j=0; j<(g[i].sz); ++j)
            cnt[col[g[i].ptr[j]]]++;
        int color = 0, cur = i;
        if (cnt[0] > 1)
            color = 1;
        while(1){
            col[cur] = color;
            int ncur = -1;
            for(int j=0; j<(g[cur].sz); ++j)
                if (col[g[cur].ptr[j]] == color){
                    enem[cur]++;
                    if (++enem[g[cur].ptr[j]] == 2){
                        ncur = g[cur].ptr[j];
                        for(int l=0; l<(g[ncur].sz); ++l)
                            if (col[g[ncur].ptr[l]] == color){
                                enem[g[ncur].ptr[l]]--;
                                enem[ncur]--;
                            }
                    }
                }
            if (ncur == -1)
                break;
            cur = ncur;
            color = !color;
        }
    }
    vec res[2]; memset(res, 0, sizeof(res));
    for(int i=0; i<(n); ++i)
        res[col[i]].ptr = pushback(res[col[i]].ptr, &res[col[i]].sz, i);
    printf("%d\n", 1 + !(res[1].sz==0));
    for(int i=0; i<(2); ++i)
        for(int j=0; j<(res[i].sz); ++j){
            printf("%d", res[i].ptr[j] + 1);
            if (j + 1 < res[i].sz)
                printf(" ");
            else
                printf("\n");
        }
    return 0;
}
