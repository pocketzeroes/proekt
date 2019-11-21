#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define fill(arr, sz, val)do{     \
  for(int i=0; i<sz; i++)         \
    arr[i] = val;                 \
}while(0)

typedef long long ll;
typedef struct{
  __int128 first;
  __int128 second;
}pair;
pair newpair(__int128 a, __int128 b){
  return(pair){a,b};
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
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

////////////////////////////////////////////////////
enum{ N=524288, mod=(int)1e9};

__int128*sum;
__int128*sumone;
ll*      lazymul;

void build(int l, int r, int i){
    if(l==r){
        sum   [i] = l+1;
        sumone[i] = 1;
        return;
    }
    int m = (l+r)>>1;
    build(l,   m, 2*i);
    build(m+1, r, 2*i+1);
    sum   [i] = sum   [2*i] + sum   [2*i+1];
    sumone[i] = sumone[2*i] + sumone[2*i+1];
}
void init(){
    sum     = calloc(2*N, sizeof(__int128));
    sumone  = calloc(2*N, sizeof(__int128));
    lazymul = calloc(2*N, sizeof(ll)); fill(lazymul, 2*N, 1ll);
    build(0, N-1, 1);
}
void prop(int i){
    sum    [2*i  ] *= lazymul[i];
    sum    [2*i+1] *= lazymul[i];
    sumone [2*i  ] *= lazymul[i];
    sumone [2*i+1] *= lazymul[i];
    lazymul[2*i  ] *= lazymul[i];
    lazymul[2*i+1] *= lazymul[i];
    lazymul[i] = 1;
}
void update(int i){
    sum   [i] = sum   [2*i] + sum   [2*i+1];
    sumone[i] = sumone[2*i] + sumone[2*i+1];
}
void upd(bool ismul, int qs, int qe, int x, int l, int r, int i){
    if(qs>r||qe<l)
        return;
    if(qs<=l&&qe>=r){
        if(ismul){
            lazymul[i] *= x;
            sum    [i] *= x;
            sumone [i] *= x;
            return;
        }
        if(lazymul[i]%x==0){
            lazymul[i] /= x;
            sum    [i] /= x;
            sumone [i] /= x;
            return;
        }
    }
    prop(i);
    int m = (l+r)>>1;
    upd(ismul, qs, qe, x, l,   m, 2*i  );
    upd(ismul, qs, qe, x, m+1, r, 2*i+1);
    update(i);
}
pair getsums(int qs, int qe, int l, int r, int i){
    if(qs>r||qe<l)
        return newpair(0,0);
    if(qs<=l&&qe>=r)
        return newpair(sum[i],sumone[i]);
    prop(i);
    int m=(l+r)>>1;
    pair a = getsums(qs, qe, l,   m, 2*i  );
    pair b = getsums(qs, qe, m+1, r, 2*i+1);
    return newpair(a.first+b.first, a.second+b.second);
}

int main(){
    init();
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i=0; i<n; i++)
        scanf("%d", &arr[i]);
    vecp setup = newVecP();
    int smaller[n]; fill(smaller, n, n);
    int bigger [n]; fill(bigger , n, n);
#define setup_back setup.ptr[setup.sz-1]
    for(int i=0; i<n; i++){
        while(setup.sz && setup_back.first>arr[i]){
            smaller[setup_back.second] = i;
            setup.sz--;
        }
        pbp(setup, newpair(arr[i],i));
    }
    setup.sz = 0;
    for(int i=0; i<n; i++){
        while(setup.sz&&setup_back.first<arr[i]){
            bigger[setup_back.second] = i;
            setup.sz--;
        }
        pbp(setup, newpair(arr[i],i));
    }
    int dones[n+1]; clr(dones);
    int doneb[n+1]; clr(doneb);
    dones[n] = doneb[n] = 1;
    int sol = 0;
    for(int i=0; i<n; i++){
        int tr = i;
        while(1){
            if(dones[tr])
                break;
            dones[tr] = 1;
            upd(1, tr, smaller[tr]-1, arr[tr], 0, N-1, 1);
            tr = smaller[tr];
        }
        tr = i;
        while(1){
            if(doneb[tr])
                break;
            doneb[tr] = 1;
            upd(1, tr, bigger[tr]-1, arr[tr], 0, N-1, 1);
            tr = bigger[tr];
        }
        pair a = getsums(i, n-1, 0, N-1, 1);
        sol = (a.first-a.second*i+sol) % mod;
        upd(0, i, smaller[i]-1, arr[i], 0, N-1, 1);
        upd(0, i, bigger [i]-1, arr[i], 0, N-1, 1);
    }
    printf("%d\n", sol);
    return 0;
}
