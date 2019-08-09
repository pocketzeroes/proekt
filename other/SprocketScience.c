#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ typeof(a) tmp; tmp = a; a = b; b = tmp; }while(0)
int cmpR(const void *b, const void*a){ return ( *(int*)a - *(int*)b );}
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
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
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
typedef struct{
  int first;
  vec second;
}piv;
int cmpVec(vec*a, vec*b){
  int msz = fmin(a->sz, b->sz);
  for(int i=0;i < msz; i++){
    if(a->ptr[i] != b->ptr[i]) 
        return (a->ptr[i] < b->ptr[i])?-1:1;
  }
  if(a->sz!=b->sz)
      return (a->sz < b->sz)?-1:1;
  return 0;
}


int gcd(int a, int b){
  return (b == 0) ? a : gcd(b, a % b);
}
int lcm(int a, int b){
    return a / gcd(a,b) * b;
}
piv getratio(vecp v){
    int top = v.ptr[0].first;
    for(int z=0;z<v.sz;z++){pair i = v.ptr[z];
        top = lcm(top, i.first);
    }
    vec bot=newVec();
    for(int z=0;z<v.sz;z++){pair i = v.ptr[z];
        bot.ptr = pushback(bot.ptr, &bot.sz, i.second*(top/i.first));
    }
    return(piv){top,bot};
}
void solve(vecp v1, vecp v2){
    piv r1 = getratio(v1);
    piv r2 = getratio(v2);
    qsort(r1.second.ptr, r1.second.sz, sizeof(int), cmpR);//rev
    qsort(r2.second.ptr, r2.second.sz, sizeof(int), cmpR);//rev
    if(r1.first > 10000 || r2.first > 10000)
        return;
    if(r1.second.ptr[0] > r2.second.ptr[0])
        swap(r1, r2);
    if(r2.second.ptr[0] % r1.second.ptr[0] != 0)
        return;
    int diff = r2.second.ptr[0] / r1.second.ptr[0];
    for(int z=0;z<r1.second.sz;z++){
        r1.second.ptr[z] *= diff;
    }
    r1.first *= diff;
    if(cmpVec(&r1.second, &r2.second)==0){
        printf("%d %d\n", r1.first, r2.first);
        for(int z=0;z<r1.second.sz;z++){int i=r1.second.ptr[z];
            printf("%d ", i);
        }
        puts("");
        exit(0);
    }
}
int main(){
    pair v[12];
    for(int i=0;i<12;i++){
        scanf("%d", &v[i].first);
        getchar();
        scanf("%d", &v[i].second);
    }
    for(int i = 0; i < (1<<12); i++){
        if(__builtin_popcount(i) == 6){
            vecp v1=newVecP();
            vecp v2=newVecP();
            for(int j = 0; j < 12; j++){
                if(i & (1<<j))
                    v1.ptr = pushbackP(v1.ptr, &v1.sz, v[j]);
                else
                    v2.ptr = pushbackP(v2.ptr, &v2.sz, v[j]);
            }
            solve(v1, v2);
        }
    }
    puts("impossible");
    return 0;
}
