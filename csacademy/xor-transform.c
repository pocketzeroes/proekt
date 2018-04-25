#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define MAXN 5000005
#define INF  1000000000
#define MOD  1000000007
#define F    first
#define S    second
typedef long long ll;
typedef unsigned long long ull;
int b[8400000];

ull x;
ull nextInt(){
    ull z = (x += 0x9E3779B97F4A7C15ULL);
    z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ULL;
    z = (z ^ (z >> 27)) * 0x94D049BB133111EBULL;
    return z ^ (z >> 31);
}
int mhm_random(){
    return 1 + (nextInt() >> 33);
}


int N, M, Q,h,len;


int main(){
    scanf("%d %d %d %llu", &N, &M, &Q, &x);
    int A[N][M];
void init(){
    for(int i=0; i<N; i++)
        for(int j=0; j<M; j++)
            b[i|j]^=A[i][j];
    len=0;
    h=1; 
    while(h<((N-1)|(M-1))) 
        h*=2,len++;
    for(int i=1; i<=len; i++){
        int s=1<<i;
        for(int j=0; j<h/s; j++)
            for(int k=0; k<s/2; k++)
                b[j*s+k+s/2]^=b[j*s+k];
    }
}
int query(int K){
    return b[K%h];
}
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            A[i][j] = mhm_random();
    init();
    ull hashSol = 0;
    for (int i = 1; i <= Q; i++)
        hashSol ^= (ull)i * query(mhm_random());
    printf("%llu\n", hashSol);
    return 0;
}
