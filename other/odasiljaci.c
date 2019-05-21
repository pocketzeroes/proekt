#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
}

void swapd(double*nums, int i, int j){
   double t= nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reversed(double*nums, int start, int end){
    while(start < end){
        swapd(nums, start, end);
        start++;
        end  --;
    }
}


enum{ MAXN = 300010};

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
int n, d, t[MAXN], x[MAXN], h[MAXN];
double s[2][MAXN];
vecp v;


double drop(pair s){
    int x1 = x[s.first],
        y1 = h[s.first],
        x2 = x[s.second],
        y2 = h[s.second];
    return ((double)x1 * (y1 - y2) - (double)y1 * (x1 - x2)) / (y1 - y2);
}
void update(pair*s, int c){
    if(drop(*s) < drop((pair){s->first, c}))
        s->second = c;
}

int main(){
    scanf("%d %d", &n, &d);
    ++n;
    for(int i=1; i<n; ++i)
        scanf("%d %d %d", t + i, x + i, h + i);
    x[n] = d;
    ++n;
#define v_back v.ptr[v.sz-1]
    for(int k = 0; k < 2; ++k){
        for(int i = 0; i < n - 1; ++i){
            for(; v.sz && h[v_back.first] <= h[i]; v.sz--);
            if(v.sz)
                for(update(&v_back, i); v.sz > 1; v.sz--){
                    update(&v.ptr[v.sz - 2], i);
                    if(drop(v_back) < drop(v.ptr[v.sz - 2]))
                        break;
                }
            if(t[i]){
                v.ptr = pushbackP(v.ptr, &v.sz, newPair(i,0));
                s[k][i] = x[i];
            }
            else if(v.sz)
                s[k][i] = min(drop(v_back), (double)x[i + 1]);
            else
                s[k][i] = x[i + 1];
        }
        if(!k){
            reverse(t, 0, n-1);
            reverse(x, 0, n-1);
            reverse(h, 0, n-1);
            for(int i = 0; i < n; ++i)
                x[i] = d - x[i];
            v.sz=0;
        }
    }
    reversed(s[1], 0, n-1);
    for(int i = 0; i < n; ++i)
        s[1][i] = d - s[1][i];
    double t = 0.;
    for(int i = 0; i < n - 1; ++i)
        if(s[0][i] > s[1][i + 1])
            t += s[0][i] - s[1][i + 1];
    printf("%.6lf\n", d - t);
    return 0;
}
