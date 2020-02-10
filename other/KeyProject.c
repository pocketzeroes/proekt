#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}
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

typedef long long ll;
enum{N=805,inf=1000000010};
int n,m,i,x,y,ca[N],cb[N],ata[N],atb[N],va[N],vb[N];
int d[N],fl[N],fr[N];
vec a[N],b[N];
ll ans;

inline void fix(int x){
  if(ata[x]>=ca[x])va[x]=inf;else va[x]=a[x].ptr[ata[x]];
  if(atb[x]>=cb[x])vb[x]=inf;else vb[x]=b[x].ptr[atb[x]];
}
inline void aug(){
  int i,best=inf,A,B,o,tmp;
  for(tmp=inf,i=1;i<=n;i++){
    if(va[i]<tmp){
      tmp=va[i];
      o=i;
    }
    if(tmp+vb[i]<best){
      best=tmp+vb[i];
      A=o;
      B=i;
    }
    if(tmp<inf&&i<n){
      if(fr[i])tmp-=d[i];
      else tmp+=d[i];
    }
  }
  for(tmp=inf,i=n;i;i--){
    if(va[i]<tmp){
      tmp=va[i];
      o=i;
    }
    if(tmp+vb[i]<best){
      best=tmp+vb[i];
      A=o;
      B=i;
    }
    if(tmp<inf&&i>1){
      if(fl[i-1])tmp-=d[i-1];
      else tmp+=d[i-1];
    }
  }
  ans+=best;
  printf("%lld\n",ans);
  ata[A]++,atb[B]++;
  fix(A),fix(B);
  if(A<B)for(i=A;i<B;i++){
    if(fr[i])fr[i]--;
    else fl[i]++;
  }
  if(A>B)for(i=B;i<A;i++){
    if(fl[i])fl[i]--;
    else fr[i]++;
  }
}
int main(){
  scanf("%d %d", &n, &m);
  for(i=1;i<n ;i++)
    scanf("%d", &d[i]);
  for(i=1;i<=m;i++){scanf("%d %d", &x, &y); pb(a[x], y);}
  for(i=1;i<=m;i++){scanf("%d %d", &x, &y); pb(b[x], y);}
  for(i=1;i<=n;i++){
    qsort(a[i].ptr, a[i].sz, sizeof(int), cmp);
    qsort(b[i].ptr, b[i].sz, sizeof(int), cmp);
    ca[i]=a[i].sz;
    cb[i]=b[i].sz;
    fix(i);
  }
  while(m--)
    aug();
  return 0;
}
