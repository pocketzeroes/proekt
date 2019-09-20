#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include <stddef.h>
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


double INF = 1e100;
double EPS = 1e-12;

double dist(double x1, double y1, double x2, double y2){
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}
bool intersect(double x1, double y1, double r1, double x2, double y2, double r2){
    double d =dist(x1,y1,x2,y2);
    if(d>r1+r2 || fabs(d-r1-r2)<EPS)
        return false;
    if(fabs(d)<EPS && fabs(r1-r2)<EPS)
        return true;
    if( (d+r1 < r2) || (fabs(r2-d-r1)<EPS) || (d+r2 < r1) || (fabs(r1-d-r2)<EPS) )
        return false;
    return true;
}
int main(){
    int n;
    while(scanf("%d", &n)==1 && n != -1){
        double x[n], y[n], r[n];
        for (int i=0;i<n;i++)
            scanf("%lf%lf%lf", &x[i], &y[i], &r[i]);
        bool g[n][n]; memset(g,0,sizeof(g));
        for (int i=0;i<n;i++)
            for (int j=i+1;j<n;j++)
                if (intersect(x[i],y[i],r[i],x[j],y[j],r[j]))
                    g[i][j] = g[j][i] = true;
        bool mark[n]; memset(mark,0,sizeof(mark));
        stack*q=new();
        int best = 0;
        for(int i=0;i<n;i++){
            if(mark[i])
                continue;
            push(q, i);
            int c = 0;
            while(!empty(q)){
                int p = top(q); pop(q);
                if(mark[p])
                    continue;
                mark[p] = true;
                c++;
                for (int j=0;j<n;j++)
                    if (g[p][j] && !mark[j])
                        push(q, j);
            }
            best = fmax(best,c);
        }
        if (best != 1)
            printf("The largest component contains %d rings.\n", best);
        else
            puts("The largest component contains 1 ring.");
    }
    return 0;
}
