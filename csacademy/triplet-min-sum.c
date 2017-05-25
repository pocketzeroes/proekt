#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

#define SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

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
////////////////////

enum{ Nmax    =(int) 1e5 + 5};
enum{ logNmax =(int) 18     };
int depth[Nmax], pos[Nmax], euler[2 * Nmax], rmq[logNmax][2 * Nmax], l[2 *Nmax], euler_count;
vec v[Nmax];

void dfs(int x, int p) {
    euler[++euler_count] = x;
    pos[x] = euler_count;
    if (p) {
        depth[x] = depth[p] + 1;
    }
    for(int i=0;i<v[x].sz;i++){int it = v[x].ptr[i];
        if (it != p) {
            dfs(it, x);
            euler[++euler_count] = x;
        }
    }
}
int lca(int x, int y) {
    if (pos[x] > pos[y]) {
        SWAP(x, y);
    }
    int dif = pos[y] - pos[x] + 1;
    int log_dif = l[dif];
    int best = rmq[log_dif][pos[x]];
    if (depth[rmq[log_dif][pos[x] + dif - (1 << log_dif)]] < depth[best]) {
        best = rmq[log_dif][pos[x] + dif - (1 << log_dif)];
    }
    return best;
}
int dist(int x, int y) {
    return depth[x] + depth[y] - 2 * depth[lca(x, y)];
}
void initLCA() {
    dfs(1, 0);
    for (int i = 2; i <= euler_count; ++i) {
        l[i] = l[i / 2] + 1;
    }
    for (int i = 1; i <= euler_count; ++i) {
        rmq[0][i] = euler[i];
    }
    for (int j = 1; (1 << j) <= euler_count; ++j) {
        for (int i = 1; i <= euler_count; ++i) {
            rmq[j][i] = rmq[j - 1][i];
            if (i + (1 << (j - 1)) <= euler_count) {
                if (depth[rmq[j - 1][i + (1 << (j - 1))]] < depth[rmq[j][i]]) {
                    rmq[j][i] = rmq[j - 1][i + (1 << (j - 1))];
                }
            }
        }
    }
}
int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i < n; ++i) {
        int x, y; 
        scanf("%d %d", &x, &y);
        v[x].ptr=pushback(v[x].ptr, &v[x].sz ,y);
        v[y].ptr=pushback(v[y].ptr, &v[y].sz ,x);
    }
    initLCA();
    while (q--) {
        int a, b, c; 
        scanf("%d %d %d", &a, &b, &c);
        int best = lca(a, b);
        int best_sum = dist(best, a) + dist(best, b) + dist(best, c);
        int crt = lca(a, c);
        int crt_sum = dist(crt, a) + dist(crt, b) + dist(crt, c);
        if (crt_sum < best_sum) {
            best = crt;
            best_sum = crt_sum;
        }
        crt = lca(b, c);
        crt_sum = dist(crt, a) + dist(crt, b) + dist(crt, c);
        if (crt_sum < best_sum) {
            best = crt;
            best_sum = crt_sum;
        }
        printf("%d %d\n", best, best_sum);
    }
    return 0;
}






















































