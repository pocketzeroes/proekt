#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>



int N, M;
int A[2011], B[2011];
int G[4000000], GN;


int lower_bound(int*a, int n, int x) {
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x <= a[mid]) 
            h = mid;
        else
            l = mid + 1;
    }
    return l;
}
int cmp (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
void amax(int*x, int y){ 
    if(*x < y)
       *x = y;
}
int even(int n, int a[]) {
    int ret = 0;
    for(int i=0, i_len=(n); i<i_len; ++i) {
        int x = 0;
        for (int j=i; j+1<n; j+=2) {
            x ^= a[j] ^ a[j+1];
            amax(&ret, x);
        }
    }
    return ret;
}
int odd() {
    for(int i=0, i_len=(M); i<i_len; ++i) {
        int x = B[i];
        for (int j=i; j<M; j+=2) {
            G[GN++] = x;
            x ^= B[j+1] ^ B[j+2];
        }
    }
    qsort(G, GN, sizeof(int), cmp);
    int ans = 0;
    for (int t=29; t>=0; t--) {
        bool ok = false;
        for(int i=0, i_len=(N); i<i_len; ++i) {
            int x = A[i];
            for (int j=i; j<N; j+=2) {
                int y = (ans ^ (1<<t) ^ x) & ~((1<<t)-1);
                int k = lower_bound(G, GN, y);
                if (k < GN && (G[k] >> t) == (y >> t)) {
                    ok = true;
                    break;
                }
                x ^= A[j+1] ^ A[j+2];
            }
            if (ok)
                break;
        }
        if (ok) {
            ans |= 1<<t;
        }
    }
    return ans;
}
int main(){
    scanf("%d", &N);
    scanf("%d", &M);
    for(int i=0, i_len=(N); i<i_len; ++i)
      scanf("%d", A+i);
    for(int i=0, i_len=(M); i<i_len; ++i)
      scanf("%d", B+i);
    int ans = 0;
    amax(&ans, even(N, A));
    amax(&ans, even(M, B));
    amax(&ans, odd());
    printf("%d\n", ans);
}


















































