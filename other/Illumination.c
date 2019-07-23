#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
enum{ MAXL = 100000};
enum{ MAXR = 1000};
enum{ MAXV = 2*MAXL};
typedef struct{
  int r, c, id;
}lamp;
int N, R, L;
lamp lamps[MAXL];
int adj[MAXV][MAXR*2], nadj[MAXV];
int nvisited, ncomponents;
int visited  [MAXV];
int smallest [MAXV];
int component[MAXV];
int stack    [MAXV], top;
int onstack  [MAXV];

void get_input(){
    int i;
    scanf(" %d %d %d", &N, &R, &L);
    assert(R <= MAXR);
    assert(L <= MAXL);
    for (i = 0; i < L; i++){
        scanf(" %d %d", &lamps[i].r, &lamps[i].c);
        lamps[i].id = i;
    }
}
void add_edge(int u, int v) {
    assert(nadj[u] < MAXR*2);
    adj[u][nadj[u]++] = v;
}
void add_constraint(int x, int y, int k) {
    add_edge(2*x + k, 2*y + 1-k);
    add_edge(2*y + k, 2*x + 1-k);
}
int cmp(const void *A, const void *B){
    lamp *a = (lamp *)A;
    lamp *b = (lamp *)B;
    if (a->r != b->r) {
        return a->r - b->r;
    }
    return a->c - b->c;
}
void mk_graph(){
    int i, j, k, t;
    for (k = 0; k < 2; k++){
        qsort(lamps, L, sizeof(lamp), cmp);
        for (i = 0; i < L; i++) {
            for (j = i+1; j < L; j++){
                if (lamps[i].r != lamps[j].r)
                    break;
                if (lamps[j].c - lamps[i].c > 2*R)
                    break;
                add_constraint(lamps[i].id, lamps[j].id, k);
            }
        }
        for (i = 0; i < L; i++){
            t = lamps[i].r;
            lamps[i].r = lamps[i].c;
            lamps[i].c = t;
        }
    }
}
void push(int u) {
    stack[top++] = u;
    onstack[u] = 1;
}
int pop() {
    int v;
    assert(top > 0);
    v = stack[--top];
    onstack[v] = 0;
    return v;
}
void visit(int u){
    int i, v;
    visited[u] = smallest[u] = ++nvisited;
    push(u);
    for (i = 0; i < nadj[u]; i++){
        v = adj[u][i];
        if (!visited[v]) {
            visit(v);
            if (smallest[v] < smallest[u])
                smallest[u] = smallest[v];
        } 
        else if (onstack[v]) {
            if (visited[v] < smallest[u])
                smallest[u] = visited[v];
        }
    }
    if (smallest[u] == visited[u]){
        ncomponents++;
        do {
            v = pop();
            component[v] = ncomponents;
        }
        while (u != v);
    }
}
void scc() {
    int u;
    for (u = 0; u < 2*L; u++)
        if (!visited[u])
            visit(u);
}
int is_impossible() {
    int i;
    for (i = 0; i < L; i++)
    if (component[2*i] == component[2*i + 1])
        return 1;
    return 0;
}
int main(){
    get_input();
    mk_graph();
    scc();
    if (is_impossible())
        printf("0\n");
    else
        printf("1\n");
    return 0;
}
