//test 19 wa
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}


#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef struct vecS {
  int*ptr;
  int sz;
  int second;
}vec;
vec newVec() {
  vec rez;// = malloc(sizeof(vec));
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}


enum{ N = 1234567};
char str[10][N];
char s[N];
int p[N];
vec a[N];
int cmp(const void*pa,const void*pb){
  vec*a=(vec*)pa;
  vec*b=(vec*)pb;
  int msz = min(a->sz, b->sz);
  for(int i=0;i < msz; i++){
    if(a->ptr[i] != b->ptr[i]) return (a->ptr[i] < b->ptr[i])?-1:1;
  }
  if(a->sz!=b->sz)return (a->sz < b->sz)?-1:1;
  if(a->second == b->second)return 0;
  return (a->second < b->second)?-1:1;
}
void printarr(int sz){
  for(int i=0;i<sz;i++){vec el = a[i];
    printf("int=%d;", el.second );
    printf("arr=");
    for(int z=0; z<el.sz; z++){int e = el.ptr[z];
      printf("%d ", e);
    }
    puts("");
  }
}
int main(){
  int n, cnt;
  scanf("%d %d", &n, &cnt);
  int len;
  for (int i = 0; i<cnt; i++) {
    scanf("%s", str[i]);
    len =(int) strlen(str[i]);
    for (int j = 1; j <= len; j++) {
      s[j] = str[i][j - 1];
    }
    int k = 0;
    p[1] = 0;
    for (int j = 2; j <= len; j++) {
      while (k>0 && s[j] != s[k + 1]) {
        k = p[k];
      }
      if (s[j] == s[k + 1]) {
        k++;
      }
      p[j] = k;
    }
    a[i].sz=0; free(a[i].ptr); a[i].ptr=NULL;
    int j = len;
    while (j>0 && 2 * len - j <= n){
      a[i].ptr = pushback(a[i].ptr, &a[i].sz, j);
      j = p[j];
    }
    a[i].second = i;
  }
//  puts("before sort");printarr(cnt);
  qsort(a, cnt, sizeof(vec), cmp);
//  puts("after  sort");printarr(cnt);
  for (int i = 0; i<cnt; i++) {
		int id = a[i].second;
    printf("%s\n", str[id]);
  }
  return 0;
}



















































