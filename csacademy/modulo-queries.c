#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}

int nr, N, Q, K, a[40009], lst[40009], id[40009], l[40009], r[40009], ans[209][40009];
enum{ MX =(int) 4e4 + 1};

void prec (int pos){
    memset (lst, 0, sizeof (lst));
    for (int i=l[pos]; i<=r[pos]; i++)
        lst[a[i]] = a[i];
    for (int i=1; i<=MX; i++)
        if (lst[i] != i)
            lst[i] = lst[i - 1];
    for (int K=1; K<=MX; K++)
        for (int cat=0; cat*K<=MX; cat++){
            int curr = lst[min (cat * K + K - 1, MX)];
            if (curr >= cat * K){
                curr -= cat * K;
                if (curr > ans[pos][K])
                    ans[pos][K] = curr;
            }
        }
}
int solve (int x, int y, int K){
    if (id[y] - id[x] <= 1){
        int maxi = 0;
        for (int i=x; i<=y; i++){
            int curr = a[i] % K;
            if (curr > maxi)
                maxi = curr;
        }
        return maxi;
    }
    int maxi = 0;
    for (int i=x; i<=r[id[x]]; i++){
        int curr = a[i] % K;
        if (curr > maxi)
            maxi = curr;
    }
    for (int i=l[id[y]]; i<=y; i++){
        int curr = a[i] % K;
        if (curr > maxi)
            maxi = curr;
    }
    for (int i=id[x]+1; i<id[y];i++)
        if (ans[i][K]>maxi)
            maxi=ans[i][K];
    return maxi;
}
int main (){
  scanf ("%d %d", &N, &Q);
  for (int i=1; i<=N; i++)
    scanf ("%d", &a[i]);
  while ((K + 1) * (K + 1) <= 4 * N && K + 1 <= N) K ++;
  for (int i=1; i<=N; i+=K){
    l[++nr] = i;
    for (int j=i; j<=i + K - 1 && j<=N; j++)
        id[j] = nr, r[nr] = j;
    prec (nr);
  }
  while (Q --){
    int x, y, k;
    scanf ("%d %d %d", &x, &y, &k);
    printf ("%d\n", solve (x, y, k));
  }
  return 0;
}
