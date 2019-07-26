#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

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

////////////////////////
typedef struct Node{
    vec  values;
    int  computed;
    int  score;
    struct Node*ant;
    int  vi;
    int  vj;
    int  op;
}Node;
typedef Node* Nodep;

#include<stddef.h>
#include<stdbool.h>
#define check_pointer(p) if (!p) {puts("Out of memory."); exit(EXIT_FAILURE);}
#define MINIMUM_SIZE  1
#define GROWTH_FACTOR 2
typedef Nodep T;

typedef struct{
    T *bottom;
    T *top;
    T *allocated_top;
}
stack;
stack * new(void){
  stack *s = malloc(sizeof(stack));
  check_pointer(s);
  s->bottom = malloc(MINIMUM_SIZE * sizeof(T));
  check_pointer(s->bottom);
  s->top = s->bottom - 1;
  s->allocated_top = s->bottom + MINIMUM_SIZE - 1;
  return s;
}
void destroy(stack *s){
  free(s->bottom);
  free(s);
}
bool empty(stack *s){
    return s->top < s->bottom ? true : false;
}
void push(stack *s, T x){
    if (s->top == s->allocated_top)
    {
        ptrdiff_t qtty = s->top - s->bottom + 1;
        ptrdiff_t new_qtty = GROWTH_FACTOR * qtty;
        s->bottom = realloc(s->bottom, new_qtty * sizeof(T));
        check_pointer(s->bottom);
        s->top = s->bottom + qtty - 1;
        s->allocated_top = s->bottom + new_qtty - 1;
    }
    *(++s->top) = x;
}
T pop(stack *s){
    return *(s->top--);
}
T top(stack *s){
    return *(s->top);
}

void computeScore(Node*n, int target);

Node*newNode(vec values, int target, Node*ant, int vi, int vj, int op){
    Node*rez=calloc(1, sizeof(Node));
    rez->values = values;
    computeScore(rez, target);
    rez->ant = ant;
    rez->vi = vi;
    rez->vj = vj;
    rez->op = op;
    return rez;
}
void getOps(Node*n){
    if     (n->op == 0) printf("%d + %d = %d\n", n->vi, n->vj, n->vi + n->vj);
    else if(n->op == 1) printf("%d - %d = %d\n", n->vi, n->vj, n->vi - n->vj);
    else if(n->op == 2) printf("%d * %d = %d\n", n->vi, n->vj, n->vi * n->vj);
    else if(n->op == 3) printf("%d / %d = %d\n", n->vi, n->vj, n->vi / n->vj);
}
void computeScore(Node*n, int target){
    int bestScore = target;
    int best = 0;
    for(int z=0; z< n->values.sz; z++){int v = n->values.ptr[z];
        int dif = abs(target-v);
        if (dif < bestScore){
            bestScore = dif;
            best = v;
        }
    }
    n->computed = best;
    n->score    = bestScore;
}

/////////////////node
int best;
int bestScore;
Node*bestNode;

vec combineValues(vec values, int i, int j, int value){
    vec newArray = newVec();
    for (int v = 0; v < values.sz; ++v){
        if (v != i && v != j) {
            newArray.ptr = pushback(newArray.ptr, &newArray.sz, values.ptr[v]);
        }
    }
    newArray.ptr = pushback(newArray.ptr, &newArray.sz, value);
    return newArray;
}
bool exploreSolution(Node*solution, stack*solutions, int target){
    int n = solution->values.sz;
    if (n == 1)
        return false;
    for (int i = 0; i < n; ++i){
        for (int j = i+1; j < n; ++j) {
            int vi = solution->values.ptr[i];
            int vj = solution->values.ptr[j];
            int vn = 0;
            vn = vi + vj;
            vec valuesAdd = combineValues(solution->values, i, j, vn);
            Node*pnode = newNode(valuesAdd, target, solution, vi, vj, 0);
            if(pnode->score == 0){
                best      = pnode->computed;
                bestScore = pnode->score;
                bestNode  = pnode;
                return true;
            }
            if (pnode->score < bestScore){
                best      = pnode->computed;
                bestScore = pnode->score;
                bestNode  = pnode;
            }
            push(solutions, pnode);
            if (vj > vi){
                int aux = vi;
                vi      = vj;
                vj      = aux;
            }
            vn = vi - vj;
            if (vn != 0 ){
                vec valuesSub = combineValues(solution->values, i, j, vn);
                Node*sub = newNode(valuesSub, target, solution, vi, vj, 1);
                if(sub->score == 0){
                    best      = sub->computed;
                    bestScore = sub->score;
                    bestNode  = sub;
                    return true;
                }
                if (sub->score < bestScore){
                    best      = sub->computed;
                    bestScore = sub->score;
                    bestNode  = sub;
                }
                push(solutions, sub);
            }
            vn = vi * vj;
            vec valuesMult = combineValues(solution->values, i, j, vn);
            Node*mult = newNode(valuesMult, target, solution, vi, vj, 2);
            if (mult->score == 0){
                best      = mult->computed;
                bestScore = mult->score;
                bestNode  = mult;
                return true;
            }
            if (mult->score < bestScore){
                best      = mult->computed;
                bestScore = mult->score;
                bestNode  = mult;
            }
            push(solutions, mult);
            if (vj > vi) {
                int aux;
                aux = vi;
                vi  = vj;
                vj  = aux;
            }
            if(vi % vj == 0){
                vn = vi/vj;
                vec valuesDiv = combineValues(solution->values, i, j, vn);
                Node*div = newNode(valuesDiv, target, solution, vi, vj, 3);
                if (div->score == 0){
                    best      = div->computed;
                    bestScore = div->score;
                    bestNode  = div;
                    return true;
                }
                if (div->score < bestScore){
                    best      = div->computed;
                    bestScore = div->score;
                    bestNode  = div;
                }
                push(solutions, div);
            }
        }
    }
    return false;
}
int main(){
    int n_cases = in_nextInt();
    for(int c = 0; c < n_cases; ++c){
        if(c != 0)
            puts("");
        vec values = newVec();
        for(int i = 0; i < 6; ++i){
            values.ptr = pushback(values.ptr, &values.sz, in_nextInt());
        }
        int target = in_nextInt();
        stack*solutions = new();//of Node
        Node*first = newNode(values, target, NULL,0,0, -1);
        best      = first->computed;
        bestScore = first->score;
        bestNode  = first;
        push(solutions, first);
        bool exact = false;
        int explored = 0;
        while(!exact && !empty(solutions)){
            Node*solution = pop(solutions);
            explored++;
            exact = exploreSolution(solution, solutions, target);
        }
        printf("Target: %d\n", target);
        stack*path = new();//of Node
        Node*current = bestNode;
        while(current != NULL){
            push(path, current);
            current = current->ant;
        }
        while(!empty(path)){
            current = pop(path);
            if(current->op != -1){
                getOps(current);
            }
        }
        printf("Best approx: %d\n", best);
    }
    return 0;
}
