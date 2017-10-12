#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int cmp (const void *b, const void *a){
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
/////////////

enum{ N =(int) 2e5+5};
int n, k, l;
int head[2*N], len, vis[N], sz[N];
vec v;
typedef struct Node_s{
    int next, to;
}Node;
Node e[N];
void addEdge(int from, int to){
    e[len].to=to; 
    e[len].next=head[from]; 
    head[from]=len++;
}
void init(){
    memset(head, -1, sizeof(head));
    len = 0;
}
int dfs1(int x, int pre){
    int sum = 1;
    for(int i = head[x]; ~i; i=e[i].next){
        if(e[i].to==pre) 
            continue;
        sum+=(sz[i/2]=dfs1(e[i].to, x));
    }
    return sum;
}
void dfs2(int x, int pre){
    for(int i = head[x]; ~i; i=e[i].next){
        if(e[i].to==pre) 
            continue;
        if(vis[i/2]==1)
            v.ptr = pushback(v.ptr, &v.sz, sz[i/2]);
        else 
            dfs2(e[i].to, x);
    }
}
int main(){
    init();
    scanf("%d%d", &n, &k);
    for(int i = 1; i < n; i++){
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        vis[len/2] = c;
        addEdge(u, v);
        addEdge(v, u);
    }
    l = dfs1(1, 0);
    if(l<=k) 
        puts("0");
    else{
        dfs2(1, 0);
        qsort(v.ptr, v.sz, sizeof(int),cmp);//greater<int>() );
        int cnt = 0;
        while(l > k && cnt<v.sz)
            l -= v.ptr[cnt++];
        if(l>k) puts("-1");
        else printf("%d\n", cnt);
    }
    return 0;
}























