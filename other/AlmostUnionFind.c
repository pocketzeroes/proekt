#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
void erase(vec*v, int pos){
    for(int i=pos; i < v->sz-1; i++)
        v->ptr[i] = v->ptr[i+1];
    (v->sz)--;
}
/////////////////////////////////
enum{MAXN = 100020};
int  root[MAXN];
vec  sets[MAXN];
long sums[MAXN];

//class AlmostUnionFind{
void AlmostUnionFind(int n){
    for(int i=1; i<=n; i++){
        root[i] = i;
        sums[i] = i;
        sets[i].sz=0;
        pb(sets[i], i);
    }
}
void move(int x, int y){
    if(root[x] == root[y])
        return;
    int it;
    for(it=0; it<sets[root[x]].sz && sets[root[x]].ptr[it]!=x; it++);
    sums[root[x]] -= x;
    sums[root[y]] += x;
    erase(&sets[root[x]], it);
    pb(sets[root[y]], x);
    root[x] = root[y];
}
void unite(int x, int y){
    x = root[x];
    y = root[y];
    if(x == y)
        return;
    if(sets[x].sz >= sets[y].sz){
        for(int z=0;z<sets[y].sz;z++){int i = sets[y].ptr[z];
            pb(sets[x], i);
            root[i] = x;
        }
        sets[y].sz=0;
        sums[x] += sums[y];
        sums[y] = 0;
    }
    else{
        for(int z=0;z<sets[x].sz;z++){int i = sets[x].ptr[z];
            pb(sets[y], i);
            root[i] = y;
        }
        sets[x].sz=0;
        sums[y] += sums[x];
        sums[x] = 0;
    }
}
//};
int main(){
    int n, m, command, p, q;
    while(scanf("%d %d", &n, &m)==2){
        clr(root);
        clr(sets);
        clr(sums);
        AlmostUnionFind(n);
        while(m--){
            scanf("%d", &command);
            if     (command==1){
                scanf("%d %d", &p, &q);
                unite(p, q);
            }
            else if(command==2){
                scanf("%d %d", &p, &q);
                move(p, q);
            }
            else if(command==3){
                scanf("%d", &p);
                printf("%d %ld\n", sets[root[p]].sz, sums[root[p]]);
            }
        }
    }
    return 0;
}
