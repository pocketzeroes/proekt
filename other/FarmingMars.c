#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{MAXN = 10005};
int N, M;
double A[MAXN];

int main(){
    scanf("%d %d", &N, &M);
    for(int i=0; i<N; i++)
        scanf("%lf", &A[i]);
    for(int qi = 0; qi < M; qi++){
        int l, r;
        scanf("%d %d", &l, &r);
        --l, --r;
        double maj = -1, cnt = 0;
        for(int i = l; i <= r; i++){
            if(cnt == 0){
                maj = A[i];
                cnt++;
            }
            else if(A[i] == maj)
                cnt++;
            else
                cnt--;
        }
        cnt = 0;
        for(int i = l; i <= r; i++) 
            if (A[i] == maj) 
                cnt++;
        puts(cnt >= (r - l + 1) / 2 + 1 ? "usable" : "unusable");
    }
    return 0;
}
