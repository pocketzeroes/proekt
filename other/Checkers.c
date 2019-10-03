#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<stddef.h>

#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

typedef struct{
  int first;
  int second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}

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

T pop(stack *s)
{
    return *(s->top--);
}
T top(stack *s)
{
    return *(s->top);
}

bool**newmat(int x, int y){
  bool**rv = calloc(x, sizeof(bool*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(bool));
  return rv;
}

/////////////////////////
int gsz;

inline bool rng(int y, int x){
    return y >= 0 && x >= 0 && y < gsz && x < gsz;
}
bool checkBlackHorse(int y, int x, bool**wmap, bool**bmap){
    bool**wmvis = newmat(gsz, gsz);
    stack*stk=new();//of pair
    push(stk, newpair(y, x));
    int ndeg[gsz][gsz]; clr(ndeg);
    while(!empty(stk)){
        pair posi = top(stk); pop(stk);
        int degree = 0;
        int nyY = posi.first+2;
        int nyX = posi.second+2;
        if(rng(nyY, nyX) && wmap[nyY-1][nyX-1]){
            if(!wmap[nyY][nyX]){
                degree++;
                wmvis[nyY - 1][nyX - 1] = true;
                if(ndeg[nyY][nyX] == 0){
                    push(stk, newpair(nyY, nyX));
                    if(bmap[nyY][nyX])
                        return 0;
                }
            }
            else
                return 0;
        }
        nyY = posi.first  - 2;
        nyX = posi.second + 2;
        if(rng(nyY, nyX) && wmap[nyY + 1][nyX - 1]){
            if(!wmap[nyY][nyX]){
                degree++;
                wmvis[nyY + 1][nyX - 1] = true;
                if(ndeg[nyY][nyX] == 0){
                    push(stk, newpair(nyY, nyX));
                    if(bmap[nyY][nyX])
                        return 0;
                }
            }
            else
                return 0;
        }
        nyY = posi.first  - 2;
        nyX = posi.second - 2;
        if(rng(nyY, nyX) && wmap[nyY + 1][nyX + 1]){
            if(!wmap[nyY][nyX]){
                degree++;
                wmvis[nyY + 1][nyX + 1] = true;
                if(ndeg[nyY][nyX] == 0){
                    push(stk, newpair(nyY, nyX));
                    if(bmap[nyY][nyX])
                        return 0;
                }
            }
            else
                return 0;
        }
        nyY = posi.first  + 2;
        nyX = posi.second - 2;
        if(rng(nyY, nyX) && wmap[nyY - 1][nyX + 1]){
            if(!wmap[nyY][nyX]){
                degree++;
                wmvis[nyY - 1][nyX + 1] = true;
                if (ndeg[nyY][nyX] == 0){
                    push(stk, newpair(nyY, nyX));
                    if (bmap[nyY][nyX])
                        return 0;
                }
            }
            else
                return 0;
        }
        ndeg[posi.first][posi.second] = degree;
    }
    for(int y=0; y<gsz; y++)
        for(int x=0; x<gsz; x++)
            if (wmap[y][x] != wmvis[y][x])
                return 0;
    if (ndeg[y][x] % 2 == 0) {
        for (int y = 0; y < gsz; y++)
            for (int x = 0; x < gsz; x++)
                if (ndeg[y][x]%2 != 0)
                    return 0;
    }
    else{
        int ojamnCount = 0;
        for (int y = 0; y < gsz; y++) {
            for (int x = 0; x < gsz; x++) {
                if (ndeg[y][x] % 2 != 0) {
                    ojamnCount++;
                    if (ojamnCount == 3)
                        return 0;
                }
            }
        }
    }
    return 1;
}
int main(){
    scanf("%d", &gsz);
    bool**wmap = newmat(gsz, gsz);
    bool**bmap = newmat(gsz, gsz);
    char read;
    getchar();
    for(int y=0; y<gsz; y++){
        for(int x=0; x<gsz; x++){
            read=getchar();
            if     (read == 'W') wmap[y][x] = true;
            else if(read == 'B') bmap[y][x] = true;
        }
        getchar();
    }
    int count = 0;
    for(int y=0; y<gsz; y++){
        for(int x=0; x<gsz; x++){
            if(bmap[y][x])
                count += checkBlackHorse(y, x, wmap, bmap);
        }
    }
    printf("%d\n", count);
    return 0;
}
