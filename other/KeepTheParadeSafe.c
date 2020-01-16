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
typedef long long ll;
#define rep(i,n) for(int (i)=0;(i)<(int)(n);(i)++)
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define fi first
#define se second
#define x first
#define y second

typedef struct{
  ll first, second;
}pair;
pair newP(int a, int b){
  return(pair){a,b};
}
typedef pair P;
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
///////////////////////////////-----------------------------

P SUB(P a, P b){
  return(P){a.x-b.x, a.y-b.y};
}
ll dot(P a, P b){
  return a.x*b.x + a.y*b.y;
}
ll cross(P a, P b){
  return a.x*b.y - a.y*b.x;
}
ll norm(P a){
  return a.x*a.x + a.y*a.y;
}
int ccw(P a, P b, P c){
  b = SUB(b, a);
  c = SUB(c, a);
  if(cross(b,c) > 0)return+1;
  if(cross(b,c) < 0)return-1;
  if(dot  (b,c) < 0)return+2;
  if(norm(b)<norm(c))return-2;
  return 0;
}
int hullsz;
P*convexHull(P*ps, int pssz){
  int n=pssz,k=0;
  qsort(ps, pssz, sizeof(P), cmpP);
  P*ch = calloc(2*n, sizeof(P));
  for(int i=0; i<n; ch[k++]=ps[i++]){
    while(k>=2&&ccw(ch[k-2], ch[k-1], ps[i])<=0)--k;
  }
  for(int i=n-2, t=k+1; i>=0; ch[k++]=ps[i--]){
    while(k>=t && ccw(ch[k-2], ch[k-1], ps[i])<=0) --k;
  }
  hullsz = k-1;
  return ch;
}
int inPolygon(P*ps, P p){
  int n = hullsz;
  bool in = false;
  rep(i,n){
    P a = SUB(ps[i], p);
    P b = SUB(ps[(i+1)%n], p);
    if(cross(a,b)==0 && dot(a,b)<=0)return 2;
    if(a.y>b.y)swap(a,b);
    if( (a.y*b.y<0 ||(a.y*b.y<=0&&b.y>0))&&cross(a,b)<=0)in=!in;
  }
  return in;
}
P read(){
  ll x, y;
  scanf("%lld %lld", &x, &y);
  return newP(x, y);
}
int solve(){
  int n;
  scanf("%d", &n);
  P t[n];
  rep(i,n) t[i] = read();
  int s;
  scanf("%d", &s);
  P c[s];
  rep(i,s) c[i] = read();
  P*h = convexHull(t, n);
  int hsz = hullsz;
  int COUNT(){
    int ans=0;
    rep(i,s){
      if(inPolygon(h,c[i])!=0)++ans;
    }
    return ans;
  }
  if(hsz<=2)return 0;
  if(hsz>=4)return COUNT();
  assert(hsz==3);
  bool exist=false;
  rep(i,n){
    if(inPolygon(h,t[i])==1)exist=true;
  }
  if(exist)return COUNT();
  int ect[3]; clr(ect);
  rep(i,n){
    bool vertex = false;
    rep(j,3)if(cmpP(&h[j], &t[i])==0)vertex=true;
    if(vertex)continue;
    int ct=0;
    int idx=-1;
    rep(j,3){
      P p=h[j],q=h[(j+1)%3];
      if(ccw(p,q,t[i])==0){
        ++ct;
        idx=j;
      }
    }
    assert(ct<=1);
    if(ct)ect[idx]++;
  }
  int z=0;
  rep(i,3)z+=(ect[i]==0);
  if(z>=2)return 0;
  if(z==0)return COUNT();
  P dame = newP(0,0);
  rep(i,3)if(ect[i]==0)dame=h[(i+2)%3];
  //--
  vecp nh = newVecP();
  rep(i,n)if(cmpP(&t[i], &dame)!=0) pbp(nh, t[i]);
  h = convexHull(nh.ptr, nh.sz);
  assert(hullsz==4);
  return COUNT();
}
int main(){
  printf("%d\n", solve());
  return 0;
}
