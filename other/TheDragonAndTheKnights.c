#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<ctype.h>
typedef long long ll;
typedef struct{
  ll first;
  ll second;
}pair;
pair newPair(ll a, ll b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
int unique(pair*a, int len){
	int i, j;
	for (i = j = 0; i < len; i++)
		if(cmpP(&a[i], &a[j])!=0)
      a[++j] = a[i];
	return j + 1;
}

void scan(int*x){
  int ch, flag;
  while(!isdigit(ch = getchar()) && ch != '-');
  *x = (flag = ch == '-') ? 0 : ch - '0';
  while(isdigit(ch = getchar()))
    *x = (*x << 3) + (*x << 1) + ch - '0';
  if(flag)
    *x = -(*x);
}
enum{ maxn = 101, maxm = 50001};
int t, n, m, a[maxn], b[maxn], c[maxn], cnt;
pair h[maxm];//pll
int main(){
  scan(&t);
  while(t--){
    scan(&n), scan(&m);
    cnt = n + 1;
    for(int i = 0; i < n; ++i){
      scan(&a[i]), scan(&b[i]), scan(&c[i]);
      for(int j = 0; j < i; ++j)
        cnt += a[i] * b[j] != b[i] * a[j];
    }
    for(int i = 0; i < m; ++i){
      int x, y;
      scan(&x), scan(&y);
      h[i] =(pair){0, 0};
      for(int j = 0; j < n; ++j)
        if((ll)a[j] * x + (ll)b[j] * y + c[j] > 0){
          if(j < 50)
            h[i].first |= 1LL << j;
          else
            h[i].second |= 1LL << j - 50;
        }
    }
    qsort(h, m, sizeof(pair), cmpP);
    cnt -= unique(h, m);
    puts(cnt ? "VULNERABLE" : "PROTECTED");
  }
  return 0;
}
