#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
enum{ MAXN = 5555};
enum{ MOD  =(int)1e9+7};
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

#define bitset_elem(ptr,bit) ((unsigned char *)(ptr))[(bit)/CHAR_BIT]
#define bitset_mask(bit) (1U << ((bit) % CHAR_BIT))
int bitset_isset(void *ptr, int bit){
  return (bitset_elem(ptr,bit) & bitset_mask(bit)) != 0;
}
int bitset_set(void *ptr, int bit){
  unsigned char *b = (unsigned char *)ptr + (bit / CHAR_BIT);
  unsigned char m = bitset_mask(bit);
  if ((*b & m)) return 0;
  *b |= m;
  return 1;
}
int bitset_unset(void *ptr, int bit){
	unsigned char *b = (unsigned char *)ptr + (bit / CHAR_BIT);
	unsigned char m = bitset_mask(bit);
	if ((*b & m) == 0)
    return 0;
	*b &= ~m;
	return 1;
}
// using bs = bitset<MAXN>;
int n, m, q;
char graph[2][MAXN][768];

void set(char*bs, int off, bool b){
    if(b)
        bitset_set  (bs, off);
    else
        bitset_unset(bs, off);
}
void flip(char*bs, int off){
    if(bitset_isset(bs, off))
        bitset_unset(bs, off);
    else
        bitset_set  (bs, off);
}

int main(){
    scanf("%d %d %d", &n, &m, &q);
    for(int i=0; i<m; ++i){
        int u, v;
        scanf("%d %d", &u, &v);
        set(graph[0][u], v, 1);
        set(graph[1][v], u, 1);
    }
    int trans = 0;
    int neg   = 0;
    while(q-- > 0){
        int op;
        int u, v;
        scanf("%d", &op);
        if(op == 1){
            for(int i=0; i<n; ++i){
                set(graph[0][i], n, neg);
                set(graph[1][i], n, neg);
                set(graph[0][n], i, neg);
                set(graph[1][n], i, neg);
            }
            ++n;
        }
        else if(op == 2 || op == 4){
            scanf("%d %d", &u, &v);
            flip(graph[trans  ][u], v);
            flip(graph[trans^1][v], u);
        }
        else if (op == 3){
            scanf("%d", &u);
            for(v = 0; v < n; ++v){
                if(u == v)
                    continue;
                set(graph[0][u], v, neg);
                set(graph[0][v], u, neg);
                set(graph[1][u], v, neg);
                set(graph[1][v], u, neg);
            }
        }
        else if(op == 5)
            trans ^= 1;
        else if(op == 6)
            neg ^= 1;
    }
    printf("%d\n", n);
    for(int u=0; u<n; ++u){
        vec adj = newVec();
        for(int v = n - 1; v >= 0; --v){
            if(u == v)
                continue;
            if(bitset_isset(graph[trans][u], v)^neg)
               pb(adj, v);
        }
        ll res = 0;
        for(int z=0; z<adj.sz; z++){int v = adj.ptr[z];
            res = (7LL * res + v) % MOD;
        }
        printf("%d %lld\n", adj.sz, res);
    }
    return 0;
}
