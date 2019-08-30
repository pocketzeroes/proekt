#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<ctype.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b ); }
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

typedef struct{
  int first;
  int second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
int cmpP(pair a, pair b){
  if(a.first  != b.first) return(a.first  < b.first )?-1:1;
  if(a.second != b.second)return(a.second < b.second)?-1:1;
  return 0;
}

int get(){
	char ch; int v=0,f=0;
	while (!isdigit(ch=getchar())) if (ch=='-') break;
	if (ch=='-') f=1;else v=ch-48;
	while (isdigit(ch=getchar())) v=v*10+ch-48;
	return f?-v:v;
} 
enum{ maxn = 1000020};
int b[maxn];
int main() {
    vec H=newVec();
    int n = get();
    for (int i = 0; i < n; i++){
        int x = get();
        if(H.sz==0 || H.ptr[H.sz-1] != x)
            pb(H, x);
    }
    n = H.sz;
    for(int i = 0; i < n; i++)
        b[i] = H.ptr[i];
    qsort(b, n, sizeof(int), cmp);
    int sz = unique(b, n);
    vec posi[sz]; clr(posi);
    for(int i = 0; i < n; i++){
        H.ptr[i] = lower_bound(b, sz, H.ptr[i]);
        pb(posi[H.ptr[i]], i);
    }
    pair best[2] = {{0, n}, {0, n}};
    for(int h = 0; h < sz - 1; h++){
        pair nbest[2] = {best[0], best[1]};
        for (int i = 0; i < posi[h].sz; i++){
            int p = posi[h].ptr[i];
            if (p == n - 1 || H.ptr[p] + 1 != H.ptr[p + 1])
                continue;
            pair s=newpair(0, n);
            if (p != best[0].second)
                s = best[0];
            else
                s = best[1];
            s.first++, s.second = p + 1;
            if (posi[h + 1].sz == 1)
                s.second = n;
            if(cmpP(s, nbest[0])>0)
                nbest[1] = nbest[0], nbest[0] = s;
            else if(cmpP(s, nbest[1])>0)
                nbest[1] = s;
        }
        best[0] = nbest[0], best[1] = nbest[1];
    }
    printf("%d\n", n - 1 - best[0].first);
    return 0;
}
