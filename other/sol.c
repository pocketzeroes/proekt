#include<stdio.h>  // panda
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ typeof(a) tmp; tmp = a; a = b; b = tmp; }while(0)
typedef double db;
db eps = 1e-6;

int sign(db k){
  if(k > eps)
    return 1;
  else if(k < -eps)
    return -1;
  return 0;
}
int cmp(db k1, db k2){
  return sign(k1 - k2);
}
int inmidd(db k1, db k2, db k3){
  return sign (k1 - k3) * sign (k2 - k3) <= 0;
}
typedef struct{
  db x, y;
}pt;

pt opAdd(pt t, pt o){
  return(pt){o.x+t.x, o.y+t.y};
}
pt opSub(pt t, pt o){
  return (pt){t.x-o.x, t.y-o.y};
}
pt opMul(pt t, db o){
  return(pt){t.x*o, t.y*o};
}
pt opDiv(pt t, db o){
  return(pt){t.x/o, t.y/o};
}
int opEq(pt t, pt o){
  return cmp(t.x, o.x) == 0 &&
         cmp(t.y, o.y) == 0;
}
pt turn90(pt t){
  return (pt){-t.y, t.x};
}
bool opLt(pt t, pt o){
  int a = cmp(t.x, o.x);
   if(a == -1)
    return 1;
  else if(a == 1)
    return 0;
  else
    return cmp(t.y, o.y) == -1;
}
db Abs(pt t){
  return sqrt(t.x*t.x + t.y*t.y);
}
int getP(pt t){
  return sign(t.y) == 1 ||
        (sign(t.y) == 0 &&
         sign(t.x) == -1);
}

