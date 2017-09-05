#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#ifdef _WIN32
  #define inline static
#endif
typedef long long ll;
inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
///////////////////////////////////////////////

enum{ N = 2017};

char s[N][N];
int h[N][N], v[N][N], g[N][N], ul[N][N], dr[N][N], n, m;

long long ans = 0;
int bit[N];
vec rem[N];

void upd(int x, int val) {
  for (; x; x -= x &-x)
    bit[x] += val;
} 
int get(int x) {
  int ret = 0;
  for (; x < N; x += x&-x)
    ret += bit[x];
  return ret;
}
void process(int x, int y) {
  memset(bit, 0, sizeof bit);
  int z = 1;
  for (int i = 1;; i++, x++, y++) {
    if (x >= n || y >= m) break;
    upd(i, 1);
    int off=ul[x][y] + i;
    rem[off].ptr = pushback(rem[off].ptr, &rem[off].sz ,i);
    z = max(z, ul[x][y] + i);
    for(int q=0;q<rem[i].sz;q++){int d = rem[i].ptr[q];
      upd(d, -1);
    }
    ans += get(i-dr[x][y]+1);
  }
  for (int i= 1; i <= z; i++)
    rem[i].sz=0;
}
int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%s", s[i]);
    for (int j = 0; j < m; j++)
      s[i][j] -= '0';
  }
  for (int i = n-1; i >= 0; i--) {
    for (int j = m-1; j >= 0; j--) {
      v[i][j] = h[i][j] = g[i][j] = 0;
      if (!s[i][j]) continue;
      h[i][j] = 1 + (j+1 < m ? h[i][j+1] : 0);
      v[i][j] = 1 + (i+1 < n ? v[i+1][j] : 0);
      g[i][j] = 1 + (i+1 < n && j+1 < m ? g[i+1][j+1] : 0);
      ul[i][j] = min(h[i][j], min(v[i][j], g[i][j]));
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      v[i][j] = h[i][j] = g[i][j] = 0;
      if (!s[i][j]) continue;
      h[i][j] = 1 + (j-1 >= 0 ? h[i][j-1] : 0);
      v[i][j] = 1 + (i-1 >= 0 ? v[i-1][j] : 0);
      g[i][j] = 1 + (i-1 >= 0 && j-1 >= 0 ? g[i-1][j-1] : 0);
      dr[i][j] = min(h[i][j], min(v[i][j], g[i][j]));
    }
  }
  ans = 0;
  for (int i = 0; i < n; i++)
    process(i, 0);
  for (int j = 1; j < m; j++)
    process(0, j);
  printf("%lld\n", ans);
  return 0;
}




















































