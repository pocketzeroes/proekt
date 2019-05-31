#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cmpr(const void *b, const void *a){
   return ( *(int*)a - *(int*)b );
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
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef long long ll;

inline ll max(ll a, ll b){return a>b?a:b;}
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

enum{ MAX_S = 300};

ll*sum;
typedef struct{
    int a, b, t;
    ll c;
}Curve;
Curve newCurve(int aa, int bb, ll cc){
    Curve rez;
    rez.a=aa; 
    rez.b=bb; 
    rez.c=cc;
    return rez;
}
ll f(Curve c, int x){
    return x >= c.a ? 0 : (sum[c.a-x-1] + c.c);
}
int ot(Curve c, Curve rhs){
    int lo = c.b, 
        hi = c.a-1;
    while(lo < hi){
        int m = (lo+hi) / 2;
        if (f(c, m) >= f(rhs, m))
            hi = m;
        else
            lo = m+1;
    }
    return hi;
}

int main(){
    int N = in_nextInt();
    int K = in_nextInt();
    vec jewels[MAX_S+1]; memset(jewels, 0, sizeof(jewels));
    for (int i=0; i<N; i++){
        int s = in_nextInt();
        int v = in_nextInt();
        jewels[s].ptr = pushback(jewels[s].ptr, &jewels[s].sz, v);
    }
    for(int x=0; x<MAX_S+1; x++)
        qsort(jewels[x].ptr, jewels[x].sz, sizeof(int), cmpr);//reverse
    ll    dp[K+1]; memset(dp, 0, sizeof(dp));
    Curve dq[K+1]; memset(dq, 0, sizeof(dq));
    for (int s=0; s<MAX_S+1; s++){
        if (jewels[s].sz > 0){
            int L = jewels[s].sz;
            if(sum){free(sum);sum=NULL;}
            sum = calloc(L, sizeof(ll));
            for(int i=0; i<L; i++)
                sum[i] = jewels[s].ptr[i];
            for(int i=0; i+1<L; i++)
                sum[i+1] += sum[i];
            for(int m=0; m<s; m++){
                int start=K-m, j=1, fptr = 0, bptr = 0;
                for (int i=0; start-i*s>=0; i++){
                    while (bptr-fptr > 0 && dq[fptr].a <= i)
                        fptr++;
                    while (j-i <= L && (start-j*s) >= 0){
                        int pos = start-j*s;
                        Curve nc = newCurve(j, i, dp[pos]);
                        if (fptr < bptr)
                            dq[bptr-1].t = ot(nc, dq[bptr-1]);
                        while (bptr-fptr > 1 && dq[bptr-1].t <= dq[bptr-2].t){
                            bptr--;
                            dq[bptr-1].t = ot(nc, dq[bptr-1]);
                        }
                        dq[bptr++] = nc;
                        j++;
                    }
                    while (bptr-fptr > 1 && f(dq[fptr], i) <= f(dq[fptr+1], i))
                        fptr++;
                    if (fptr < bptr){
                        int pos = start-i*s;
                        dp[pos] = max(dp[pos], f(dq[fptr], i));
                    }
                }
            }
        }
    }
    printf("%lld", dp[1]);
    for (int x=2; x<=K; x++)
        printf(" %lld", dp[x]);
    puts("");
    return 0;
}