int inmid(pt k1, pt k2, pt k3){
  return inmidd(k1.x, k2.x, k3.x) &&
         inmidd(k1.y, k2.y, k3.y);
}
db cross (pt k1, pt k2){
  return k1.x * k2.y - k1.y * k2.x;
}
db dot (pt k1, pt k2){
  return k1.x * k2.x + k1.y * k2.y;
}
int compareangle (pt k1, pt k2){
  return getP(k1) <  getP(k2) ||
        (getP(k1) == getP(k2) && sign (cross (k1, k2)) > 0);
}
pt getLL (pt k1, pt k2, pt k3, pt k4){
  db w1 = cross(opSub(k1, k3), opSub(k4, k3));
  db w2 = cross(opSub(k4, k3), opSub(k2, k3));
  return opDiv(opAdd(opMul(k1,w2), opMul(k2,w1)),(w1+w2));
}
int intersect (db l1, db r1, db l2, db r2){
  if (l1 > r1)
    swap(l1, r1);
  if (l2 > r2)
    swap(l2, r2);
  return cmp (r1, l2) != -1 && cmp (r2, l1) != -1;
}
int checkSS (pt k1, pt k2, pt k3, pt k4){
  return intersect (k1.x, k2.x, k3.x, k4.x) &&
         intersect (k1.y, k2.y, k3.y, k4.y) &&
         sign (cross(opSub(k3, k1), opSub(k4, k1))) *
         sign (cross(opSub(k3, k2), opSub(k4, k2))) <= 0 &&
         sign (cross(opSub(k1, k3), opSub(k2, k3))) *
         sign (cross(opSub(k1, k4), opSub(k2, k4))) <= 0;
}
int onS (pt k1, pt k2, pt q){
  return inmid (k1, k2, q) && sign (cross (opSub(k1, q), opSub(k2, k1))) == 0;
}
typedef struct{
  pt a, b;
}line;
line newline(pt a, pt b){
  return(line){a,b};
}
int include(line p, pt k){
  return sign(cross(opSub(p.b, p.a), opSub(k, p.a))) > 0;
}
pt dir(line p){
  return opSub(p.b, p.a);
}
pt getLL2(line k1, line k2){
  return getLL(k1.a, k1.b, k2.a, k2.b);
}
int parallel (line k1, line k2){
  return sign(cross(dir(k1), dir(k2))) == 0;
}
int sameDir (line k1, line k2){
  return parallel(k1, k2) && sign(dot(dir(k1), dir(k2))) == 1;
}
int cmpL(const void*pa, const void*pb){
  line*aa=(line*)pa;
  line*bb=(line*)pb;
  line k1= *aa;
  line k2= *bb;
  if(sameDir (k1, k2))
    return include(k2, k1.a)?-1:1;
  return compareangle(dir(k1), dir(k2))?-1:1;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
line*pushbackL(line*array, int *size, line value){
  line*output = resizeArray(array, line, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	line*ptr;
	int sz;
}vecl;
vecl newVecL(){
	vecl rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int checkpos(line k1, line k2, line k3){
  return include(k3, getLL2(k1, k2));
}
vecl getHL(vecl*L){
  qsort(L.ptr, L.sz);
  deque < line > q;
  for (int i = 0; i < (int) L.size (); i++){
    if (i && sameDir (L[i], L[i - 1]))
      continue;
    while (q.size () > 1
            && !checkpos (q[q.size () - 2], q[q.size () - 1], L[i]))
      q.pop_back ();
    while (q.size () > 1 && !checkpos (q.b, q.a, L[i]))
      q.pop_front ();
    q.push_back (L[i]);
  }
  while (q.size () > 2 && !checkpos (q[q.size () - 2], q[q.size () - 1], q.a))
    q.pop_back ();
  while (q.size () > 2 && !checkpos (q.b, q.a, q[q.size () - 1]))
    q.pop_front ();
  vector < line > ans;
  for (int i = 0; i < q.size (); i++)
    ans.push_back (q[i]);
  return ans;
}
int contain(pt*A, pt q){
  int pd = 0;
  for(int i = 1; i < A.sz; i++){
    pt u = A[i-1],
       v = A[i];
    if(onS (u, v, q))
      return 1;
    if(cmp (u.y, v.y) > 0)
      swap (u, v);
    if(cmp (u.y, q.y) >= 0 || cmp (v.y, q.y) < 0)
      continue;
    if(sign (cross (u - v, q - v)) < 0)
      pd ^= 1;
  }
  return pd << 1;
}
int main(){
  int n;
  double ans = 0;
  scanf ("%d", &n);
  pt p[n+1];
  for (int i = 0; i < n; ++i)
    scanf ("%lf %lf", &p[i].x, &p[i].y);
  for (int i = 0; i < n; ++i){
    vector < line > L;
    L.pushback(line{pt{ -20000, -20000}, pt{ 20000, -20000}});
    L.pushback(line{pt{  20000, -20000}, pt{ 20000,  20000}});
    L.pushback(line{pt{  20000,  20000}, pt{-20000,  20000}});
    L.pushback(line{pt{ -20000,  20000}, pt{-20000, -20000}});
    for (int j = 0; j < n; ++j){
      if (i == j)
        continue;
      pt mid = (p[i] + p[j]) / 2;
      L.pushback(line{ mid, (p[j] - mid).turn90 () + mid});
    }
    L = getHL (L);
    int sz = int (L.size ());
    if (sz > 2){
      pt v[sz];
      for (int j = 0; j < sz; ++j){
        v[j] = getLL2(L[j], L[(j + 1) % sz]);
        p[n]=p[0];
        if(contain(p, v[j]))
          ans = max (ans, (p[i] - v[j]).Abs ());
      }
      for (int j = 0; j < sz; ++j){
        line l1 = line{v[j], v[(j + 1) % sz]};
        for (int k = 0; k < n; ++k){
          line l2 = line{p[k], p[(k + 1) % n]};
          if (checkSS(v[j], v[(j + 1) % sz], p[k], p[(k + 1) % n])){
            pt u = getLL2(l1, l2);
            ans = max (ans, (p[i] - u).Abs ());
          }
        }
      }
    }
  }
  printf ("%.8f\n", ans);
  return 0;
}
