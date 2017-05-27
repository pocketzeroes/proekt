#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long i64;

i64 min(i64 a,i64 b){return a<b?a:b;}
i64 max(i64 a,i64 b){return a>b?a:b;}

typedef struct pair{
  i64 first;
  i64 second;
}pair;
pair newPair(i64 a, i64 b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushback(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct vecS {
	pair*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int cmpP(const void*pa,const void*pb)
{
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first == b->first)return (a->second < b->second)?-1:1;
  return (a->first < b->first)?-1:1;
}
void swap(pair*nums, int i, int j) {
  pair t  = nums[i];
  nums[i] = nums[j];
  nums[j] = t;
}
void reverse(pair*nums,int start,int end){
  while( start < end) {
    swap(nums, start, end);
    start++;
    end  --;
  }
}




////////////
vec a, b,  sta, stb;
i64 ans;

void solve(int la,int ra,int lb,int rb){
  if(la==ra)return;
  int ma=(la+ra)/2;
  pair p=sta.ptr[ma];
  int mb=-1;
  i64 res=-1;
  for(int i=lb;i<rb;i++){
    pair q=stb.ptr[i];
    if( q.first<p.first || q.second< p.second)continue;
    i64 cres=(q.second-p.second)*(q.first-p.first);
    if(cres>res){
      res=cres;
      mb=i;
    }
  }
  ans=max(ans, res);
  if(mb==-1){
    mb=lb;
    while(mb<rb&&stb.ptr[mb].first<sta.ptr[ma].first)++mb;
  }
  solve(la, ma, lb, mb+1);
  solve(ma+1,ra, mb,  rb);
}
int main(){
  i64 n,m;
  scanf("%lld %lld", &n, &m);
  for(i64 i=0;i<n;i++){
    i64 x,y; scanf("%lld %lld", &x,&y);
    a.ptr=pushback(a.ptr, &a.sz, newPair(x,y));
  }
  for(i64 i=0;i<m;i++){
    i64 x,y; scanf("%lld %lld", &x,&y);
    b.ptr=pushback(b.ptr, &b.sz, newPair(x,y));
  }
  qsort(a.ptr, a.sz, sizeof(pair), cmpP);
  qsort(b.ptr, b.sz, sizeof(pair), cmpP);
  reverse(b.ptr, 0, b.sz-1);
  for(int i=0;i<a.sz;i++){pair w = a.ptr[i];
    if(sta.sz>0 && sta.ptr[sta.sz-1].second<=w.second)continue;
    sta.ptr = pushback(sta.ptr, &sta.sz ,w);
  }
  for(int i=0;i<b.sz;i++){pair w=b.ptr[i];
    if(stb.sz>0 && stb.ptr[stb.sz-1].second>=w.second)continue;
    stb.ptr = pushback(stb.ptr, &stb.sz ,w);
  }
  reverse(stb.ptr, 0, stb.sz-1);
  solve(0, sta.sz, 0, stb.sz);
  printf("%lld\n", ans );
  return 0;
}




















