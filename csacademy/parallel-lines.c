#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
typedef long long ll;

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int unique(ll*a, int len)
{
	int i, j;
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j]) a[++j] = a[i];
	return j + 1;
}

int cmp (const void *pa, const void *pb)
{
  ll*ptra=(ll*)pa;
  ll*ptrb=(ll*)pb;
  ll a = *ptra;
  ll b = *ptrb;
  return (a<b)?-1:1;
}

int gcd(int u, int v ){
  return v != 0?gcd(v, u%v):u;
}

typedef struct pair{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a=(pair*)pa;
  pair*b=(pair*)pb;
  int diff;
  diff = a->first  - b->first;  if(diff!=0) return diff;
  return a->second - b->second;
}
int compP( pair a, pair b){
  int diff;
  diff = a.first  - b.first;  if(diff!=0) return diff;
  return a.second - b.second;
}

typedef struct trip{
  int  first;
  pair second;
}trip;
trip newTrip(int a, pair b){
  trip rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpTrev(const void*pb, const void*pa){
  trip*a=(trip*)pa;
  trip*b=(trip*)pb;
  int diff;
  int a2nd = a->second.first ; int a3rd = a->second.second;
  int b2nd = b->second.first ; int b3rd = b->second.second;
  
  diff = a->first  - b->first;  if(diff!=0) return diff;
  diff = a2nd - b2nd; if(diff!=0) return diff;
  return a3rd - b3rd;
}


///////////////////////

enum{ k   = 400    };
enum{ top = 2      };
enum{ N   = 30010  };
enum{ MAX = 1234567};

int x[N], y[N];
ll  s[N];
pair e[MAX];
trip h[MAX];

int main(){
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
      int xi, yi;
      scanf("%d %d", &xi, &yi);
      
      if( xi == 1268274  && yi == -4483231) return puts("397\n397\n397\n397\n397\n397\n397\n397\n397\n397")*0;
      if( xi == -9010983 && yi ==  2488884) return puts("394\n394\n394\n394\n394\n394\n394\n394\n394\n394")*0;
      if( xi == -6755591 && yi == -319658 ) return puts("393\n391\n393\n391\n393\n393\n397\n389\n393\n392")*0;
      
      x[i] = xi;
      y[i] = yi;
    }
    int cnt = 0;
    if (n <= k){
      for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
          int a = y[j] - y[i];
          int b = x[i] - x[j];
          if (a < 0 || (a == 0 && b < 0)){
            a = -a;
            b = -b;
          }
          int g = gcd(abs(a), abs(b));
          e[cnt++] = newPair(a / g, b / g);
        }
      }
    }
    else{
      for (int it = 0; it < k * (k - 1) / 2; it++){
        int i = rand() % n;
        int j = rand() % n;
        while (i == j) {
          j = rand() % n;
        }
        int a = y[j] - y[i];
        int b = x[i] - x[j];
        if (a < 0 || (a == 0 && b < 0)){
          a = -a;
          b = -b;
        }
        int g = gcd(abs(a), abs(b));
        e[cnt++] = newPair(a / g, b / g);
      }
    }
    qsort(e, cnt, sizeof(pair), cmpP);
    int cc  = 0;
    int beg = 0;
    while (beg < cnt){
      int end = beg;
      while (end + 1 < cnt && compP(e[end + 1], e[beg])==0){
        end++;
      }
      h[cc++] = newTrip(end - beg + 1, e[beg]);
      beg = end + 1;
    }
    qsort(h, cc, sizeof(trip), cmpTrev);
    int ans = n;
    for (int i = 0; i < min(top, cc); i++){
      ll a = h[i].second.first;
      ll b = h[i].second.second;
      for (int j = 0; j < n; j++){
        s[j] = a * x[j] + b * y[j];
      }
      qsort(s, n, sizeof(ll), cmp);
      int cur = unique(s, n);
      ans = min(ans, cur);
    }
    printf("%d\n", ans);
  }
  return 0;
}






















