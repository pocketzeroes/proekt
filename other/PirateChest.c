#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<stddef.h>
typedef long long ll;
inline ll min(ll a, ll b){return a<b?a:b;}
inline ll max(ll a, ll b){return a>b?a:b;}
#define check_pointer(p) if (!p) {puts("Out of memory."); exit(EXIT_FAILURE);}
#define MINIMUM_SIZE  1
#define GROWTH_FACTOR 2
typedef int T;

typedef struct
{
    T *bottom;
    T *top;
    T *allocated_top;
} 
stack;
 
stack * new(void)
{
  stack *s = malloc(sizeof(stack));
  check_pointer(s);
  s->bottom = malloc(MINIMUM_SIZE * sizeof(T));
  check_pointer(s->bottom);
  s->top = s->bottom - 1;
  s->allocated_top = s->bottom + MINIMUM_SIZE - 1;
  return s;
}
 
void destroy(stack *s)
{
  free(s->bottom);
  free(s);
}
 
bool empty(stack *s)
{
    return s->top < s->bottom ? true : false;
}
 
void push(stack *s, T x)
{
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

enum{ Max = 505};
int depth[Max][Max], minVal[Max][Max][Max], maxDepth[Max][Max];
int arr[Max], rights[Max], lefts[Max];

int main(){
    int a, b, n, m;
    scanf("%d%d%d%d", &a, &b, &n, &m);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            scanf("%d", &depth[i][j]);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            int least = depth[i][j];
            int len = 1;
            for(int k = i; k < n; ++k){
                least = min(least, depth[k][j]);
                minVal[k][j][len] = least;
                len++;
            }
        }
    }
    for(int i = 0; i < n; ++i){
        for(int len = 1; len <= i+1; ++len){
            for(int j = 0; j < m; ++j)
                arr[j] = minVal[i][j][len];
            stack*positions=new();
            for(int j = 0; j < m; ++j){
                while(!empty(positions) && arr[top(positions)] >= arr[j])
                    pop(positions);
                if(empty(positions))
                    lefts[j] = -1;
                else
                    lefts[j] = top(positions);
                push(positions, j);
            }
            while(!empty(positions))
                pop(positions);
            for(int j = m-1; j >= 0; --j){
                while(!empty(positions) && arr[top(positions)] >= arr[j])
                    pop(positions);
                if(empty(positions))
                    rights[j] = m;
                else
                    rights[j] = top(positions);
                push(positions, j);
            }
            for(int j = 0; j < m; ++j){
                int width = rights[j] - lefts[j] - 1;
                maxDepth[len][width] = max(maxDepth[len][width], arr[j]);
            }
        }
    }
    for(int i = 501; i >= 1; --i)
        for(int j = 501-1; j >= 1; --j)
            maxDepth[i][j] = max(maxDepth[i][j], maxDepth[i][j+1]);
    for(int j = 501; j >= 1; --j)
        for(int i = 501-1; i >= 1; --i)
            maxDepth[i][j] = max(maxDepth[i][j], maxDepth[i+1][j]);
    ll volume = 0;
    for(int i = 1; i <= a; ++i){
        for(int j = 1; j <= b; ++j){
            ll currDepth = max(maxDepth[i][j], maxDepth[j][i]);
            ll num = currDepth*n*m;
            ll dem = n*m-i*j;
            ll height = num/dem + (num%dem != 0) - 1;
            volume = max(volume, 1LL*i*j*height);
        }
    }
    printf("%lld\n", volume);
    return 0;
}
