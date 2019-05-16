#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
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
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int n, k;
int dist[1<<20];
vec q;

int main(){
    scanf("%d %d", &n, &k);
    for(int b = 0; b < (1<<k); b++)
        dist[b] = 999999999;
    for(int i = 0; i < n; i++){
        char*s=getstr();
        int u = 0;
        for (int j = 0; j < k; j++)
            u += (1<<j)*(s[j]-'0');
        dist[u] = 0;
        q.ptr = pushback(q.ptr, &q.sz, u);
    }
    int best;
    for (int i = 0; i < q.sz; i++){
        int a = q.ptr[i];
        best = a;
        for (int j = 0; j < k; j++){
            int b = a^(1<<j);
            if (dist[a]+1 < dist[b]){
                dist[b] = dist[a]+1;
                q.ptr = pushback(q.ptr, &q.sz, b);
            }
        }
    }
    for (int j = 0; j < k; j++) {
        if (best&(1<<j))
            printf("1");
        else
            printf("0");
    }
    puts("");
    return 0;
}
