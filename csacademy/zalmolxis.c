#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include <stddef.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

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


#define check_pointer(p) if (!p) {puts("Out of memory."); exit(EXIT_FAILURE);}
#define MINIMUM_SIZE  1
#define GROWTH_FACTOR 2
typedef int T;
typedef struct{
  T *bottom;
  T *top;
  T *allocated_top;
} stack;
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
  if (s->top == s->allocated_top){
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
int size(stack*s){
  return s->top - s->bottom + 1;
}



typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
pair*pushbackP(pair *array, int *size, pair value) {
  pair *output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


///////////////////////////
int X[3030303];
int Y[1010101];

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    for(int i=0; i<N; i++) 
        scanf("%d", &X[i]);
    stack*st=new();
    push(st, 30);
    vecp hoge = newVecP();
    int orig_index = 0;
    int cnt = 0;
    while (!empty(st)) {
        int x = top(st); pop(st);
        if (orig_index >= N){
            hoge.ptr = pushbackP(hoge.ptr, &hoge.sz, newPair(cnt, x));
            Y[cnt] = -1;
            cnt++;
        } 
        else if(x > X[orig_index]){
            push(st, max(0, x-1));
            push(st, max(0, x-1));
        }
        else if(x < X[orig_index]){
            hoge.ptr = pushbackP(hoge.ptr, &hoge.sz, newPair(cnt, x));
            Y[cnt] = -1;
            cnt++;
        }
        else {
            Y[cnt] = x;
            orig_index++;
            cnt++;
        }
    }
    int hogei = 0;
    int rest = N + K;
    for (int i=0;i<(cnt);i++) {
        if (Y[i] >= 0){
            printf("%d ", Y[i]);
            --rest;
        }
        else if (cnt - i == rest) {
            printf("%d ", hoge.ptr[hogei].second);
            ++hogei;
            --rest;
        }
        else {
            stack*stst=new();
            push(stst, hoge.ptr[hogei].second);
            vec fuga = newVec();
            while (!empty(stst) && fuga.sz + (int)size(stst) + cnt - i - 1 < rest) {
                int x = top(stst); pop(stst);
                if (x == 0)
                    fuga.ptr = pushback(fuga.ptr, &fuga.sz, 0);
                else{
                    push(stst, x-1);
                    push(stst, x-1);
                }
            }
            while(!empty(stst)){
                int x = top(stst); pop(stst);
                fuga.ptr = pushback(fuga.ptr, &fuga.sz, x);
            }
            for(int z=0;z<fuga.sz;z++){int x = fuga.ptr[z];
                printf("%d ", x);
                --rest;
            }
            ++hogei;
        }
    }
    puts("");
    return 0;
}
