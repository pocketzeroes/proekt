#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
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
enum{ maxn =(int) 1e6 + 10};
bool vis[maxn];
vecp v;
int n, w, h;

int cal(int x, int y){
    if(x == 0) return y;
    if(y == h) return h + x;
    if(x == w) return 2 * h + w - y;
    return 2 * (h + w) - x;
}
void get(double t, double*x, double*y){
    if(t <= h) *x = 0, *y = t;
    else if(t <= h + w) *x = t - h, *y = h;
    else if(t <= 2 * h + w) *x = w, *y = 2 * h + w - t;
    else *x = 2 * (h + w) - t, *y = 0;
}
int main(){
    scanf("%d %d %d", &n, &w, &h);
    for(int i=0; i<n; ++i){
        int X1, Y1, X2, Y2;
        scanf("%d %d %d %d", &X1, &Y1, &X2, &Y2);
        v.ptr=pushbackP(v.ptr, &v.sz, newPair(cal(X1, Y1), i));
        v.ptr=pushbackP(v.ptr, &v.sz, newPair(cal(X2, Y2), i));
    }
    qsort(v.ptr, v.sz, sizeof(pair), cmpP);
    int sz = v.sz, p = 0, cnt = 0, one = 0;
    for(int i = 0; i < sz; ++i){
        if(p == i)
            vis[v.ptr[i].second] = true, ++p, ++cnt;
        while(!vis[v.ptr[p].second])
            vis[v.ptr[p].second] = true, p = (p + 1) % sz, ++cnt;
        if(cnt == n){
            double ax1, ay1, ax2, ay2;
            get(v.ptr[i].first - 0.5, &ax1, &ay1);
            get(v.ptr[p].first - 0.5, &ax2, &ay2);
            printf("1\n%.8f %.8f %.8f %.8f\n", ax1, ay1, ax2, ay2);
            one = 1; break;
        }
        vis[v.ptr[i].second] = false, --cnt;
    }
    if(!one)
        printf("2\n0.5 0 %.8f %.8f\n0 %.8f %.8f %.8f\n", w - 0.5, 1.0 * h, h - 0.5, 1.0 * w, 0.5);
    return 0;
}
