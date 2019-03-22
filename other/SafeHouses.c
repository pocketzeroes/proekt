#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

typedef struct{
  int first;
  int second;
}pair;
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
////////////////////
int dist(pair p1, pair p2){
    return abs(p1.first  - p2.first ) +
           abs(p1.second - p2.second);
}
int main(){
    int n;
    scanf("%d", &n);
    vecp s = newVecP();
    vecp h = newVecP();
    getchar();
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            char c = getchar();
            if(c == 'S')
                s.ptr = pushbackP(s.ptr, &s.sz, (pair){i,j});
            if(c == 'H')
                h.ptr = pushbackP(h.ptr, &h.sz, (pair){i,j});
        }
        getchar();
    }
    int ans=0;
    for(int i=0; i<s.sz; i++){
        int d = 100000;
        for(int j=0; j<h.sz; j++){
            d = min(d, dist(s.ptr[i], h.ptr[j]));
        }
        ans = max(ans, d);
    }
    printf("%d\n", ans);
    return 0;
}
