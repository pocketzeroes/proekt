#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

enum{ MAXN = 100001};
int n;
int a   [MAXN];
int next[MAXN];
int last[MAXN];

void chkmax(int*x, int y){ 
  if (*x < y) 
      *x = y;
}

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%d", &a[i]);
        if (last[a[i]]){
            next[last[a[i]] - 1] = i; 
        }
        last[a[i]] = i + 1;
    }
    int left = 0;
    int cnt  = 0;
    while (left < n){
        int uk = left;
        int t  = left;
        while (uk <= left){
            chkmax(&t, next[uk]);
            chkmax(&left, t);
            uk++;
        }
        cnt++;
        left = uk;
    }
    printf("%d\n", cnt);
    return 0;
}



















































