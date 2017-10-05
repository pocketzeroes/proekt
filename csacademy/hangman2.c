#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef unsigned long long ull;
int Q, N, K, p[30009]; 
bool ans[30009]; 
ull pw[33], h[30009][33], hs[30009]; 
char* s[30009];



int cmp (const void*pa, const void*pb){
    int*ptra=(int*)pa;
    int*ptrb=(int*)pb;
    int k = *ptra;
    int l = *ptrb;
    return (hs[k] < hs[l])?-1:1;
}
void fill(bool*arr,int sz, bool val){
    for(int i=0;i<sz;i++)
        arr[i]=val;
}
ull hash_value(int p, int l, int r) {
    return h[p][r] - pw[r - l] * h[p][l];
}
char buff[100000];
int main() {
    pw[0] = 1;
    for (int i = 1; i <= 30; i++) 
        pw[i] = pw[i - 1] * 257;
    scanf("%d", &Q);
    while(Q--){
        scanf("%d %d", &N, &K);
        for (int i = 0; i < N; i++){
            scanf("%s", &buff);
            s[i] = strdup(buff);
        }
        fill(ans, N, false);
        if (K <= 2) 
            fill(ans, N, true);
        else if (N <= 1000) {
            for (int i = 0; i < N; i++) {
                for (int j = i + 1; j < N; j++) {
                    int cnt = 0;
                    for (int k = 0; k < K; k++) {
                        if (s[i][k] != s[j][k]) 
                            cnt++;
                        if (cnt >= 3) 
                            break;
                    }
                    if (cnt <= 2) 
                        ans[i] = ans[j] = true;
                }
            }
        }
        else {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < K; j++) {
                    h[i][j + 1] = h[i][j] * 257 + s[i][j];
                }
            }
            for (int i = 0; i < K; i++) {
                for (int j = i + 1; j < K; j++) {
                    for (int k = 0; k < N; k++) {
                        p[k] = k;
                        hs[k] = hash_value(k, 0, i) * pw[K - i - 1] + hash_value(k, i + 1, j) * pw[K - j] + hash_value(k, j + 1, K);
                    }
                    qsort(p, N, sizeof(int), cmp);
                    for (int k = 0; k < N; k++) {
                        if (k != 0 && hs[p[k]] == hs[p[k - 1]]) 
                            ans[p[k]] = true;
                        if (k != N - 1 && hs[p[k]] == hs[p[k + 1]]) 
                            ans[p[k]] = true;
                    }
                }
            }
        }
        for (int i = 0; i < N; i++) 
            printf("%d", ans[i]);
        puts("");
    }
    return 0;
}
























