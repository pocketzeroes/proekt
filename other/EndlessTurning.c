#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
int R, cur, next1;
ll N;
double X, Y;
const double UB = 1E7+1;
char*name[123];
double xline[123][2];
double yline[123][2];
double slope[123];
int nr[123];

char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

typedef struct point{
  double x, y;
  int L;
}point;
point newpoint(double _x, double _y, int _L){
  point rez;
  rez.x = _x;
  rez.y = _y;
  rez.L = _L;
  return rez;
}
int cmpPt(point lhs, point rhs){
  if(fabs(lhs.x - rhs.x) > 1E-6)
    return(lhs.x < rhs.x)?-1:1;
  return(lhs.y < rhs.y)?-1:1;
}
int cmpPoint(const void*pa, const void*pb){
  point*lhs=(point*)pa;
  point*rhs=(point*)pb;
  if(fabs(lhs->x - rhs->x) > 1E-6)
    return(lhs->x < rhs->x)?-1:1;
  return(lhs->y < rhs->y)?-1:1;
}
point ipts[123][123];

point calcintersection(int i, int j){
  double L1x1 = xline[i][0];
  double L1x2 = xline[i][1];
  double L1y1 = yline[i][0];
  double L1y2 = yline[i][1];
  double L2x1 = xline[j][0];
  double L2x2 = xline[j][1];
  double L2y1 = yline[j][0];
  double L2y2 = yline[j][1];
  double c1x  = L1y2 - L1y1;
  double c1y  = L1x1 - L1x2;
  double c1   = L1x1*(L1y1 - L1y2) + L1y1*(L1x2 - L1x1);
  double c2x  = L2y2 - L2y1;
  double c2y  = L2x1 - L2x2;
  double c2   = L2x1*(L2y1 - L2y2) + L2y1*(L2x2 - L2x1);
  double x,y;
  if (fabs(c1y) > 1E-8)
    slope[i] = -c1x / c1y;
  else
    slope[i] = 1E12;
  if (fabs(c2y) > 1E-8)
    slope[j] = -c2x / c2y;
  else
    slope[j] = 1E12;
  assert(fabs(c1x*L1x1 + c1y*L1y1 + c1) < 1E-7);
  assert(fabs(c1x*L1x2 + c1y*L1y2 + c1) < 1E-7);
  assert(fabs(c2x*L2x1 + c2y*L2y1 + c2) < 1E-7);
  assert(fabs(c2x*L2x2 + c2y*L2y2 + c2) < 1E-7);
  if (fabs(c2x) > 1E-8) {
    double d = c1y - (c1x/c2x)*c2y;
    if (fabs(d) < 1E-8)
      return newpoint(0,0,-1);
    y = (-c1 + c1x/c2x*c2) / d;
    x = (-c2 - c2y*y) / c2x;
  }
  else if (fabs(c2y) > 1E-8){
    double d = c1x - (c1y/c2y)*c2x;
    if (fabs(d) < 1E-8)
      return newpoint(0,0,-1);
    x = (-c1 + c1y/c2y*c2) / d;
    y = (-c2 - c2x*x) / c2y;
  }
  else {
    assert(false);
  }
  assert( (fabs(x) < UB) && (fabs(y) < UB) );
  assert(fabs(c1x*x + c1y*y + c1) < 1E-3);
  assert(fabs(c2x*x + c2y*y + c2) < 1E-3);
  return newpoint(x,y,0);
}
void findstartingpoint(){
  for (int i = 0; i < R; i++){
    double Lx1 = xline[i][0];
    double Lx2 = xline[i][1];
    double Ly1 = yline[i][0];
    double Ly2 = yline[i][1];
    double cx = Ly2 - Ly1;
    double cy = Lx1 - Lx2;
    double c = Lx1*(Ly1 - Ly2) + Ly1*(Lx2 - Lx1);
    if (fabs(cx*X + cy*Y + c) < 1E-8) {
      cur = i;
      point P = newpoint(X,Y,-1);
      for (int j = 0; j < nr[i]; j++) {
        if(cmpPt(P, ipts[i][j])<0){
          next1 = ipts[i][j].L;
          return;
        }
      }
      next1 = -1;
      return;
    }
  }
  assert(false);
}
int findindex(int i, int j){
  for (int k = 0; k < nr[i]; k++)
    if (ipts[i][k].L == j)
      return k;
  assert(false);
}
void doit(){
  scanf("%d %lld %lf %lf", &R, &N, &X, &Y);
  for(int i=0; i<R; i++){
    nr[i] = 0;
    name[i] = getstr();
    scanf("%lf %lf %lf %lf", &xline[i][0], &yline[i][0], &xline[i][1], &yline[i][1]);
    assert( (fabs(xline[i][0]) < UB) && (fabs(yline[i][0]) < UB) && (fabs(xline[i][1]) < UB) && (fabs(yline[i][1])) < UB );
    for (int j = 0; j < i; j++) {
      point t = calcintersection(i,j);
      if (t.L == 0) {
        ipts[i][j] = newpoint(t.x, t.y, j);
        ipts[j][i] = newpoint(t.x, t.y, i);
        nr[i]++;
        nr[j]++;
      }
      else if (t.L == -1) {
        ipts[i][j] = newpoint(UB, UB, -1);
        ipts[j][i] = newpoint(UB, UB, -1);
      }
    }
    ipts[i][i] = newpoint(UB, UB, -1);
  }
  for(int i = 0; i < R; i++){
    qsort(ipts[i], R, sizeof(point), cmpPoint);
  }
  findstartingpoint();
  int dir = 1;
  int firstline = cur;
  ll steps = 1;
  while (steps <= N) {
    if (next1 == -1){
      puts( name[cur] );
      return;
    }
    if(next1 == firstline)
      N = (N % steps) + steps;
    if(slope[cur] < slope[next1]){
      dir *= -1;
    }
    int k = findindex(next1, cur);
    assert(ipts[next1][k].L == cur);
    if((k+dir < 0) || (k+dir >= nr[next1])){
      cur = next1;
      next1 = -1;
    }
    else{
      int nextnext = ipts[next1][k+dir].L;
      cur = next1;
      next1 = nextnext;
    }
    steps++;
  }
  puts( name[cur] );
}
int main(){
  int T = 1;
  for(int t=1; t<=T; t++)
    doit();
  return 0;
}


