#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
double max(double a, double b){return a>b?a:b;}
typedef struct{
  double first;
  double second;
}pair;
pair newPair(double a, double b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
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
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

int main(){
    int N, L;
    scanf("%d %d", &N, &L);
    double x[N]; memset(x, 0, sizeof(x));
    for(int i=0; i<N; ++i)
        scanf("%lf", &x[i]);
    vecp I = newVecP();
    I.ptr = pushbackP(I.ptr, &I.sz, newPair(10, 100));
    for(int i=0; i<N; ++i){
        for(int j=i+1; j<N; ++j){
            double Dx = max(x[i]-x[j], x[j]-x[i]);
            I.ptr = pushbackP(I.ptr, &I.sz, newPair(Dx,100));
            for(int n = 1; Dx/(n*L-1) > 0.1; ++n)
                I.ptr = pushbackP(I.ptr, &I.sz, newPair(Dx/(n*L+1),Dx/(n*L-1)));
        }
    }
    qsort(I.ptr, I.sz, sizeof(pair), cmpP);
    double end  = 0.1,
           best = 0.0;
    for(int i = 0; i < I.sz && I.ptr[i].first <= 10; ++i){
        if(I.ptr[i].first >= end)
            best = I.ptr[i].first;
        end = max(end, I.ptr[i].second);
    }
    if(best == 0)
        puts("no fika");
    else
        printf("%.10lf\n", best);
    return 0;
}
