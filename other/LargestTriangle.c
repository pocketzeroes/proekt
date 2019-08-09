#include<stdio.h> // largest triangle
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

ll seen_largest_area;
typedef struct{
  ll x, y;
}pt;
pt newpt(ll x, ll y){
  return(pt){x,y};
}
pt opAdd(pt t, pt p){
  return newpt(t.x+p.x, t.y+p.y);
}
pt opSub(pt t, pt p){
  return newpt(t.x-p.x, t.y-p.y);
}
int cmpPt(const void*pa, const void*pb){
  pt*t=(pt*)pa;
  pt*p=(pt*)pb;
  if(t->x != p->x) return(t->x < p->x)?-1:1;
  if(t->y != p->y) return(t->y < p->y)?-1:1;
  return 0;
}
int unique(pt*a, int len){
	int i, j;
	for(i = j = 0; i < len; i++)
		if(cmpPt(&a[i], &a[j])!=0)
      a[++j] = a[i];
	return j + 1;
}
void swap(pt*nums, int i, int j) {
   pt t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(pt*nums, int start, int end){
    while( start < end){
        swap(nums, start, end);
        start++;
        end  --;
    }
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pt*pushbackPt(pt*array, int *size, pt value){
    pt*output = resizeArray(array, pt, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	pt*ptr;
	int sz;
}vecpt;
vecpt newVecPt(){
	vecpt rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


ll cross(pt p, pt q){
  return p.x * q.y - p.y * q.x;
}
ll Triangle(pt A, pt B, pt C){
  ll v = cross(A, B) + cross(B, C) + cross(C, A);
  v = v > 0 ? v : -v;
  seen_largest_area = max(seen_largest_area, v);
  return v;
}
vecpt ComputeConvexHull(pt*points, int psz){
  vecpt hull = newVecPt();
  for(int z=0; z<psz; z++){pt p = points[z];
    while(hull.sz >= 2 && cross(opSub(hull.ptr[hull.sz-1], hull.ptr[hull.sz-2]), opSub(p, hull.ptr[hull.sz-1])) <= 0)
      hull.sz--;
    hull.ptr = pushbackPt(hull.ptr, &hull.sz, p);
  }
  return hull;
}
int main(){
  int N;
  scanf("%d", &N);
  pt p[N];
  int psz=N;
  for(int i=0; i<N; i++)
    scanf("%lld %lld", &p[i].x, &p[i].y);
  qsort(p, N, sizeof(pt), cmpPt); 
  psz = unique(p, N);    
  vecpt lower_hull = ComputeConvexHull(p, psz); 
  reverse(p, 0, psz-1); 
  vecpt upper_hull = ComputeConvexHull(p, psz); 
  for(size_t i=1; i+1<upper_hull.sz; i++)
    lower_hull.ptr = pushbackPt(lower_hull.ptr, &lower_hull.sz, upper_hull.ptr[i]);
  size_t M = lower_hull.sz;
  for(size_t i=0; i<M; i++)
    lower_hull.ptr = pushbackPt(lower_hull.ptr, &lower_hull.sz, lower_hull.ptr[i]);
  seen_largest_area = 0;
  for(size_t i=0; i<M; i++){
    for(size_t j=i+1, k=j; j<i+M; j++){
      while(k < i + M && Triangle(lower_hull.ptr[i], lower_hull.ptr[j], lower_hull.ptr[k+1]) > 
                         Triangle(lower_hull.ptr[i], lower_hull.ptr[j], lower_hull.ptr[k]  )  )
        ++k;
    }
  }
  printf("%.9f\n", (double)seen_largest_area / 2.0);
  return 0;
}
