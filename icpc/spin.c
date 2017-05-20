#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
typedef long long ll;
typedef struct PointS{
  ll x, y;
}Point;
Point newPoint(int x, int y){
  Point rez;
  rez.x=x;
  rez.y=y;
  return rez;
}
Point operatorSub(Point a, Point b){return newPoint(a.x-b.x, a.y-b.y); }
bool  operatorEqu(Point a, Point b){return a.x == b.x && a.y == b.y;}
Point slope(Point p){
  return (p.x < 0 || p.x == 0 && p.y < 0) ? newPoint(-p.x, -p.y) : newPoint(p.x, p.y);
}
ll crossp( Point a,  Point b){
  return (ll)a.x*b.y - (ll)a.y*b.x;
}
ll dotp( Point a,  Point b) {
  return (ll)a.x*b.x + (ll)a.y*b.y;
}
int xcmp(const void*pa,const void*pb)
{
  Point*ptra=(Point*)pa;
  Point*ptrb=(Point*)pb;
  Point a = *ptra;
  Point b = *ptrb;
  return(a.x < b.x || a.x == b.x && a.y < b.y)?-1:1;
}
bool slopecmp( Point a,  Point b) {
  return (ll)a.y*b.x < (ll)b.y*a.x;
}
typedef struct pair{
    Point first;
    int second;
}pair;
pair newPair(Point a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
int eventcmp(const void*pa,const void*pb)
{
  pair*a=(pair*)pa;
  pair*b=(pair*)pb;
  if (slopecmp(a->first, b->first))
    return -1;
  if (slopecmp(b->first, a->first))
    return  1;
  return(a->second < b->second)?-1:1;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Point *pushbackPt(Point *array, int *size, Point value) {
    Point *output = resizeArray(array, Point, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	Point*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
pair *pushbackP(pair *array, int *size, pair value) {
    pair *output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct pvecS {
	pair*ptr;
	int sz;
}pvec;
pvec newPvec() {
	pvec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
vec ConvexHull(vec p){
  qsort(p.ptr, p.sz, sizeof(Point), xcmp);
  vec top=newVec();top.ptr=pushbackPt(top.ptr, &top.sz, p.ptr[0]);
  vec bot=newVec();bot.ptr=pushbackPt(bot.ptr, &bot.sz, p.ptr[0]);
  for (int i = 1; i < p.sz; i++){
    if(operatorEqu(p.ptr[i] , p.ptr[i-1]))
      continue;
    while(top.sz > 1 && crossp(operatorSub(p.ptr[i],top.ptr[top.sz-2]), operatorSub(top.ptr[top.sz-1],top.ptr[top.sz-2])) <= 0) top.sz--;
    while(bot.sz > 1 && crossp(operatorSub(p.ptr[i],bot.ptr[bot.sz-2]), operatorSub(bot.ptr[bot.sz-1],bot.ptr[bot.sz-2])) >= 0) bot.sz--;
    top.ptr=pushbackPt(top.ptr, &top.sz,p.ptr[i]);
    bot.ptr=pushbackPt(bot.ptr, &bot.sz,p.ptr[i]);
  }
  for (int i = top.sz-2; i >= 1; i--)
    bot.ptr=pushbackPt(bot.ptr, &bot.sz, top.ptr[i]);
  return bot;
}
bool InsideHull(vec hull, Point p, int*first, int*last){
 *first = 0;
 *last  = 0;
  if (hull.sz == 1)
    return operatorEqu(p, hull.ptr[0]);
  int base = 0;
  if (crossp(operatorSub(hull.ptr[0],p), operatorSub(hull.ptr[1],p)) == 0) {
    if (hull.sz == 2)
      return dotp(operatorSub(p,hull.ptr[0]), operatorSub(hull.ptr[1],hull.ptr[0]) ) >= 0 && dotp(operatorSub(p,hull.ptr[1]), operatorSub(hull.ptr[0],hull.ptr[1]) ) >= 0;
    if(operatorEqu(p , hull.ptr[1]))
      return true;
    base++;
  }
  int H = hull.sz;
  int sgn = (crossp(operatorSub(hull.ptr[base%H],p), operatorSub(hull.ptr[(base+1)%H],p) ) > 0) ? 1 : -1;
  int lo = base+1, hi = base + hull.sz-1;
  while (hi > lo){
    int mid = (lo+hi)/2;
    if(crossp(operatorSub(hull.ptr[mid%H],p), operatorSub(hull.ptr[(mid+1)%H],p) ) * sgn < 0)
      hi = mid;
    else if (crossp(operatorSub(hull.ptr[mid%H],p), operatorSub(hull.ptr[(base+1)%H],p) ) * sgn > 0)
      hi = mid;
    else
      lo = mid+1;
  }
  if (crossp(operatorSub(hull.ptr[lo%H],p), operatorSub(hull.ptr[(lo+1)%H],p) ) * sgn >= 0)
    return true;
  if(sgn > 0) *last  = base = lo%H;
  else        *first = base = lo%H;
  sgn = -sgn;
  lo = base+1, hi = base + hull.sz-1;
  while (hi > lo) {
    int mid = (lo+hi)/2;
    if (crossp(operatorSub(hull.ptr[mid%H],p), operatorSub(hull.ptr[(mid+1)%H],p) ) * sgn < 0)
      hi = mid;
    else if (crossp(operatorSub(hull.ptr[mid%H],p), operatorSub(hull.ptr[(base+1)%H],p) ) * sgn > 0)
      hi = mid;
    else
      lo = mid+1;
  }
  if(sgn > 0) *last  = lo%H;
  else        *first = lo%H;
  return false;
}
int main() {
  int N, a, b, c;
  scanf("%d", &N);
  do{
    vec Pyes=newVec();
    vec Pno =newVec();
    for (int i = 0; i < N; i++) {
      scanf("%d %d %d", &a, &b, &c);
      if(c) Pyes.ptr=pushbackPt(Pyes.ptr,&Pyes.sz, newPoint(a, b));
      else   Pno.ptr=pushbackPt( Pno.ptr, &Pno.sz, newPoint(a, b));
    }
    if(Pyes.sz == 1){
      puts("1");
      continue;
    }
    vec hull = ConvexHull(Pyes);
    int cur = 0;
    pvec events=newPvec();
    for (int i = 0; i < Pno.sz; i++){
      int first = 0, last = 0;
      if (InsideHull(hull, Pno.ptr[i], &first, &last))
        continue;
      events.ptr=pushbackP(events.ptr, &events.sz, newPair( slope(operatorSub( hull.ptr[first],Pno.ptr[i] )) , -1));
      events.ptr=pushbackP(events.ptr, &events.sz, newPair( slope(operatorSub( hull.ptr[last ],Pno.ptr[i] )) ,  1));
      if(!slopecmp(events.ptr[events.sz-1].first, events.ptr[events.sz-2].first))
        cur++;
    }
    int best = cur;
    qsort(events.ptr, events.sz, sizeof(pair), eventcmp);
    for (int i = 0; i < events.sz; i++){
      cur += events.ptr[i].second;
      best = max(best, cur);
    }
    printf("%d\n", N-best);
  }while(0);
}



































































