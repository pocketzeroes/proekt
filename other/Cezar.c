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
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

enum{ MAXN = 110};
enum{ SLOVA = 26};

int mat[SLOVA][SLOVA];

vec graf[MAXN];
int n;

char*unos  [MAXN];
char*glavni[MAXN];
int in [SLOVA];
int bio[SLOVA];

vec ispis;
int da;

int lcp(int a, int b){
  int kraj = fmin(strlen(glavni[a]), strlen(glavni[b]));
  int i = 0;
  for(; i < kraj; i++)
    if(glavni[a][i] != glavni[b][i]) 
      break;
  return i;
}
int pref(int a, int b){
  int x = lcp(a, b);
  if(x == strlen(glavni[a]))
    return 1;
  return 0;
}
void dodaj(int x, int y){
  if(mat[x][y])
    return;
  mat[x][y] = 1;
  graf[x].ptr = pushback(graf[x].ptr, &graf[x].sz, y);
  in[y]++;
}
void rek(int cvor){
  if(bio[cvor]){
    da = 1;
    return;
  }
  bio[cvor] = 1;
  for(int i = 0; i < graf[cvor].sz; i++)
    rek(graf[cvor].ptr[i]);
  bio[cvor] = 0;
}
void topoloski(int cvor){
  if(bio[cvor]) 
    return;
  bio[cvor] = 1;
  for(int i = 0; i < graf[cvor].sz; i++)
    topoloski(graf[cvor].ptr[i]);
  ispis.ptr = pushback(ispis.ptr, &ispis.sz, cvor);
}
int main(){
  scanf("%d", &n);
  for(int i=0; i<n; i++)
    unos[i] = getstr();
  for(int i=0; i<n; i++){
    int x;
    scanf("%d", &x);
    x--;
    glavni[i] = unos[x];
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j < i; j++){
      if(pref(i, j)){
        puts("NE");
        return 0;
      }
    }
  }
  for(int i=0; i<n-1; i++){
    if(pref(i, i + 1)) 
      continue;
    for(int j = 0; ; j++){
      if(glavni[i][j] != glavni[i + 1][j]){
        dodaj(glavni[i + 1][j] - 'a', glavni[i][j] - 'a');
        break;
      }
    }
  }
  for(int i = 0; i < SLOVA; i++){
    memset(bio, 0, sizeof(bio));
    da = 0;
    rek(i);
    if(da){
      puts("NE");
      return 0;
    }
  }
  memset(bio, 0, sizeof(bio));
  for(int i = 0; i < SLOVA; i++)
    if(!in[i])
      topoloski(i);
  puts("DA");
  int rj[MAXN];
  for(int i = 0; i < ispis.sz; i++)
    rj[ispis.ptr[i]] = i;
  for(int i = 0; i < SLOVA; i++)
    printf("%c", (char)(rj[i] + 'a'));
  puts("");
  return 0;
}
