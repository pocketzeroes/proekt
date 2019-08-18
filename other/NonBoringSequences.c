#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cmp(const void*a, const void*b){ return ( *(int*)a - *(int*)b );}
int unique(int*a, int len){
	int i, j;
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j])
      a[++j] = a[i];
	return j + 1;
}

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

enum{ maxn = 200001};
int t, n, val[maxn], tot, que[maxn], pos[maxn], l[maxn], r[maxn];
bool boring(int L, int R){
  if(L >= R)
    return 0;
  for(int i = L, j = R; i <= j; ++i, --j){
    if(l[i] < L && r[i] > R)
      return boring(L, i - 1) || boring(i + 1, R);
    if(l[j] < L && r[j] > R)
      return boring(L, j - 1) || boring(j + 1, R);
  }
  return 1;
}
int main(){
  scanf("%d", &t);
  while(t--){
    tot = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i){
      scanf("%d", val + i);
      que[tot++] = val[i];
    }
    qsort(que, tot, sizeof(int), cmp);
    tot = unique(que, tot);
    memset(pos, 0, tot * sizeof(int));
    for(int i = 1; i <= n; ++i){
      val[i] = lower_bound(que, tot, val[i]);
      l[i] = pos[val[i]];
      pos[val[i]] = i;
    }
    memset(pos, 0, tot * sizeof(int));
    for(int i = n; i; --i){
      r[i] = pos[val[i]] ? pos[val[i]] : n + 1;
      pos[val[i]] = i;
    }
    puts(boring(1, n) ? "boring" : "non-boring");
  }
  return 0;
}
