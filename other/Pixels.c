#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

enum{ MAXN = 100005};
enum{ MAXB = 320   };
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
int n, m;
int*inp[MAXN];
int*ans[MAXN];
bool bs[3][MAXB][MAXB];
bool basis[MAXB][MAXB];
int sum[MAXB];
char buf[6];

void upload(bool*bs, int k){
  for(int i=0; i<m; i++){
    if(bs[i]){
      if(basis[i][i]){
        for(int z=0;z<320;z++)
          bs[z] ^= basis[i][z];
        k ^= sum[i];
      }
      else{
        for(int z=0;z<320;z++)
          basis[i][z] = bs[z];
        sum[i] = k;
        return;
      }
    }
  }
  if(k){
    puts("IMPOSSIBLE");
    exit(0);
  }
}
int*gauss(){
  int*dap = calloc(m, sizeof(int));
  for(int i=m-1; i>=0; i--){
    if(basis[i][i]){
      dap[i] = sum[i];
      for(int j=0; j<i; j++){
        if(basis[j][i])
          sum[j] ^= sum[i];
      }
    }
  }
  return dap;
}
void solve(){
  for(int i=0; i<m; i++)
    bs[0][i][i]=1;
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      memset(bs[(i+1)%3][j], 0, 320*sizeof(bool));
      if(i != 0){
        for(int z=0;z<320;z++)
          bs[(i+1)%3][j][z] = bs[(i+2)%3][j][z];
      }
      for(int k=-1; k<=1; k++){
        if(j + k < 0 || j + k >= m)
          continue;
        for(int z=0;z<320;z++)
          bs[(i + 1) % 3][j][z] ^= bs[i % 3][j + k][z];
      }
      if(inp[i][j])
        bs[(i + 1) % 3][j][m] = !bs[(i + 1) % 3][j][m];
    }
  }
  for(int i=0; i<m; i++){
    bool msk[320];
    for(int z=0;z<320;z++)
      msk[z] = bs[n%3][i][z];
    int cnst = msk[m];
    if(cnst)
      msk[m] = !msk[m];
    upload(msk, cnst);
  }
  for(int i=0; i<n; i++)
    ans[i] = calloc(m, sizeof(int));
  ans[0] = gauss();
  bool ok(int x, int y){
    return x >= 0 && x < n && y >= 0 && y < m;
  }
  for(int i=1; i<n; i++){
    for(int j=0; j<m; j++){
      ans[i][j] = inp[i-1][j];
      if(ok(i - 1, j - 1)) ans[i][j] ^= ans[i - 1][j - 1];
      if(ok(i - 1, j - 0)) ans[i][j] ^= ans[i - 1][j - 0];
      if(ok(i - 1, j + 1)) ans[i][j] ^= ans[i - 1][j + 1];
      if(ok(i - 2, j - 0)) ans[i][j] ^= ans[i - 2][j - 0];
    }
  }
}
int main(){
  scanf("%d %d", &n, &m);
  int foo[n*m]; clr(foo);
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      scanf("%s", buf);
      if(*buf == 'B')
        foo[i*m+j] = 1;
      else
        foo[i*m+j] = 0;
    }
  }
  if(n < m){
    for(int i=0; i<m; i++){
      inp[i] = calloc(n, sizeof(int));
      for(int j=0; j<n; j++){
        inp[i][j] = foo[i+j*m];
      }
    }
    swap(n, m);
    solve();
    swap(n, m);
    for(int i=0; i<n; i++){
      for(int j=0; j<m; j++){
        printf(ans[j][i] ? "P " : "A ");
      }
      puts("");
    }
  }
  else{
    for(int i=0; i<n; i++){
      inp[i]=calloc(m, sizeof(int));
      for(int j=0; j<m; j++)
        inp[i][j] = foo[i * m + j];
    }
    solve();
    for(int i=0; i<n; i++){
      for(int j=0; j<m; j++){
        printf(ans[i][j] ? "P " : "A ");
      }
      puts("");
    }
  }
  return 0;
}
