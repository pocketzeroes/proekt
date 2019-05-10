#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
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
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#define check_pointer(p) if (!p) {puts("Out of memory."); exit(EXIT_FAILURE);}
#define MINIMUM_SIZE  1
#define GROWTH_FACTOR 2
typedef pair T;

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
///////////////////////////////////
enum{ MAXN = 1000000};
enum{ MAXM = 62     };

char line[MAXN + 1];
char bomb[MAXM + 1];
int begin_cut[MAXN], 
    end_cut  [MAXN];
int n, m, left;

void bomb1(){
    for (int i=0; i<n; i++){
        if (line[i] == bomb[0]){
            begin_cut[i]++; 
            end_cut  [i]++;
        }
    }
}
void bomb2(){
    stack*S=new();
    for (int i=0; i<n; i++){
        if (line[i] == bomb[0]){
            push(S, (pair){i, 1});
            continue;
        }
        while(!empty(S)){
            pair tmp = top(S);pop(S);
            if (line[i] != bomb[tmp.second]){
                while(!empty(S))
                    pop(S);
                break;
            }
            tmp.second++;
            if (tmp.second == m){
                begin_cut[tmp.first]++;
                end_cut[i]++;
            }
            else
                push(S, (pair){tmp.first, tmp.second});
            break;
        }
    }
}
void Remove(){
    int erase = 0;
    left = 0;
    for (int i=0; i<n; i++){
        erase += begin_cut[i];
        if (erase)
            line[i] = '*';
        else
            left++;
        erase -= end_cut[i];
    }
}
void write(){
    if (left){
        for (int i=0; i<n; i++)
            if (line[i] != '*')
                printf ("%c", line[i]);
    }
    else
        printf ("FRULA");
    printf ("\n");
}
int main(){
    scanf ("%s%s", line, bomb);
    n = strlen(line), 
    m = strlen(bomb);
    if (m == 1)
        bomb1();
    else       
        bomb2();
    Remove();
    write();
    return 0;
}
