#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

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

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef struct pairS{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
pair *pushbackP(pair *array, int *size, pair value) {
  pair *output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct vecpS {
	pair*ptr;
	int sz;
}vecp;
vecp newVecP() {
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

///////////////////
vec v[100001];
vecp ans;

void go(int a, int b){
    if(v[a].sz && v[a].ptr[v[a].sz-1] == b && v[b].sz && v[b].ptr[v[b].sz-1] == a){
        ans.ptr = pushbackP(ans.ptr, &ans.sz, newPair(min(a, b), max(a, b)));
        v[a].sz--;
        v[b].sz--;
        if(v[a].sz>0){
            go(a, v[a].ptr[v[a].sz-1]);
        }
        if(v[b].sz>0){
            go(b, v[b].ptr[v[b].sz-1]);
        }
    }
}
int main(){
    int n;
    scanf("%d", &n);
    int m = 0;
    for(int i = 1; i <= n; ++i){
        int first;
        scanf("%d", &first);
        m += first;
        for(int z=0;z<first;z++){
          int vv;
          scanf("%d", &vv);
          v[i].ptr = pushback(v[i].ptr, &v[i].sz, vv);
        }
        reverse(v[i].ptr, 0, v[i].sz-1);
        if(v[i].sz>0){
            go(i, v[i].ptr[v[i].sz-1]);
        }
    }
    m /= 2;
    if(ans.sz != m){
        puts("-1");
    }
    else{
        for(int i=0;i<ans.sz;i++){pair pp = ans.ptr[i];
            printf("%d %d\n", pp.first, pp.second);
        }
    }
    return 0;
}
































