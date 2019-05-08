#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void reverse(char * str){
  if (str){
    char * end = str + strlen(str) - 1;
#   define XOR_SWAP(a,b) do{\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
    while (str < end){
      XOR_SWAP(*str, *end);
      str++;
      end--;
    }
#   undef XOR_SWAP
  }
}
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int  n;
char*s;

double Dist(double x1, double y1, double x2, double y2){
  double dx = x2 - x1;
  double dy = y2 - y1;
  return sqrt(dx * dx + dy * dy);
}
double Adjust(){
  int i = 0;
  while (i < n && s[i] == 'T')
    ++i;
  if (i == n)
    return -0.5;
  if (i == 0){
    if (s[i] == 'S')
      return 0;
    else
      return -2 + M_PI / 2;
  }
  double x1 = 0.5;
  double y1 = sqrt(3) / 2;
  if (s[i] == 'S'){
    double x2 = i;
    double y2 = 1.0;
    return -x2 - 1 + Dist(0, 0, x1, y1) + Dist(x1, y1, x2, y2); 
  }
  else{
    double xc    = i + 0.5;
    double yc    = 0.5;
    double h     = Dist(x1, y1, xc, yc);
    double alpha = atan2(y1 - yc, x1 - xc);
    double fi    = acos(0.5 / h);
    double x2    = xc + 0.5 * cos(alpha - fi);
    double y2    = yc + 0.5 * sin(alpha - fi);
    return -xc - 1 + Dist(0, 0, x1, y1) + Dist(x1, y1, x2, y2) + 0.5 * (alpha - fi - M_PI / 2);
  }
}
int main(){
  scanf("%d", &n);
  s = getstr();
  double ret = 2 * n + 2;
  ret += Adjust();
  reverse(s);
  ret += Adjust();
  printf("%.6lf\n", ret);
  return 0;
}
