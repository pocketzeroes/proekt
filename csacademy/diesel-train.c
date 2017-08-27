#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}
int Read(){
  int n;
  scanf("%d", &n);
  return n;
}

enum{ MAXN = 100005};
int a[MAXN], n, d, l;
ll ans;

int main(){
    d = Read(), l = Read(), n = Read();
    for (int i = 1; i <= n; i ++)
        a[i] = Read();
    qsort(a+1, n, sizeof(int), cmp);
    a[n + 1] = d;
    for (int i = 1; i <= n + 1; i ++){
        int len = a[i] - a[i - 1];
        if (len <= l)
            continue;
        ans += 1LL * (len - l) * (len - l);
    }
    return printf("%lf\n", (double)ans / (4LL * d)), 0;
}




















































