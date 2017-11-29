#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}

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

int cmpP( pair a, pair b){
  int diff;
  diff = a.first  - b.first;  if(diff!=0) return diff;
  return a.second - b.second;
}

typedef struct{
  pair first;
  int  second;
}trip;
trip newTrip(pair a, int b){
  trip rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpT(const void*pa, const void*pb){
    trip*a=(trip*)pa;
    trip*b=(trip*)pb;
    int rv=cmpP(a->first, b->first);
    if(rv!=0)return rv<0?-1:1;
    return a->second < b->second?-1:1;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
trip*pushbackT(trip *array, int *size, trip value) {
    trip *output = resizeArray(array, trip, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	trip*ptr;
	int sz;
}vect;
vect newVecT(){
	vect rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


//////////////////////
enum{ SQN = 81000};
int t;
int m , a , b;

typedef struct{
    int arr[2][2];
}mat;

mat matmul(mat*aa, mat*other){
    mat res;
    for(int i = 0 ; i < 2 ; ++i){
        for(int j = 0 ; j < 2 ; ++j){
            res.arr[i][j] = 0;
            for(int k = 0 ; k < 2 ; ++k){
                res.arr[i][j] = (res.arr[i][j] + 1LL * aa->arr[i][k] * other->arr[k][j]) % m;
            }
        }
    }
    return res;
}
pair get(mat*x, int a, int b){
    return newPair((1LL * x->arr[0][0] * a + 1LL * x->arr[0][1] * b) % m , (1LL * x->arr[1][0] * a + 1LL * x->arr[1][1] * b) % m);
}
mat fib;
mat ifib;
mat fibsqn;
vect lft;// of trip
vect rgt;// of trip
ll ans;
int main(){
    scanf("%d", &t);
    while(t--){
        scanf("%d %d %d", &m, &a, &b);
        fib.arr[0][0] = 0;
        fib.arr[0][1] = 1;
        fib.arr[1][0] = 1;
        fib.arr[1][1] = 1;
        ifib.arr[0][0] = m - 1;
        ifib.arr[0][1] = 1;
        ifib.arr[1][0] = 1;
        ifib.arr[1][1] = 0;
        fibsqn.arr[0][0] = 1;
        fibsqn.arr[0][1] = 0;
        fibsqn.arr[1][0] = 0;
        fibsqn.arr[1][1] = 1;
        for(int i = 0 ; i < SQN ; ++i){
            fibsqn = matmul(&fibsqn, &fib);
        }
        mat cur; memset(cur.arr, 0, sizeof(cur.arr));
        cur.arr[0][0] = 1;
        cur.arr[0][1] = 0;
        cur.arr[1][0] = 0;
        cur.arr[1][1] = 1;
        lft.sz=0;
        for(int j = 0 ; j < SQN ; ++j){
            lft.ptr = pushbackT(lft.ptr, &lft.sz, newTrip(get(&cur, 0, 1), j));
            cur = matmul(&cur, &fibsqn);
        }
        cur.arr[0][0] = 1;
        cur.arr[0][1] = 0;
        cur.arr[1][0] = 0;
        cur.arr[1][1] = 1;
        rgt.sz=0;
        for(int j = 0 ; j < SQN ; ++j){
            rgt.ptr = pushbackT(rgt.ptr, &rgt.sz, newTrip(get(&cur, a, b), j));
            cur = matmul(&cur, &ifib);
        }
        qsort(lft.ptr, lft.sz, sizeof(trip), cmpT);
        qsort(rgt.ptr, rgt.sz, sizeof(trip), cmpT);
        ans = (ll)1e15 + 15;
        int j = 0;
        for(int z=0;z<lft.sz;z++){trip x = lft.ptr[z];
            pair me = x.first;
            while(j < rgt.sz && cmpP(rgt.ptr[j].first, me)<0)
                ++j;
            if(j < rgt.sz && cmpP(rgt.ptr[j].first, me)==0)
                ans = min(ans , 1LL * x.second * SQN + rgt.ptr[j].second);
        }
        if(ans >= (ll)1e15)
            ans = -1;
        printf("%lld\n" , ans);
    }
}
