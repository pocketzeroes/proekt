#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;

const ll mod = 1000000007ll;

int lower_bound(int*a, int n, int x){
  int l = 0;
  int h = n;
  while (l < h){
    int mid = (l + h) / 2;
    if (x <= a[mid]) 
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}
int main(){
    int N, L;
    scanf("%d %d", &N, &L);
    int seq [L]; clr(seq );
    int used[N]; clr(used);
    for (int i = 0; i < (L); ++i)
      scanf("%d", &seq[i]), --seq[i], used[seq[i]] = 1;
    for (int i = 0; i < (L-1); ++i)
      if(seq[i] >= seq[i+1]){
        puts("0");
        return 0;
      }
    if(seq[L-1] != N-1){
        puts("0");
        return 0;
    }
    ll  res    = 1;
    int before = 0;
    for(int i = N; i--;)
      if(!used[i]){
        int pos = lower_bound(seq, L, i);
        res = res * (L-pos + before) % mod;
        before++;
      }
    printf("%lld\n", res);
    return 0;
}
