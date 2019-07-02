#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
//////////////////////////////
enum{ MAXN = 10000};

bool ret;
vec g[MAXN];
int n;
int cad[MAXN];

int letra (char c){
  if (c == 'A') return 0;
  if (c == 'G') return 1;
  if (c == 'T') return 2;
  if (c == 'C') return 3;
  puts("error");
  return -3;
}
int m[MAXN];

int yaestaria[MAXN], ya[MAXN];
vec vere;
bool sepodra;

void dfs (int v, int label){
  if (!sepodra)
    return;
  if ((yaestaria[v] == 0) && !ya[v]) {
    vere.ptr = pushback(vere.ptr, &vere.sz, v);
    yaestaria[v] = 1;
  }
  if (m[v] >= 0)
    sepodra = sepodra && (m[v] == label);
  else{
    if (label == (cad[v] + 2) % 4) {
      sepodra = false;
      return;
    }
    m[v] = label;
    for (int i = 0; i < g[v].sz; i++)
      dfs(g[v].ptr[i], label);
    if (label != cad[v]){
      if (v > 0)
        dfs(v - 1, cad[v - 1]);
      if (v + 1 < n)
        dfs(v + 1, cad[v + 1]);
    }
  }
  return;
}
void haz (int x){
  if (ret)
    return;
  if (x == n){
    ret = true;
    return;
  }
  if (m[x] >= 0 || g[x].sz == 0){
    haz(x + 1);
    return;
  }
  for (int c = 0; !ret && c < 4; c++)
    if (c != (cad[x] + 2) % 4){
      vere.sz=0;
      memset (yaestaria, 0, sizeof(yaestaria));
      sepodra = true;
      dfs(x, c);
      if (sepodra){
        for (int i = 0; i < vere.sz; i++)
          ya[vere.ptr[i]] = 1;
        haz(x + 1);
      }
      for (int i = 0; i < vere.sz; i++){
        ya[vere.ptr[i]] = 0;
        m[vere.ptr[i]] = -1;
      }
    }
  return;
}
int main(){
  int t, taml;
  for(;;){
    scanf("%d %d", &n, &t);
    if(n == 0)
      break;
    char*s=getstr();
    for (int i = 0; i < n; i++)
      cad[i] = letra(s[i]);
    for (int i = 0; i < n; i++)
      g[i].sz=0;
    while (t--){
      scanf("%i:", &taml);
      int v[taml];
      for(int i = 0; i < taml; i++)
        scanf("%d", &v[i]);
      for(int i = 0; i < taml - 1 - i; i++){
        g[v[i]].ptr = pushback(g[v[i]].ptr, &g[v[i]].sz, v[taml - 1 - i]);
        g[v[taml-1-i]].ptr = pushback(g[v[taml-1-i]].ptr, &g[v[taml-1-i]].sz, v[i]);
      }
    }
    ret = false;
    for (int i = 0; i < n; i++){
      m [i] = -1;
      ya[i] = 0;
    }
    haz(0);
    if(ret)
      puts("YES");
    else
      puts("NO");
  }
  return 0;
}
