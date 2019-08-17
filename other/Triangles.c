#include<stdio.h>
#include<stdbool.h>

#define EPS 1e-6
typedef struct{
  double x;
  double y;
  double z;
} pt;
bool leq(double x, double y){
  return (x <= y + EPS) || (x <= y - EPS);
}
pt cross(pt p1, pt p2){
  pt ret;
  ret.x = p1.y * p2.z - p1.z * p2.y;
  ret.y = p1.z * p2.x - p1.x * p2.z;
  ret.z = p1.x * p2.y - p1.y * p2.x;
  return ret;
}
double dot(pt v1, pt v2){
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
pt mul(pt p, double c){
    pt ret;
  ret.x = p.x * c;
  ret.y = p.y * c;
  ret.z = p.z * c;
  return ret;
}
pt add(pt p1, pt p2){
  pt ret;
  ret.x = p1.x + p2.x;
  ret.y = p1.y + p2.y;
  ret.z = p1.z + p2.z;
  return ret;
}
pt sub(pt p1, pt p2){
  pt ret;
  ret.x = p1.x - p2.x;
  ret.y = p1.y - p2.y;
  ret.z = p1.z - p2.z;
  return ret;
}
void prn(pt p){
 printf("(%.3lf, %.3lf, %.3lf)\n", p.x, p.y, p.z);
}
bool sameside(pt p1, pt p2, pt a, pt b){
  pt c1 = cross(sub(b,a), sub(p1,a));
  pt c2 = cross(sub(b,a), sub(p2,a));
  double d = dot(c1,c2);
  return leq(0, d);
}
bool inside(pt p, pt a, pt b, pt c){
  return sameside(p, a, b, c) && sameside(p, b, a, c) && sameside(p, c, a, b);
}
int main(){
  int cases;
  scanf("%d", &cases);
  pt points[6];
  while(cases-->0){
  for ( int i = 0; i < 6; i++ ){
    scanf("%lf%lf%lf", &points[i].x, &points[i].y, &points[i].z);
  }
  pt n1 = cross(sub(points[1],points[0]), sub(points[2],points[0]));
  int n_in = 0;
  int n_out = 0;
  for ( int i = 3; i < 6; i++ ){
    int j = i < 5 ? (i + 1):3;
    pt lv = sub(points[j], points[i]);
    if ( dot(lv, n1) == 0 ) continue;
    double s = dot(n1, sub(points[0], points[i])) / (double) dot(n1,lv);
    pt intersect = add(points[i],mul(lv,s));
    bool in = inside(intersect, points[0], points[1], points[2]);
    if ( leq(0,s) && leq(s,1) ) {
      if ( in ) n_in++;
      else n_out++;
    }
  }
  printf( ( n_in > 0 && n_out > 0 ) ? "YES\n":"NO\n");
  }
  return 0;
}
